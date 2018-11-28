/********************************************************************************
 *    Copyright (C) 2018 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIR_MQ_OFI_CONTEXT_H
#define FAIR_MQ_OFI_CONTEXT_H

#include <FairMQLogger.h>
#include <FairMQTransportFactory.h>

#include <asiofi/domain.hpp>
#include <asiofi/fabric.hpp>
#include <asiofi/info.hpp>
#include <asiofi/memory_resources.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/pmr/synchronized_pool_resource.hpp>
#include <memory>
#include <netinet/in.h>
#include <ostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

namespace fair
{
namespace mq
{
namespace ofi
{

enum class ConnectionType : bool { Bind, Connect };

struct Address {
    std::string Protocol;
    std::string Ip;
    unsigned int Port;
    friend auto operator<<(std::ostream& os, const Address& a) -> std::ostream&
    {
        return os << a.Protocol << "://" << a.Ip << ":" << a.Port;
    }
    friend auto operator==(const Address& lhs, const Address& rhs) -> bool
    {
        return (lhs.Protocol == rhs.Protocol) && (lhs.Ip == rhs.Ip) && (lhs.Port == rhs.Port);
    }
};

struct ContextError : std::runtime_error { using std::runtime_error::runtime_error; };

/**
 * @class Context Context.h <fairmq/ofi/Context.h>
 * @brief Transport-wide context
 *
 * @todo TODO insert long description
 */
class Context
{
  public:
    Context(FairMQTransportFactory& sendFactory,
            FairMQTransportFactory& receiveFactory,
            int numberIoThreads = 1);
    ~Context();

    auto GetAsiofiVersion() const -> std::string;
    auto GetIoContext() -> boost::asio::io_context& { return fIoContext; }
    static auto ConvertAddress(std::string address) -> Address;
    static auto ConvertAddress(Address address) -> sockaddr_in;
    static auto ConvertAddress(sockaddr_in address) -> Address;
    static auto VerifyAddress(const std::string& address) -> Address;
    auto Interrupt() -> void { LOG(debug) << "OFI transport: Interrupted (NOOP - not implemented)."; }
    auto Resume() -> void { LOG(debug) << "OFI transport: Resumed (NOOP - not implemented)."; }
    auto MakeReceiveMessage(size_t size) -> MessagePtr;
    auto MakeSendMessage(size_t size) -> MessagePtr;
    auto GetOfiFabric() -> asiofi::fabric&;
    auto GetOfiDomain() -> asiofi::domain&;
    auto GetMessagePmr() -> boost::container::pmr::memory_resource* { return fMessageMemoryPool.get(); }
    auto GetMessageMR() const -> const asiofi::memory_region& { return fRegisteredMemoryResource->get_region(); }
 
    template<typename... Args>
    auto EmplaceOfiFabric(Args&&... args) -> void
    {
        if (!fOfiFabric) {
            fOfiFabric = tools::make_unique<asiofi::fabric>(std::forward<Args>(args)...);
        } else {
            throw ContextError("ofi fabric already created");
        }
    }

    template<typename... Args>
    auto EmplaceOfiDomain(Args&&... args) -> void
    {
        if (!fOfiDomain) {
            fOfiDomain = tools::make_unique<asiofi::domain>(std::forward<Args>(args)...);
            assert(!fRegisteredMemoryResource);
            fRegisteredMemoryResource = tools::make_unique<asiofi::registered_memory_resource>(*fOfiDomain, 2147483648);
            assert(!fMessageMemoryPool);
            fMessageMemoryPool = tools::make_unique<boost::container::pmr::synchronized_pool_resource>(
                boost::container::pmr::pool_options(), fRegisteredMemoryResource.get());
        } else {
            throw ContextError("ofi domain already created");
        }
    }

  private:
    boost::asio::io_context fIoContext;
    boost::asio::io_context::work fIoWork;
    std::vector<std::thread> fThreadPool;
    FairMQTransportFactory& fReceiveFactory;
    FairMQTransportFactory& fSendFactory;
    std::unique_ptr<asiofi::fabric> fOfiFabric;
    std::unique_ptr<asiofi::domain> fOfiDomain;
    std::unique_ptr<asiofi::registered_memory_resource> fRegisteredMemoryResource;
    std::unique_ptr<boost::container::pmr::synchronized_pool_resource> fMessageMemoryPool;

    auto InitThreadPool(int numberIoThreads) -> void;
}; /* class Context */

} /* namespace ofi */
} /* namespace mq */
} /* namespace fair */

#endif /* FAIR_MQ_OFI_CONTEXT_H */
