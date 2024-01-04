#include "dc_motor.h"


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
                   uint16_t PWM_freq_max)
{
    // Initialise a struct
    DC_MTR* dc_motor = NULL;

    dc_motor->PWM_timer = PWM_timer;
    dc_motor->ENC_timer = ENC_timer;
    dc_motor->PWM_channel = PWM_channel;
    dc_motor->encoder_channel = encoder_channel;
    dc_motor->encA_port = encA_port;
    dc_motor->encA_pin = encA_pin;
    dc_motor->encB_port = encB_port;
    dc_motor->encB_pin = encB_pin;

    dc_motor->PWM_freq_min = PWM_freq_min;
    dc_motor->PWM_freq_max = PWM_freq_max;


    return dc_motor;
}                   


void DC_MTR_setDutyCycle(DC_MTR* dc_mtr_ptr, float duty_cycle) {
	if (duty_cycle > 100) duty_cycle = 100;
	if (duty_cycle < 0) duty_cycle = 0;

	float pw_resolution = (((float)(*(dc_mtr_ptr->PWM_timer)).Init.Period + 1.0f) / 100.0f);

	uint16_t pw_desired = pw_resolution * duty_cycle;
	__HAL_TIM_SET_COMPARE(dc_mtr_ptr->PWM_timer, dc_mtr_ptr->ENC_timer, pw_desired); 
}