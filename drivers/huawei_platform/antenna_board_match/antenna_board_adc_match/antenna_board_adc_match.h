/*
 * drivers/antenna_board_match/antenna_board_adc_match.h
 *
 * huawei antenna board match driver
 *
*/

#ifndef _ANTENNA_BOARD_ADC_MATCH
#define _ANTENNA_BOARD_ADC_MATCH
#include <linux/device.h>

#define DEFAULT_ANTENNA_BOARD_ADC_CHANNEL (7)

struct antenna_adc_match_info {
    struct device *dev;
};

#endif