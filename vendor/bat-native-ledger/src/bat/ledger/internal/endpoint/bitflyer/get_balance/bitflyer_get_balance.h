/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVELEDGER_ENDPOINT_BITFLYER_GET_BALANCE_GET_BALANCE_H_
#define BRAVELEDGER_ENDPOINT_BITFLYER_GET_BALANCE_GET_BALANCE_H_

#include <string>

#include "bat/ledger/ledger.h"

// GET https://bitflyer.jp/api/link/v1/account/inventory
//
// Success code:
// HTTP_OK (200)
//
// Error codes:
// HTTP_UNAUTHORIZED (401)
//
// Response body:
// {
//   "account_hash": "0123456789",
//   "inventory": [
//     {
//       "currency_code": "JPY",
//     	 "amount": 1024078,
//     	 "available": 508000
//     },
//     {
//       "currency_code": "BTC",
//    	 "amount": 10.24,
//     	 "available": 4.12
//     },
//     {
//       "currency_code": "ETH",
//     	 "amount": 10.24,
//     	 "available": 4.12
//     }
//   ]
// }

namespace ledger {
class LedgerImpl;

namespace endpoint {
namespace bitflyer {

using GetBalanceCallback = std::function<void(
    const type::Result result,
    const double available)>;

class GetBalance {
 public:
  explicit GetBalance(LedgerImpl* ledger);
  ~GetBalance();

  void Request(
      const std::string& address,
      const std::string& token,
      GetBalanceCallback callback);

 private:
  std::string GetUrl(const std::string& address);

  type::Result CheckStatusCode(const int status_code);

  type::Result ParseBody(
      const std::string& body,
      double* available);

  void OnRequest(
      const type::UrlResponse& response,
      GetBalanceCallback callback);

  LedgerImpl* ledger_;  // NOT OWNED
};

}  // namespace bitflyer
}  // namespace endpoint
}  // namespace ledger

#endif  // BRAVELEDGER_ENDPOINT_BITFLYER_GET_BALANCE_GET_BALANCE_H_
