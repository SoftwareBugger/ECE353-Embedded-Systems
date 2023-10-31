/**
 * @file joystick.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "joystick.h"

/* Static Global Variables */
static cyhal_adc_t joystick_adc_obj;
static cyhal_adc_channel_t joystick_adc_chan_x_obj;
static cyhal_adc_channel_t joystick_adc_chan_y_obj;
const cyhal_adc_channel_config_t channel_config = { .enable_averaging = false, .min_acquisition_ns = 220, .enabled = true };

const cyhal_adc_config_t joystic_config = {
    .continuous_scanning = true, 
    .resolution = 12, 
    .average_count = 1, 
    .average_mode_flags = 0,
    .ext_vref_mv = 0,
    .vneg = CYHAL_ADC_VNEG_VREF,
    .vref = CYHAL_ADC_REF_VDDA_DIV_2,
    .ext_vref = NC,
    .is_bypassed = false,
    .bypass_pin = NC
};

/* Public API */

/** Initialize the ADC channels connected to the Joystick
 *
 * @param - None
 */
void joystick_init(void)
{
    cy_rslt_t rslt;

    /* Initialize ADC.*/
    rslt = cyhal_adc_init(&joystick_adc_obj, PIN_ANALOG_JOY_X, NULL);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization, halt the MCU

    /* Set the Reference Voltage to be VDDA */
    rslt = cyhal_adc_configure(&joystick_adc_obj, &joystic_config);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization, halt the MCU


    /* Initialize X direction */
    rslt = cyhal_adc_channel_init_diff(
        &joystick_adc_chan_x_obj, 
        &joystick_adc_obj, 
        PIN_ANALOG_JOY_X, 
        CYHAL_ADC_VNEG, 
        &channel_config
    );
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization, halt the MCU


    /* Initialize Y direction */
    rslt = cyhal_adc_channel_init_diff(
        &joystick_adc_chan_y_obj, 
        &joystick_adc_obj, 
        PIN_ANALOG_JOY_Y, 
        CYHAL_ADC_VNEG, 
        &channel_config
    );
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization, halt the MCU

}

/** Read X direction of Joystick 
 *
 * @param - None
 */
uint16_t  joystick_read_x(void)
{
    /* ADD CODE */
    return cyhal_adc_read_u16(&joystick_adc_chan_x_obj);

    }

/** Read Y direction of Joystick 
 *
 * @param - None
 */
uint16_t  joystick_read_y(void)
{
    /* ADD CODE */
    return cyhal_adc_read_u16(&joystick_adc_chan_y_obj);
}


/* ADD CODE */
/**
 * @brief 
 * Returns the current position of the joystick 
 * @return joystick_position_t 
 */
joystick_position_t joystick_get_pos(void)
{
    uint16_t x = joystick_read_x();
    uint16_t y = joystick_read_y();
    if (x > JOYSTICK_THRESH_X_LEFT_2p7V && y > JOYSTICK_THRESH_Y_UP_2p7V) return JOYSTICK_POS_UPPER_LEFT;
    else if (x > JOYSTICK_THRESH_X_LEFT_2p7V && y < JOYSTICK_THRESH_Y_DOWN_0p6V) return JOYSTICK_POS_LOWER_LEFT;
    else if (x < JOYSTICK_THRESH_X_RIGHT_0p6V && y > JOYSTICK_THRESH_Y_UP_2p7V) return JOYSTICK_POS_UPPER_RIGHT;
    else if (x < JOYSTICK_THRESH_X_RIGHT_0p6V && y < JOYSTICK_THRESH_Y_DOWN_0p6V) return JOYSTICK_POS_LOWER_RIGHT;
    else if (x < JOYSTICK_THRESH_X_RIGHT_0p6V) return JOYSTICK_POS_RIGHT;
    else if (x > JOYSTICK_THRESH_X_LEFT_2p7V) return JOYSTICK_POS_LEFT;
    else if (y > JOYSTICK_THRESH_Y_UP_2p7V) return JOYSTICK_POS_UP;
    else if (y < JOYSTICK_THRESH_Y_DOWN_0p6V) return JOYSTICK_POS_DOWN;
    else return JOYSTICK_POS_CENTER;
}

/* ADD CODE */
/**
 * @brief 
 * Prints out a string to the console based on parameter passed 
 * @param position 
 * The enum value to be printed.
 */
void joystick_print_pos(joystick_position_t position)
{
    switch (position) {
        case JOYSTICK_POS_CENTER:
            printf("center\n");
            break;
        case JOYSTICK_POS_LEFT:
            printf("left\n");
            break;
        case JOYSTICK_POS_RIGHT:
            printf("right\n");
            break;
        case JOYSTICK_POS_UP:
            printf("up\n");
            break;
        case JOYSTICK_POS_DOWN:
            printf("down\n");
            break;
        case JOYSTICK_POS_UPPER_LEFT:
            printf("upper left\n");
            break;
        case JOYSTICK_POS_UPPER_RIGHT:
            printf("upper right\n");
            break;
        case JOYSTICK_POS_LOWER_LEFT:
            printf("lower left\n");
            break;
        case JOYSTICK_POS_LOWER_RIGHT:
            printf("lower right\n");
            break;
    }
}