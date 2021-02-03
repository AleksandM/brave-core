/* Copyright 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_GREASELION_BROWSER_GREASELION_CONVERTED_EXTENSION_H_
#define BRAVE_COMPONENTS_GREASELION_BROWSER_GREASELION_CONVERTED_EXTENSION_H_

#include <memory>
#include <utility>

#include "base/files/scoped_temp_dir.h"
#include "base/macros.h"
#include "base/memory/weak_ptr.h"

namespace extensions {
class Extension;
}  // namespace extensions

namespace greaselion {

class GreaselionConvertedExtension {
 public:
  GreaselionConvertedExtension(
      scoped_refptr<extensions::Extension> extension,
      std::unique_ptr<base::ScopedTempDir> extension_dir);
  ~GreaselionConvertedExtension();

  scoped_refptr<extensions::Extension> extension() const { return extension_; }
  std::unique_ptr<base::ScopedTempDir>& extension_dir() {
    return extension_dir_;
  }

 private:
  scoped_refptr<extensions::Extension> extension_;
  std::unique_ptr<base::ScopedTempDir> extension_dir_;
  DISALLOW_COPY_AND_ASSIGN(GreaselionConvertedExtension);
};

}  // namespace greaselion

#endif  // BRAVE_COMPONENTS_GREASELION_BROWSER_GREASELION_CONVERTED_EXTENSION_H_
