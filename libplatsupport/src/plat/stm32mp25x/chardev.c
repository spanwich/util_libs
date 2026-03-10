/*
 * Copyright 2025, PhD Research Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * STM32MP25x character device stub.
 * The VM guest accesses USART2 via passthrough; native components
 * use seL4_DebugPutChar. No platsupport serial driver is needed.
 */

#include <platsupport/chardev.h>
#include <platsupport/plat/serial.h>

struct ps_chardevice *
ps_cdev_init(enum chardev_id id, const ps_io_ops_t *o, struct ps_chardevice *d)
{
    /* No hardware serial driver implemented for STM32MP25x yet. */
    return NULL;
}
