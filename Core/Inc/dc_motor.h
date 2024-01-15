#ifndef DC_MOTOR_STM32_H
#define DC_MOTOR_STM32_H

#include <stdio.h>
#include "stm32l4xx_hal.h"


/* Structs */
typedef struct DC_MTR {
    
    /* Port and pin information */
    TIM_HandleTypeDef* PWM_timer;
    uint32_t PWM_channel;

    /* Motor driver specific information - fixed when initialised */
    uint16_t PWM_freq_min;
    uint16_t PWM_freq_max;

    GPIO_TypeDef* DIR_port;
    uint16_t DIR_pin;

    GPIO_TypeDef* PWM_port;
    uint16_t PWM_pin;
    
    /* Variables to be edited with usage */
    uint16_t current_duty_cycle;
    float PWM_resolution;


} DC_MTR;


/* Initialisation functions */
DC_MTR* DC_MOTOR_init(TIM_HandleTypeDef* PWM_timer,
                      GPIO_TypeDef* PWM_port,
                      uint16_t PWM_pin,
                      uint32_t PWM_channel,
                      uint16_t PWM_freq_min,
                      uint16_t PWM_freq_max,
                      GPIO_TypeDef* DIR_port,
                      uint16_t DIR_pin);


// Motor commands
void DC_MTR_setDutyCycle(DC_MTR* dc_mtr_ptr, float duty_cycle);
void DC_MTR_setDIR(DC_MTR* dc_mtr_ptr, int DIR_state);
void DC_MTR_swapDIR(DC_MTR* dc_mtr_ptr);
int DC_MTR_getDIR(DC_MTR* dc_mtr_ptr);
// void DC_MTR_setPWMFreq(DC_MTR* dc_mtr_ptr, float frequency);



#endif