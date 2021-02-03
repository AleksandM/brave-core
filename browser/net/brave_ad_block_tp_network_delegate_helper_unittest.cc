/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/net/brave_ad_block_tp_network_delegate_helper.h"

#include <memory>
#include <string>
#include <vector>

#include "brave/browser/net/url_context.h"
#include "brave/common/network_constants.h"
#include "chrome/test/base/testing_browser_process.h"
#include "content/public/test/browser_task_environment.h"
#include "content/public/test/test_browser_context.h"
#include "net/base/net_errors.h"
#include "testing/gtest/include/gtest/gtest.h"

using brave::ResponseCallback;

TEST(BraveAdBlockTPNetworkDelegateHelperTest, NoChangeURL) {
  const GURL url("https://bradhatesprimes.brave.com/composite_numbers_ftw");
  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  int rc =
      OnBeforeURLRequest_AdBlockTPPreWork(ResponseCallback(), request_info);
  EXPECT_TRUE(request_info->new_url_spec.empty());
  EXPECT_EQ(rc, net::OK);
}

TEST(BraveAdBlockTPNetworkDelegateHelperTest, EmptyRequestURL) {
  auto request_info = std::make_shared<brave::BraveRequestInfo>(GURL());
  int rc =
      OnBeforeURLRequest_AdBlockTPPreWork(ResponseCallback(), request_info);
  EXPECT_TRUE(request_info->new_url_spec.empty());
  EXPECT_EQ(rc, net::OK);
}

namespace {
class TestTorBrowserContext : public content::TestBrowserContext {
 public:
  TestTorBrowserContext() : content::TestBrowserContext() {}
  ~TestTorBrowserContext() override = default;

  bool IsTor() const override { return true; }
};
}  // namespace

class BraveCNAMEAdBlockTest : public testing::Test {
 public:
  BraveCNAMEAdBlockTest() : tor_browser_context_(new TestTorBrowserContext()) {}
  ~BraveCNAMEAdBlockTest() override = default;

  content::BrowserContext* tor_context() { return tor_browser_context_.get(); }

 private:
  content::BrowserTaskEnvironment task_environment_;
  std::unique_ptr<content::BrowserContext> tor_browser_context_;
};

TEST_F(BraveCNAMEAdBlockTest, DisableRequestsOverTor) {
  const GURL url("https://wow.brave.com");
  auto request_info = std::make_shared<brave::BraveRequestInfo>(url);
  request_info->tab_origin = GURL("https://brave.com");
  request_info->resource_type = blink::mojom::ResourceType::kMainFrame;
  request_info->browser_context = tor_context();

  int rc =
      OnBeforeURLRequest_AdBlockTPPreWork(ResponseCallback(), request_info);
  EXPECT_EQ(rc, net::OK);
}
