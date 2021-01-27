/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVELEDGER_BITFLYER_BITFLYER_WALLET_H_
#define BRAVELEDGER_BITFLYER_BITFLYER_WALLET_H_

#include <string>

#include "bat/ledger/ledger.h"

namespace ledger {
class LedgerImpl;

namespace bitflyer {

class BitflyerWallet {
 public:
  explicit BitflyerWallet(LedgerImpl* ledger);

  ~BitflyerWallet();

  void Generate(ledger::ResultCallback callback);

 private:
  LedgerImpl* ledger_;  // NOT OWNED
};

}  // namespace bitflyer
}  // namespace ledger
#endif  // BRAVELEDGER_BITFLYER_BITFLYER_WALLET_H_
