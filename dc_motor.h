#ifndef DC_MOTOR_STM32_H
#define DC_MOTOR_STM32_H

#include <stdio.h>
#include "stm32l4xx_hal.h"


/* Structs */
typedef struct DC_MTR {
    
    /* Port and pin information */
    GPIO_TypeDef* encA_port;
    uint16_t encA_pin;

    GPIO_TypeDef* encB_port;
    uint16_t encB_pin;

    TIM_HandleTypeDef* PWM_timer;
    TIM_HandleTypeDef* ENC_timer;
    uint32_t PWM_channel;
    uint32_t encoder_channel;

    /* Motor driver specific information */
    uint16_t PWM_freq_min;
    uint16_t PWM_freq_max;

    
    /* PWM frequency for input */
    uint16_t lastPWM;

    
    
} DC_MTR;

/* Initialisation functions */
DC_MOTOR* DC_MOTOR_init(TIM_HandleTypeDef* PWM_timer,
                   TIM_HandleTypeDef* ENC_timer,
                   uint32_t PWM_channel,
                   uint32_t encoder_channel,
                   GPIO_TypeDef* encA_port,
                   uint16_t encA_pin,
                   GPIO_TypeDef* encB_port,
                   uint16_t encB_pin,
                   uint16_t PWM_freq_min,
                   uint16_t PWM_freq_max);

void DC_MTR_setDutyCycle(DC_MTR* dc_mtr_ptr, float duty_cycle);

#endif