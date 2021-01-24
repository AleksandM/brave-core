/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_LEDGER_URL_FETCHER_H_
#define BAT_LEDGER_URL_FETCHER_H_

#include <string>

#include "bat/ledger/internal/async_result.h"
#include "bat/ledger/internal/bat_ledger_context.h"
#include "brave/vendor/bat-native-ledger/include/bat/ledger/public/interfaces/ledger.mojom.h"

namespace ledger {

class URLFetcher : public BATLedgerContext::Component {
 public:
  static const std::string kComponentKey;

  using FetchResult = AsyncResult<mojom::UrlResponsePtr>;
  virtual FetchResult Fetch(mojom::UrlRequestPtr request);

 private:
  friend class BATLedgerContext;

  explicit URLFetcher(BATLedgerContext* context);

  void LogURLRequest(const mojom::UrlRequest& request);
  void LogURLResponse(const mojom::UrlResponse& response);
  void LogURLResponseDetails(const mojom::UrlResponse& response);
};

}  // namespace ledger

#endif  // BAT_LEDGER_URL_FETCHER_H_
