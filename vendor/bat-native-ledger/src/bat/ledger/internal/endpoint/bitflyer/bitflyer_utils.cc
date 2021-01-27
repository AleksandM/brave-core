/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/endpoint/bitflyer/bitflyer_utils.h"

#include "base/base64.h"
#include "base/strings/stringprintf.h"
#include "bat/ledger/internal/bitflyer/bitflyer_util.h"
#include "bat/ledger/ledger.h"

namespace ledger {
namespace endpoint {
namespace bitflyer {

const char kStaging[] = "http://demo22oy5z2d2lu6pyoum26m7k.azurewebsites.net";
const char kProduction[] = "https://bitflyer.jp";
const char kClientSecretStaging[] =
    "8862095b1d7ead05ccd7044ad70d43bfe4b1964b297db4536acf46b26259aa42";
const char kClientSecretProduction[] =
    "8862095b1d7ead05ccd7044ad70d43bfe4b1964b297db4536acf46b26259aa42";

std::string GetClientSecret() {
  return ledger::_environment == type::Environment::PRODUCTION
      ? kClientSecretProduction
      : kClientSecretStaging;
}

std::vector<std::string> RequestAuthorization(const std::string& token) {
  std::vector<std::string> headers;

  if (!token.empty()) {
    headers.push_back("Authorization: Bearer " + token);
    return headers;
  }

  const std::string id = ::ledger::bitflyer::GetClientId();
  const std::string secret = GetClientSecret();

  std::string user;
  base::Base64Encode(
      base::StringPrintf(
          "%s:%s",
          id.c_str(),
          secret.c_str()),
      &user);

  headers.push_back("Authorization: Basic " + user);

  return headers;
}

std::string GetServerUrl(const std::string& path) {
  DCHECK(!path.empty());

  std::string url;
  if (ledger::_environment == type::Environment::PRODUCTION) {
    url = kProduction;
  } else {
    url = kStaging;
  }

  return url + path;
}

}  // namespace bitflyer
}  // namespace endpoint
}  // namespace ledger
