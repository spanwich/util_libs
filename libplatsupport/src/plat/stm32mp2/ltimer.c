/*
 * Copyright 2025, PhD Research Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * STM32MP2 ltimer — minimal implementation using ARM generic timer.
 * Provides get_time (via CNTPCT_EL0) and no-op set_timeout.
 * Sufficient for SerialServer/TimeServer to function.
 */

#include <platsupport/ltimer.h>
#include <utils/util.h>
#include <string.h>

/* ARM generic timer frequency: 40 MHz on STM32MP2 (from CNTFRQ_EL0) */
static uint64_t timer_freq = 0;

static inline uint64_t read_cntpct(void)
{
    uint64_t val;
    asm volatile("mrs %0, cntpct_el0" : "=r"(val));
    return val;
}

static inline uint64_t read_cntfrq(void)
{
    uint64_t val;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(val));
    return val;
}

static int stm32mp2_get_time(void *data, uint64_t *time)
{
    if (!timer_freq) {
        timer_freq = read_cntfrq();
        if (!timer_freq) {
            timer_freq = 40000000; /* fallback: 40 MHz */
        }
    }
    uint64_t ticks = read_cntpct();
    /* Convert ticks to nanoseconds: ns = ticks * 1e9 / freq */
    *time = (ticks / timer_freq) * 1000000000ULL +
            ((ticks % timer_freq) * 1000000000ULL) / timer_freq;
    return 0;
}

static int stm32mp2_set_timeout(void *data, uint64_t ns, timeout_type_t type)
{
    /* No timeout IRQ support — SerialServer polling will still work */
    return 0;
}

static int stm32mp2_reset(void *data)
{
    return 0;
}

static void stm32mp2_destroy(void *data)
{
}

static size_t stm32mp2_get_num_irqs(void *data)
{
    return 0;
}

static int stm32mp2_get_nth_irq(void *data, size_t n, ps_irq_t *irq)
{
    return EINVAL;
}

static size_t stm32mp2_get_num_pmems(void *data)
{
    return 0;
}

static int stm32mp2_get_nth_pmem(void *data, size_t n, pmem_region_t *region)
{
    return EINVAL;
}

static int stm32mp2_get_resolution(void *data, uint64_t *resolution)
{
    *resolution = 25; /* 25 ns at 40 MHz */
    return 0;
}

int ltimer_default_init(ltimer_t *timer, ps_io_ops_t ops,
                        ltimer_callback_fn_t callback, void *callback_token)
{
    if (!timer) {
        return EINVAL;
    }
    memset(timer, 0, sizeof(*timer));

    timer->get_time = stm32mp2_get_time;
    timer->set_timeout = stm32mp2_set_timeout;
    timer->reset = stm32mp2_reset;
    timer->destroy = stm32mp2_destroy;
    timer->get_num_irqs = stm32mp2_get_num_irqs;
    timer->get_nth_irq = stm32mp2_get_nth_irq;
    timer->get_num_pmems = stm32mp2_get_num_pmems;
    timer->get_nth_pmem = stm32mp2_get_nth_pmem;
    timer->get_resolution = stm32mp2_get_resolution;

    return 0;
}

int ltimer_default_describe(ltimer_t *timer, ps_io_ops_t ops)
{
    return 0;
}
