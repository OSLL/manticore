#include <process/proc/proc.h>
#include <utils/string_utils.h>
#include <utils/exceptions.h>

#include <boost/regex.hpp>

#include <algorithm>
#include <fstream>
#include <memory>

namespace manticore { namespace process {

namespace detail {

    MemoryRegionConstPtr ParseRegion(std::string const & line) {
        static const boost::regex split("^([[:xdigit:]]+)-([[:xdigit:]]+)\\s+([-rwxp]{4})\\s+([[:xdigit:]]+)\\s+([[:graph:]]+)\\s+(\\d+)\\s+([[:graph:]]*)$");
        MemoryRegionPtr region;
        boost::smatch match;
        try {
            if (boost::regex_match(line, match, split)) {
                region = std::make_shared<MemoryRegion>();

                size_t lower = std::stoul(match[1], nullptr, 16);
                size_t upper = std::stoul(match[2], nullptr, 16);
                std::string perm = match[3];
                std::string path = match[7];

                region->SetPath(path);
                region->SetRange(MemoryRegion::MemoryRange(lower, upper));
                for (auto it = perm.begin(); it != perm.end(); ++it) {
                    switch (*it) {
                    case 'w': region->SetPermissionFlag(MemoryRegion::PermissionFlag::Write); break;
                    case 'r': region->SetPermissionFlag(MemoryRegion::PermissionFlag::Read); break;
                    case 'x': region->SetPermissionFlag(MemoryRegion::PermissionFlag::Execute); break;
                    case 'p': region->SetPermissionFlag(MemoryRegion::PermissionFlag::Private); break;
                    }
                }
            } else {
                throw std::runtime_error("match not found");
            }
        } catch (std::exception const & ex) {
            throw UnexpectedProcFormatException();
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
        MemoryRegionConstPtr region = detail::ParseRegion(line);
        regions.push_back(detail::ParseRegion(line));
    }

    return regions;
}

void Proc::Dump(pid_t id, std::vector<u8> & memory, MemoryRegionConstPtr const & region) { }

} }
