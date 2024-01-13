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

    GPIO_TypeDef* DIR_port;
    uint16_t DIR_pin;
    
    /* PWM frequency for input */
    uint16_t lastPWM;

    /* Encoder information */
    const int encZero;
    
    
} DC_MTR;

// NOTE: http://www.disca.upv.es/aperles/arm_cortex_m3/llibre/st/STM32F439xx_User_Manual/group__tim__exported__macros.html#gac73f5e7669d92971830481e7298e98ba
// __HAL_TIM_IS_TIM_COUNTING_DOWN(__HANDLE__) can be used to tell if the counter is counting down or up

/* Initialisation functions */
DC_MTR* DC_MOTOR_init(TIM_HandleTypeDef* PWM_timer,
                   TIM_HandleTypeDef* ENC_timer,
                   uint32_t PWM_channel,
                   uint32_t encoder_channel,
                   GPIO_TypeDef* encA_port,
                   uint16_t encA_pin,
                   GPIO_TypeDef* encB_port,
                   uint16_t encB_pin,
                   uint16_t PWM_freq_min,
                   uint16_t PWM_freq_max,
                   GPIO_TypeDef* DIR_port,
                   uint16_t DIR_pin);


// Motor commands
void DC_MTR_setDutyCycle(DC_MTR* dc_mtr_ptr, float duty_cycle);
void DC_MTR_setDIR(DC_MTR* dc_mtr_ptr, int DIR_state);
void DC_MTR_swapDIR(DC_MTR* dc_mtr_ptr);
// void DC_MTR_setPWMFreq(DC_MTR* dc_mtr_ptr, float frequency);

// Encoder commands
int DC_MTR_getDIR(DC_MTR* dc_mtr_ptr);
// int DC_MTR_getPos(DC_MTR* dc_mtr_ptr);

#endif