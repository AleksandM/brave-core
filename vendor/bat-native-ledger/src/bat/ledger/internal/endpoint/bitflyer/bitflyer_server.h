/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVELEDGER_ENDPOINT_BITFLYER_BITFLYER_SERVER_H_
#define BRAVELEDGER_ENDPOINT_BITFLYER_BITFLYER_SERVER_H_

#include <memory>

#include "bat/ledger/internal/endpoint/bitflyer/post_oauth/bitflyer_post_oauth.h"
// #include "bat/ledger/internal/endpoint/bitflyer/post_transaction/post_transaction.h"
// #include "bat/ledger/internal/endpoint/bitflyer/post_transaction_commit/post_transaction_commit.h"
#include "bat/ledger/ledger.h"

namespace ledger {
class LedgerImpl;

namespace endpoint {

class BitflyerServer {
 public:
  explicit BitflyerServer(LedgerImpl* ledger);
  ~BitflyerServer();

  bitflyer::PostOauth* post_oauth() const;

 private:
  std::unique_ptr<bitflyer::PostOauth> post_oauth_;
//  std::unique_ptr<bitflyer::PostTransaction> post_transaction_;
//  std::unique_ptr<bitflyer::PostTransactionCommit> post_transaction_commit_;
};

}  // namespace endpoint
}  // namespace ledger

#endif  // BRAVELEDGER_ENDPOINT_BITFLYER_BITFLYER_SERVER_H_
