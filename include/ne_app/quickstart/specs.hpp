// SPDX-License-Identifier: Apache-2.0
// Copyright 2026, Ne.app. All rights reserved
// Official repository: https://github.com/ne-app/adb

#pragma once

#include <ne_app/core/store.hpp>
#include <ne_app/www/httplib.hpp>

/// @brief Namespace of Ne.app's QS Cache specs.
namespace ne_app::qs::detail {

    /// @brief File frame from host configuration file to download for client file.
    struct qs_info_frm final {
        int32_t magic_;
        int16_t type_;
        size_t len_;
        uint8_t pad_[4];
    };

    enum : int16_t {
        kQSFileInvalid,
        kQSFilePDF = 700,
        kQSFileJSON,
        kQSFileJS,
        kQSFileHTML,
        kQSFileConfig,
    };

    enum : int32_t {
        kQSMagicFilePDF = 0x874f8d,
        kQSMagicFileJSON,
        kQSMagicFileHTML,
        kQSMagicFileJS,
    };

}
