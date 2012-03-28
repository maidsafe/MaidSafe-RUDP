/*******************************************************************************
 *  Copyright 2012 MaidSafe.net limited                                        *
 *                                                                             *
 *  The following source code is property of MaidSafe.net limited and is not   *
 *  meant for external use.  The use of this code is governed by the licence   *
 *  file licence.txt found in the root of this directory and also on           *
 *  www.maidsafe.net.                                                          *
 *                                                                             *
 *  You are not free to copy, amend or otherwise use this source code without  *
 *  the explicit written permission of the board of directors of MaidSafe.net. *
 ******************************************************************************/
// Original author: Christopher M. Kohlhoff (chris at kohlhoff dot com)

#include "maidsafe/transport/rudp_shutdown_packet.h"

namespace asio = boost::asio;

namespace maidsafe {

namespace transport {

RudpShutdownPacket::RudpShutdownPacket() {
  SetType(kPacketType);
}

bool RudpShutdownPacket::IsValid(const asio::const_buffer &buffer) {
  return (IsValidBase(buffer, kPacketType) &&
          (asio::buffer_size(buffer) == kPacketSize));
}

bool RudpShutdownPacket::Decode(const asio::const_buffer &buffer) {
  if (!IsValid(buffer))
    return false;
  return DecodeBase(buffer, kPacketType);
}

size_t RudpShutdownPacket::Encode(const asio::mutable_buffer &buffer) const {
  return EncodeBase(buffer);
}

}  // namespace transport

}  // namespace maidsafe

