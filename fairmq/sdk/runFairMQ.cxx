/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <boost/program_options.hpp>
#include <cstdlib>
#include <fairmq/sdk/Topology.h>
#include <fairmq/StateMachine.h>
#include <fairmq/Version.h>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

namespace po = boost::program_options;

struct CLIError : ::std::runtime_error
{
    template<typename... T>
    CLIError(T&&... t)
        : ::std::runtime_error::runtime_error(to_s(std::forward<T>(t)...))
    {}

  private:
    template<typename... T>
    auto to_s(T&&... t) -> std::string
    {
        std::stringstream ss;
        (void)std::initializer_list<int>{(ss << t, 0)...};
        return ss.str();
    }
};

struct CLICommand
{
    CLICommand(const std::string& name, po::program_options options)
      : fName(name)
      , fOptions(options)
      {

      }

    CLICommand(const std::string& name, po::program_options options, std::vector<CLICommand>)
      : fName(name)
      , fOptions(options)
      {

      }

    auto Parse(int argc, char** argv) -> void
    {}
  private:
    std::string fName;
    CLICommand* fParent;
    bool fHasSubcommands;
    std::vector<CLICommand> fSubcommands;
    po::options_description fOptions;
    po::positional_options_description fPositionalOptions;
    po::parsed_options fParsed;
    po::variables_map fVm;
};


auto main(int argc, char** argv) -> int
{
    po::options_description version_opts("<version> options");
    version_opts.add_options()("date", "Print date")("long", "Print git version");
    CLICommand version("version", version_opts);

    po::options_description global("Global options");
    global.add_options()("debug,d", "Enable debug log");
    CLICommand cli("fairmq", global, {version});

    try {
      cli.Parse(argc, argv);
    } catch (CLIError& e) {
      std::cerr << e.what();
      std::cout << cli.Usage();
      return EXIT_FAILURE;
    }

    CLICommand cmd(cli.GetSubcommand());
    std::string cmd_name = cmd.GetName();
    if (cmd_name == "version") {
        if (cmd.GetOption<bool>("long")) {
            std::cout << FAIRMQ_GIT_VERSION;
        } else {
            std::cout << FAIRMQ_VERSION;
        }
        if (cmd.GetOption<bool>("date")) {
            std::cout << " from " << FAIRMQ_GIT_DATE;
        }
        std::cout << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
