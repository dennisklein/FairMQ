/********************************************************************************
 *    Copyright (C) 2021 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "Manager.h"

// Needed to compile-firewall the <boost/process/async.hpp> header because it
// interferes with the <asio/buffer.hpp> header. So, let's factor
// the whole dependency to Boost.Process out of the header.
#include <boost/version.hpp>
#if BOOST_VERSION >= 108800
#include <boost/process/environment.hpp>
#include <boost/process/search_path.hpp>
#include <boost/process/spawn.hpp>
#else
#include <boost/process.hpp>
#endif
#include <fairlogger/Logger.h>

namespace fair::mq::shmem {

// Boost 1.88+ compatibility: boost::process v2 is now default, v1 APIs moved to v1 namespace
// See: https://github.com/boostorg/process/issues/480
#if BOOST_VERSION >= 108800
namespace this_process = boost::process::v1::this_process;
namespace process = boost::process::v1;
#else
namespace this_process = boost::this_process;
namespace process = boost::process;
#endif

bool Manager::SpawnShmMonitor(const std::string& id)
{
    auto const env(this_process::environment());
    std::string const fairmq_path_key("FAIRMQ_PATH");
    std::string const shmmonitor_exe_name("fairmq-shmmonitor");
    std::string const shmmonitor_verbose_key("FAIRMQ_SHMMONITOR_VERBOSE");
    auto path(this_process::path());

    if (env.count(fairmq_path_key)) {
        path.emplace(path.begin(), env.at(fairmq_path_key).to_string());
    }

    auto exe(process::search_path(shmmonitor_exe_name, path));
    if (exe.empty()) {
        LOG(warn) << "could not find " << shmmonitor_exe_name << " in \"$" << fairmq_path_key
                  << ":$PATH\"";
        return false;
    }

    // TODO Move this to fairmq-shmmonitor itself ?
    bool verbose(env.count(shmmonitor_verbose_key)
                 && env.at(shmmonitor_verbose_key).to_string() == "true");

    process::spawn(
        exe, "-x", "-m", "--shmid", id, "-d", "-t", "2000", (verbose ? "--verbose" : ""), env);

    return true;
}

}   // namespace fair::mq::shmem
