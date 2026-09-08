/*
 * Copyright 2025, PhD Research Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * STM32MP25x character device stub.
 * Returns a valid but no-op device so callers that check for NULL
 * (e.g., VM_Arm plat_pre_init) don't abort.
 * Actual serial output uses seL4_DebugPutChar via the kernel UART frame.
 */

#include <platsupport/chardev.h>
#include <platsupport/plat/serial.h>
#include <string.h>

struct ps_chardevice *
ps_cdev_init(enum chardev_id id, const ps_io_ops_t *o, struct ps_chardevice *d)
{
    if (d) {
        memset(d, 0, sizeof(*d));
    }
    return d;
}
