/*
 * Copyright 2025, PhD Research Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * STM32MP25x clock stub — clocks managed via OP-TEE SCMI.
 */

#pragma once

enum clk_id {
    CLK_MASTER,
    /* ----- */
    NCLOCKS,
    CLK_CUSTOM,
};

enum clock_gate {
    NCLKGATES
};
