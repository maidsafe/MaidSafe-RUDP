/* Copyright (c) 2010 maidsafe.net limited
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
    * Neither the name of the maidsafe.net limited nor the names of its
    contributors may be used to endorse or promote products derived from this
    software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef MAIDSAFE_DHT_TRANSPORT_MESSAGE_HANDLER_H_
#define MAIDSAFE_DHT_TRANSPORT_MESSAGE_HANDLER_H_

#include <memory>
#include <string>
#include "boost/function.hpp"
#include "boost/signals2/signal.hpp"
#include "maidsafe-dht/transport/transport.h"

namespace bs2 = boost::signals2;

namespace maidsafe {

class Securifier;

typedef char SecurityType;
const SecurityType kNone(0x0);
const SecurityType kSign(0x1);
const SecurityType kSignWithParameters(0x2);
const SecurityType kAsymmetricEncrypt(0x4);

namespace transport {

namespace protobuf {
class Endpoint;
class WrapperMessage;
class ManagedEndpointMessage;
class NatDetectionRequest;
class NatDetectionResponse;
class ProxyConnectRequest;
class ProxyConnectResponse;
class ForwardRendezvousRequest;
class ForwardRendezvousResponse;
class RendezvousRequest;
class RendezvousAcknowledgement;
}  // namespace protobuf

// Highest possible message type ID, use as offset for type extensions.
const int kMaxMessageType(1000);

class MessageHandler {
 public:
  typedef std::shared_ptr<bs2::signal<void(                   // NOLINT (Fraser)
      const protobuf::ManagedEndpointMessage&,
      protobuf::ManagedEndpointMessage*,
      transport::Timeout*)>> ManagedEndpointMsgSigPtr;
  typedef std::shared_ptr<bs2::signal<void(                   // NOLINT (Fraser)
      const protobuf::NatDetectionRequest&,
      protobuf::NatDetectionResponse*,
      transport::Timeout*)>> NatDetectionReqSigPtr;
  typedef std::shared_ptr<bs2::signal<void(                   // NOLINT (Fraser)
      const protobuf::NatDetectionResponse&)>> NatDetectionRspSigPtr;
  typedef std::shared_ptr<bs2::signal<void(                   // NOLINT (Fraser)
      const protobuf::ProxyConnectRequest&,
      protobuf::ProxyConnectResponse*,
      transport::Timeout*)>> ProxyConnectReqSigPtr;
  typedef std::shared_ptr<bs2::signal<void(                   // NOLINT (Fraser)
      const protobuf::ProxyConnectResponse&)>> ProxyConnectRspSigPtr;
  typedef std::shared_ptr<bs2::signal<void(                   // NOLINT (Fraser)
      const protobuf::ForwardRendezvousRequest&,
      protobuf::ForwardRendezvousResponse*,
      transport::Timeout*)>> ForwardRendezvousReqSigPtr;
  typedef std::shared_ptr<bs2::signal<void(                   // NOLINT (Fraser)
      const protobuf::ForwardRendezvousResponse&)>> ForwardRendezvousRspSigPtr;
  typedef std::shared_ptr<bs2::signal<void(                   // NOLINT (Fraser)
      const protobuf::RendezvousRequest&)>> RendezvousReqSigPtr;
  typedef std::shared_ptr<bs2::signal<void(                   // NOLINT (Fraser)
      const protobuf::RendezvousAcknowledgement&)>> RendezvousAckSigPtr;
  typedef std::shared_ptr<bs2::signal<void(const TransportCondition&)>>
      ErrorSigPtr;

  explicit MessageHandler(std::shared_ptr<Securifier> securifier)
    : securifier_(securifier),
      on_managed_endpoint_message_(new ManagedEndpointMsgSigPtr::element_type),
      on_nat_detection_request_(new NatDetectionReqSigPtr::element_type),
      on_nat_detection_response_(new NatDetectionRspSigPtr::element_type),
      on_proxy_connect_request_(new ProxyConnectReqSigPtr::element_type),
      on_proxy_connect_response_(new ProxyConnectRspSigPtr::element_type),
      on_forward_rendezvous_request_(
          new ForwardRendezvousReqSigPtr::element_type),
      on_forward_rendezvous_response_(
          new ForwardRendezvousRspSigPtr::element_type),
      on_rendezvous_request_(new RendezvousReqSigPtr::element_type),
      on_rendezvous_acknowledgement_(new RendezvousAckSigPtr::element_type),
      on_error_(new ErrorSigPtr::element_type) {}
  virtual ~MessageHandler() {}
  void OnMessageReceived(const std::string &request,
                         const Info &info,
                         std::string *response,
                         Timeout *timeout);
  void OnError(const TransportCondition &transport_condition);

  std::string WrapMessage(const protobuf::ManagedEndpointMessage &msg);
  std::string WrapMessage(const protobuf::NatDetectionRequest &msg);
  std::string WrapMessage(const protobuf::ProxyConnectRequest &msg);
  std::string WrapMessage(const protobuf::ForwardRendezvousRequest &msg);
  std::string WrapMessage(const protobuf::RendezvousRequest &msg);

  ManagedEndpointMsgSigPtr on_managed_endpoint_message() {
    return on_managed_endpoint_message_;
  }
  NatDetectionReqSigPtr on_nat_detection_request() {
    return on_nat_detection_request_;
  }
  NatDetectionRspSigPtr on_nat_detection_response() {
    return on_nat_detection_response_;
  }
  ProxyConnectReqSigPtr on_proxy_connect_request() {
    return on_proxy_connect_request_;
  }
  ProxyConnectRspSigPtr on_proxy_connect_response() {
    return on_proxy_connect_response_;
  }
  ForwardRendezvousReqSigPtr on_forward_rendezvous_request() {
    return on_forward_rendezvous_request_;
  }
  ForwardRendezvousRspSigPtr on_forward_rendezvous_response() {
    return on_forward_rendezvous_response_;
  }
  RendezvousReqSigPtr on_rendezvous_request() {
    return on_rendezvous_request_;
  }
  RendezvousAckSigPtr on_rendezvous_acknowledgement() {
    return on_rendezvous_acknowledgement_;
  }
  ErrorSigPtr on_error() { return on_error_; }

 protected:
  virtual void ProcessSerialisedMessage(const int &message_type,
                                        const std::string &payload,
                                        const SecurityType &security_type,
                                        const std::string &message_signature,
                                        const Info &info,
                                        std::string *message_response,
                                        Timeout *timeout);
  std::string MakeSerialisedWrapperMessage(
      const int &message_type,
      const std::string &payload,
      SecurityType security_type,
      const std::string &recipient_public_key);
  std::shared_ptr<Securifier> securifier_;

 private:
  MessageHandler(const MessageHandler&);
  MessageHandler& operator=(const MessageHandler&);

  std::string WrapMessage(const protobuf::NatDetectionResponse &msg);
  std::string WrapMessage(const protobuf::ProxyConnectResponse &msg);
  std::string WrapMessage(const protobuf::ForwardRendezvousResponse &msg);
  std::string WrapMessage(const protobuf::RendezvousAcknowledgement &msg);

  ManagedEndpointMsgSigPtr on_managed_endpoint_message_;
  NatDetectionReqSigPtr on_nat_detection_request_;
  NatDetectionRspSigPtr on_nat_detection_response_;
  ProxyConnectReqSigPtr on_proxy_connect_request_;
  ProxyConnectRspSigPtr on_proxy_connect_response_;
  ForwardRendezvousReqSigPtr on_forward_rendezvous_request_;
  ForwardRendezvousRspSigPtr on_forward_rendezvous_response_;
  RendezvousReqSigPtr on_rendezvous_request_;
  RendezvousAckSigPtr on_rendezvous_acknowledgement_;
  ErrorSigPtr on_error_;
};

}  // namespace transport

}  // namespace maidsafe

#endif  // MAIDSAFE_DHT_TRANSPORT_MESSAGE_HANDLER_H_
