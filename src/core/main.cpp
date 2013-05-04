#include <boost/program_options.hpp>
#include <boost/bind.hpp>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <memory>

#include <process/serialize.h>
#include <process/process.h>

namespace {

    using namespace manticore::serialize;
    using namespace manticore::process;
    namespace bpo = boost::program_options;

    void print_register(RegisterConstPtr const & reg) {
        std::cout << "register: " << manticore::utils::string_cast(reg) << std::endl;
    }

    void print_mem_descriptor(MemoryRegionConstPtr const & mem) {
        std::cout << "region: " << manticore::utils::string_cast(mem) << std::endl;
    }

    void dump_memory_region(Process const & process, MemoryRegionConstPtr const & desc) {
        std::fstream file( manticore::utils::stringify("0x", manticore::utils::format_hex(desc->GetLower()), "-",
                                                       "0x", manticore::utils::format_hex(desc->GetUpper()), ".img"),
                           std::ios::binary | std::ios::out );
        std::shared_ptr<std::vector<char> > memory = process.Load(desc);
        std::copy(memory->begin(), memory->end(), std::ostream_iterator<char>(file));
        file.close();
    }

    void help(bpo::options_description const & description) {
        std::cout << description << std::endl;
    }

    void pid(pid_t id) {
        try {
            Process process(id);
            process.Seize();

            std::vector<RegisterConstPtr> snapshot(process.Snapshot());
            std::vector<MemoryRegionConstPtr> regions(process.Regions());

            // dump registers
            std::fstream regs("registers.img", std::ios::binary | std::ios::out);
            regs << snapshot; regs.close();

            // dump memory descriptors
            std::fstream mem_desc("memory.img", std::ios::binary | std::ios::out);
            mem_desc << regions; mem_desc.close();

            // dump memory
            std::for_each(regions.begin(), regions.end(), boost::bind(&dump_memory_region, boost::cref(process), _1));

            // verbose output
            std::cout << "Process " << id << " registers snapshot:" << std::endl;
            std::for_each(snapshot.begin(), snapshot.end(), &print_register);

            std::cout << std::endl << "Process " << id << " memory regions:" << std::endl;
            std::for_each(regions.begin(), regions.end(), &print_mem_descriptor);

            process.Kill();
        } catch (std::exception const & e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    void main_impl(int argc, char **argv) {
        bpo::options_description description("Options");
        description.add_options()
            ("help", "print help")
            ("pid", bpo::value<pid_t>(), "target process id")
        ;

        bpo::variables_map variables;
        bpo::store(bpo::parse_command_line(argc, argv, description), variables);
        bpo::notify(variables);

        if (variables.count("help")) {
            help(description);
            return;
        }

        if (variables.count("pid")) {
            pid(variables["pid"].as<pid_t>());
            return;
        }

        help(description);
    }

}

int main(int argc, char **argv) {
    try {
        main_impl(argc, argv);
        return 0;
    } catch (std::exception const & e) {
        std::cerr << "Unhandled exception reached the top of main: " << e.what();
    }
    return 1;
}
