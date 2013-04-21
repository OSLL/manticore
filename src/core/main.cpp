#include <boost/program_options.hpp>

#include <iostream>
#include <vector>

#include <process/process.h>

namespace bpo = boost::program_options;

void help(bpo::options_description const & description) {
    std::cout << description << std::endl;
}

void pid(pid_t id) {
    try {
        manticore::process::Process process(id);
        process.Seize();

        std::vector<manticore::process::RegisterConstPtr> snapshot(process.Snapshot());
        std::cout << "Process " << id << " registers snapshot:" << std::endl;
        for (std::vector<manticore::process::RegisterConstPtr>::const_iterator it = snapshot.begin(); it != snapshot.end(); ++it) {
            std::cout << "register: " << manticore::utils::string_cast(*it) << std::endl;
        }

        std::vector<manticore::process::MemoryRegionConstPtr> regions(process.Regions());
        for (std::vector<manticore::process::MemoryRegionConstPtr>::const_iterator it = regions.begin(); it != regions.end(); ++it) {
            std::cout << "region: " << manticore::utils::string_cast(*it) << ", size = 0x" << std::hex << (*it)->GetMemory()->size() << std::endl;
        }

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

int main(int argc, char **argv) {
    try {
        main_impl(argc, argv);
        return 0;
    } catch (std::exception const & e) {
        std::cerr << "Unhandled exception reached the top of main: " << e.what();
    }
    return 1;
}
