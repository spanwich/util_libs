/*
 * Copyright 2025, PhD Research Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * STM32MP25x serial — USART2 @ 0x400e0000 (debug console).
 */

#pragma once

#define USART2_PADDR  0x400e0000
#define USART2_IRQ    (115 + 32)  /* GIC SPI 115 */

enum chardev_id {
    STM32_USART2,
    /* Aliases */
    PS_SERIAL0 = STM32_USART2,
    /* defaults */
    PS_SERIAL_DEFAULT = STM32_USART2
};

#define DEFAULT_SERIAL_PADDR        USART2_PADDR
#define DEFAULT_SERIAL_INTERRUPT    USART2_IRQ
