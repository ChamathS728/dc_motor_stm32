/*
 * quadrature_encoder_stm32.h
 *
 *  Created on: Jan 14, 2024
 *      Author: chama
 */

#ifndef DC_MOTOR_STM32_H
#define DC_MOTOR_STM32_H

#include <stdio.h>
#include "stm32l4xx_hal.h"


typedef struct QUAD_ENC {
    /* Port and pin information */
    GPIO_TypeDef* encA_port;
    uint16_t encA_pin;

    GPIO_TypeDef* encB_port;
    uint16_t encB_pin;

    /* STM32 specific handles */
    TIM_HandleTypeDef* ENC_timer;
    uint32_t encoder_channel;

    /* Encoder information */
    const int encZero;

} QUAD_ENC;

/* Initialisation functions */
QUAD_ENC* QUAD_ENC_init(TIM_HandleTypeDef* ENC_timer,
                        uint32_t encoder_channel,
                        GPIO_TypeDef* encA_port,
                        uint16_t encA_pin,
                        GPIO_TypeDef* encB_port,
                        uint16_t encB_pin);

// NOTE: http://www.disca.upv.es/aperles/arm_cortex_m3/llibre/st/STM32F439xx_User_Manual/group__tim__exported__macros.html#gac73f5e7669d92971830481e7298e98ba
// __HAL_TIM_IS_TIM_COUNTING_DOWN(__HANDLE__) can be used to tell if the counter is counting down or up

/* Encoder commands */
int QUAD_ENC_getDIR(QUAD_ENC* quad_enc_ptr);
int QUAD_ENC_getPos(QUAD_ENC* quad_enc_ptr);


#endif