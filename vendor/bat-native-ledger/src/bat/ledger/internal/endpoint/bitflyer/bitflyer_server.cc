/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/endpoint/bitflyer/bitflyer_server.h"

#include "bat/ledger/internal/ledger_impl.h"

namespace ledger {
namespace endpoint {

BitflyerServer::BitflyerServer(LedgerImpl* ledger)
    : post_oauth_(std::make_unique<bitflyer::PostOauth>(ledger))
#if 0
      post_transaction_(std::make_unique<bitflyer::PostTransaction>(ledger)),
      post_transaction_commit_(
          std::make_unique<bitflyer::PostTransactionCommit>(ledger))
#endif
{}

BitflyerServer::~BitflyerServer() = default;

bitflyer::PostOauth* BitflyerServer::post_oauth() const {
  return post_oauth_.get();
}

#if 0
bitflyer::PostTransaction* BitflyerServer::post_transaction() const {
  return post_transaction_.get();
}

bitflyer::PostTransactionCommit* BitflyerServer::post_transaction_commit() const {
  return post_transaction_commit_.get();
}
#endif

}  // namespace endpoint
}  // namespace ledger
