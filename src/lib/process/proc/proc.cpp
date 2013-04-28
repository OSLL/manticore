#include <process/proc/proc.h>
#include <utils/string_utils.h>
#include <utils/exceptions.h>

#include <boost/regex.hpp>

#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

namespace manticore { namespace process {

namespace detail {

    MemoryRegionPtr ParseRegion(std::string const & line) {
        static const boost::regex split("^([[:xdigit:]]+)-([[:xdigit:]]+)\\s+([-rwxp]{4})\\s+([[:xdigit:]]+)\\s+([[:graph:]]+)\\s+(\\d+)\\s+([[:graph:]]*)$");
        MemoryRegionPtr region;
        boost::smatch match;
        try {
            if (boost::regex_match(line, match, split)) {
                size_t lower = std::stoul(match[1], nullptr, 16);
                size_t upper = std::stoul(match[2], nullptr, 16);
                std::string perm = match[3];
                std::string path = match[7];

                region = std::make_shared<MemoryRegion>(lower, upper, 0, path);
                region->SetPath(path);
                for (auto it = perm.begin(); it != perm.end(); ++it) {
                    switch (*it) {
                    case 'w': region->SetPermissionFlag(MemoryRegion::PermissionFlag::Write); break;
                    case 'r': region->SetPermissionFlag(MemoryRegion::PermissionFlag::Read); break;
                    case 'x': region->SetPermissionFlag(MemoryRegion::PermissionFlag::Execute); break;
                    case 'p': region->SetPermissionFlag(MemoryRegion::PermissionFlag::Private); break;
                    }
                }
            } else {
                throw std::runtime_error("match not found in line " + line);
            }
        } catch (std::exception const & ex) {
            throw UnexpectedProcFormatException(line);
        }
        return region;
    }

}

std::vector<MemoryRegionConstPtr> Proc::Ranges(pid_t id) {
    std::vector<MemoryRegionConstPtr> regions;
    std::string name(utils::stringify("/proc/", id, "/maps"));
    std::ifstream maps(name.c_str());

    if (!maps.is_open()) {
        throw utils::FileNotFoundException(name);
    }

    while (maps) {
        std::string line;
        std::getline(maps, line);
        if (!line.empty()) {
            MemoryRegionPtr region = detail::ParseRegion(line);
            /* put this check somewhere else */
            if (region->GetPath() != "[vdso]") {
                regions.push_back(region);
            }
        }
    }
    maps.close();

    return regions;
}

std::shared_ptr<std::vector<char> > Proc::Load(pid_t id, MemoryRegionConstPtr const & region) {
    std::string name(utils::stringify("/proc/", id, "/mem"));
    std::ifstream mem(name.c_str(), std::ifstream::binary);
    mem.seekg(region->GetLower(), std::ifstream::beg);
    std::shared_ptr<std::vector<char> > memory(new std::vector<char>(region->GetRange().GetSize()));
    mem.read(&(*memory)[0], region->GetRange().GetSize());
    mem.close();
    return memory;
}

} }
