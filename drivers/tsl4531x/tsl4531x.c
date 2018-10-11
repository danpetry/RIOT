/*
 * Copyright (C) 2016 Inria
 * Copyright (C) 2018 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_tsl4531x
 * @{
 *
 * @file
 * @brief       Device driver for the TSL4531x Luminosity sensor.
 *
 * @author      Daniel Petry <daniel.petry@fu-berlin.de>
 * @author      Juan I Carrano <j.carrano@fu-berlin.de>
 * @author      Alexandre Abadie <alexandre.abadie@inria.fr>
 *
 * This driver was derived from the TSL2561 driver.
 *
 * @}
 */

#include <errno.h>

#include "log.h"
#include "tsl4531x.h"
#include "tsl4531x_internals.h"
#include "xtimer.h"

#define ENABLE_DEBUG        (0)
#include "debug.h"

#define _DATALOW 0
#define _DATAHIGH 1

int tsl4531x_init(tsl4531x_t *dev, const tsl4531x_params_t *params)
{
    uint8_t id;

    /* Initialise I2C bus */
    if (i2c_acquire(params->i2c_dev) < 0) {
        DEBUG("I2C_dev is: %d.", params->i2c_dev);
        DEBUG("[Error] Cannot acquire device.\n");
        return -ENODEV;
    }

    /* Test for connectivity - verify ID and compare against stored value */
    if (i2c_read_reg(params->i2c_dev,
                     params->i2c_addr,
                     TSL4531X_COMMAND(TSL4531X_ID_REG),
                     &id, 0) < 0) {
        DEBUG("[Error] Cannot read ID register.\n");
        i2c_release(params->i2c_dev);
        return -ENXIO;
    }

    DEBUG("[Info] tsl4531x sensor ID ? %d\n", id);

    if (TSL4531X_GET_PARTNO(id) != params->part_number) {
        DEBUG("[Error] not a TSL4531 sensor.\n");
        i2c_release(params->i2c_dev);
        return -ENOTSUP;
    }

    /* Configure device. In low power mode, we initially power the sensor down. */
    if ((i2c_write_reg(params->i2c_dev,
                       params->i2c_addr,
                       TSL4531X_COMMAND(TSL4531X_CONTROL_REG),
                       TSL4531X_CONTROL(TSL4531X_POWER_MODE(params->low_power_mode)),
                       0) < 0)
        ||
        (i2c_write_reg(params->i2c_dev,
                       params->i2c_addr,
                       TSL4531X_COMMAND(TSL4531X_CONFIGURATION_REG),
                       TSL4531X_CONFIG(TSL4531X_PSAVESKIP_ON, params->integration_time),
                       0) < 0)) {

        DEBUG("[Error] Cannot configure device.\n");
        i2c_release(params->i2c_dev);
        return -ENXIO;
    }

    /* If device was configured correctly, initialise the device descriptor */
    dev->i2c_dev = params->i2c_dev;
    dev->i2c_addr = params->i2c_addr;
    dev->integration_time = params->integration_time;
    dev->low_power_mode = params->low_power_mode;
    dev->sample_start_time = 0; /* Device assumed to start up at same time as
                                   microcontroller - i.e. when it hits this line */

    return 0;
}

int tsl4531x_set_low_power_mode(tsl4531x_t *dev, bool low_power_mode)
{
    assert(dev);

    dev->low_power_mode = low_power_mode;

    i2c_write_reg(dev->i2c_dev,
                  dev->i2c_addr,
                  TSL4531X_COMMAND(TSL4531X_CONTROL_REG),
                  TSL4531X_CONTROL(TSL4531X_POWER_MODE(low_power_mode)),
                  0);

    /* In high power mode only, we restart the sample ready timer, because only
       in this mode it's used to indicate readiness after startup. */
    if (!dev->low_power_mode) {
        dev->sample_start_time = xtimer_now_usec();
    }

    return 0;
}

int tsl4531x_start_sample(tsl4531x_t *dev)
{
    assert(dev);

    /* Don't change the mode to one-shot if the device is in high power mode. */
    if (dev->low_power_mode) {
        i2c_write_reg(dev->i2c_dev,
                      dev->i2c_addr,
                      TSL4531X_COMMAND(TSL4531X_CONTROL_REG),
                      TSL4531X_CONTROL(TSL4531X_MODE_SINGLE_ADC_CYCLE),
                      0);

        dev->sample_start_time = xtimer_now_usec();
    }
    else {
        return -EPERM;
    }

    return 0;
}

bool tsl4531x_is_sample_ready(const tsl4531x_t *dev)
{
    assert(dev);

    return ((xtimer_now_usec() - dev->sample_start_time) >
            TSL4531X_GET_INTEGRATION_TIME_USEC(dev->integration_time, TSL4531X_PSAVESKIP_ON));
}

int tsl4531x_get_sample(const tsl4531x_t *dev)
{
    assert(dev);

    uint8_t als_data[2]; /* = {[DATALOW], [DATAHIGH]} */

    i2c_read_regs(dev->i2c_dev,
                  dev->i2c_addr,
                  TSL4531X_COMMAND(TSL4531X_ALSDATA1_REG),
                  als_data, 2, 0);

    return MULTIPLY_DATA((((uint16_t)als_data[_DATAHIGH]) << 8)
                         + als_data[_DATALOW], dev->integration_time);
}

int tsl4531x_simple_read(const tsl4531x_t *dev)
{
    assert(dev);

    if (dev->low_power_mode) {
        i2c_write_reg(dev->i2c_dev,
                      dev->i2c_addr,
                      TSL4531X_COMMAND(TSL4531X_CONTROL_REG),
                      TSL4531X_CONTROL(TSL4531X_MODE_SINGLE_ADC_CYCLE),
                      0);

    }

    /* In low power mode, or just after changing to high power mode, this
       function blocks for several hundred milliseconds. */
    while (!tsl4531x_is_sample_ready(dev)) {}

    return tsl4531x_get_sample(dev);
}
