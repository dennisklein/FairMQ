/********************************************************************************
 * Copyright (C) 2014-2018 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIR_MQ_TRANSPORTS_H
#define FAIR_MQ_TRANSPORTS_H

#include <fairmq/Tools.h>

#include <memory>
#include <string>
#include <unordered_map>

namespace fair
{
namespace mq
{

enum class Transport
{
    DEFAULT,
    ZMQ,
    NN,
    SHM,
    OFI
};

static std::unordered_map<std::string, Transport> TransportTypes {
    { "default", Transport::DEFAULT },
    { "zeromq", Transport::ZMQ },
    { "nanomsg", Transport::NN },
    { "shmem", Transport::SHM },
    { "ofi", Transport::OFI }
};

static std::unordered_map<Transport, std::string, tools::HashEnum<Transport>> TransportNames {
    { Transport::DEFAULT, "default" },
    { Transport::ZMQ, "zeromq" },
    { Transport::NN, "nanomsg" },
    { Transport::SHM, "shmem" },
    { Transport::OFI, "ofi" }
};

} /* namespace mq */
} /* namespace fair */

#endif /* FAIR_MQ_TRANSPORTS_H */
