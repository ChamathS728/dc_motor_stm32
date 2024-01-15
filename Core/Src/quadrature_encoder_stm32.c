/*
 * quadrature_encoder_stm32.c
 *
 *  Created on: Jan 14, 2024
 *      Author: chama
 */

#include "quadrature_encoder_stm32.h"
// #ifndef ABSTRACT
//     // NOTE: only do this if we want as much code abstracted as possible
//     // Init function should be after MX_TIM_INIT has been called from autogenerated code
    
//     // Start the encoder timer itself
//     HAL_TIM_Encoder_Start(ENC_timer, TIM_CHANNEL_ALL);

//     // Start the PWM timer
//     HAL_TIM_PWM_Start(PWM_timer, PWM_channel); // eg: do TIM_CHANNEL_1 for Channel 1 PWM generation

// #endif


QUAD_ENC* QUAD_ENC_init(TIM_HandleTypeDef* ENC_timer,
                        uint32_t encoder_channel,
                        GPIO_TypeDef* encA_port,
                        uint16_t encA_pin,
                        GPIO_TypeDef* encB_port,
                        uint16_t encB_pin,
                        int enc_res)
{
    QUAD_ENC* quad_enc_ptr;
    quad_enc_ptr->ENC_timer = ENC_timer;
    quad_enc_ptr->encoder_channel = encoder_channel;

    quad_enc_ptr->encA_port = encA_port;
    quad_enc_ptr->encA_pin = encA_pin;

    quad_enc_ptr->encB_port = encB_port;
    quad_enc_ptr->encB_pin = encB_pin;    

    quad_enc_ptr->enc_res = enc_res;

    return quad_enc_ptr;
}

// Encoder commands
int DC_MTR_getDIR(DC_MTR* dc_mtr_ptr) {
    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(dc_mtr_ptr->ENC_timer)) {
        return 0;
    }
    else {
        return 1;
    }
}

int DC_MTR_getPos(QUAD_ENC* quad_enc_ptr) {
    uint32_t counter = __HAL_TIM_GET_COUNTER(quad_enc_ptr->ENC_timer);

    int16_t pos = counter/4 * quad_enc_ptr->enc_res;
}