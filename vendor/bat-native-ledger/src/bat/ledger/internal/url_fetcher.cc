/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/url_fetcher.h"

#include <array>
#include <string>
#include <utility>

#include "base/strings/string_util.h"
#include "bat/ledger/ledger_client.h"
#include "bat/ledger/internal/ledger_impl.h"

namespace {

constexpr size_t kMaxResponseBodySizeForLogging = 128;

constexpr std::array<const char*, 4> kRequestHeadersForLogging = {
    "digest", "signature", "accept", "content-type"};

}  // namespace

namespace ledger {

const std::string URLFetcher::kComponentKey = "url_fetcher";

URLFetcher::URLFetcher(BATLedgerContext* context)
    : BATLedgerContext::Component(context) {}

AsyncResult<mojom::UrlResponsePtr> URLFetcher::Fetch(
    mojom::UrlRequestPtr request) {
  DCHECK(request);
  LogURLRequest(*request);

  FetchResult::Resolver resolver;
  context()->GetLedgerClient()->LoadURL(
      std::move(request),
      [this, resolver](const mojom::UrlResponse& response) mutable {
        LogURLResponse(response);
        LogURLResponseDetails(response);
        resolver.Complete(response.Clone());
      });
  return resolver.result();
}

void URLFetcher::LogURLRequest(const mojom::UrlRequest& request) {
  // TODO(zenparsing): It seems like skip_log is used to hide publisher info
  // network requests for social media sites. Those network requests shouldn't
  // be happening in the bat ledger service though.
  if (request.skip_log)
    return;

  auto stream = context()->LogVerbose(FROM_HERE);

  stream << "\n[ REQUEST ]";
  stream << "\n> URL: " << request.url;
  stream << "\n> Method: " << request.method;

  if (!request.content.empty())
    stream << "\n> Content: " << request.content;

  if (!request.content_type.empty())
    stream << "\n> Content-Type: " << request.content_type;

  for (const std::string& header : request.headers) {
    for (const char* name : kRequestHeadersForLogging) {
      if (base::StartsWith(header, name, base::CompareCase::INSENSITIVE_ASCII))
        stream << "\n> Header " << header;
    }
  }
}

void URLFetcher::LogURLResponse(const mojom::UrlResponse& response) {
  auto stream = context()->LogVerbose(FROM_HERE);

  std::string result;
  if (!response.error.empty())
    result = "Error (" + response.error + ")";
  else if (response.status_code >= 200 && response.status_code < 300)
    result = "Success";
  else
    result = "Failure";

  stream << "\n[ RESPONSE ]";
  stream << "\n> URL: " << response.url;
  stream << "\n> Result: " << result;
  stream << "\n> HTTP Status: " << response.status_code;

  if (response.body.size() <= kMaxResponseBodySizeForLogging)
    stream << "\n> Body: " << response.body;
}

void URLFetcher::LogURLResponseDetails(const mojom::UrlResponse& response) {
  auto stream = context()->LogFull(FROM_HERE);

  stream << "\n[ RESPONSE DETAILS ]"
         << "\n> URL: " << response.url;

  if (response.body.size() > kMaxResponseBodySizeForLogging)
    stream << "\n> Body:\n" << response.body;

  for (auto& header : response.headers)
    stream << "\n> Header: " << header.first << " = " << header.second;
}

}  // namespace ledger
