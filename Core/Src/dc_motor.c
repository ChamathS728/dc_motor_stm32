#include "dc_motor.h"


/* Initialisation functions */
DC_MTR* DC_MOTOR_init(TIM_HandleTypeDef* PWM_timer,
                      GPIO_TypeDef* PWM_port,
                      uint16_t PWM_pin,
                      uint32_t PWM_channel,
                      uint16_t PWM_freq_min,
                      uint16_t PWM_freq_max,
                      GPIO_TypeDef* DIR_port,
                      uint16_t DIR_pin)
{
    // Initialise a struct
    DC_MTR* dc_motor = NULL;

    
    dc_motor->PWM_timer = PWM_timer;
    dc_motor->PWM_channel = PWM_channel;

    dc_motor->PWM_freq_min = PWM_freq_min;
    dc_motor->PWM_freq_max = PWM_freq_max;

    dc_motor->current_duty_cycle = 0;
    dc_motor->PWM_resolution = 0;


    // Set the zero for the encoder upon initialisation by reading the current counter
    dc_motor->encZero = (ENC_timer->Instance->CNT) >> 2;

    return dc_motor;
}                   


void DC_MTR_setDutyCycle(DC_MTR* dc_mtr_ptr, float duty_cycle) {
	if (duty_cycle > 100) duty_cycle = 100;
	if (duty_cycle < 0) duty_cycle = 0;

	float pw_resolution = (((float)(*(dc_mtr_ptr->PWM_timer)).Init.Period + 1.0f) / 100.0f);

	uint16_t pw_desired = pw_resolution * duty_cycle;
    __HAL_TIM_SET_COMPARE(dc_mtr_ptr->PWM_timer, dc_mtr_ptr->PWM_timer->Channel, pw_desired);

    dc_mtr_ptr->current_duty_cycle = pw_desired;
    dc_mtr_ptr->PWM_resolution = pw_resolution;

    // Restart the PWM output
    HAL_TIM_PWM_Start(dc_mtr_ptr->PWM_timer, dc_mtr_ptr->PWM_timer->Channel);


    /*
    // Alternative implementation, not validated
    // Assumes that Timer 2 Channel 1 is used, with an ARR of 4 294 967 295
    if (duty_cycle > 100) duty_cycle = 100;
	if (duty_cycle < 0) duty_cycle = 0;

    TIM2->CCR1 = (duty_cycle * 4294967295)/100;
    */
}

void DC_MTR_setDIR(DC_MTR* dc_mtr_ptr, int DIR_state) {
    HAL_GPIO_WritePin(dc_mtr_ptr->DIR_port, dc_mtr_ptr->DIR_pin, DIR_state);
}
void DC_MTR_swapDIR(DC_MTR* dc_mtr_ptr) {
    // Toggle the direction pin
    HAL_GPIO_TogglePin(dc_mtr_ptr->DIR_port, dc_mtr_ptr->DIR_pin);
}

void DC_MTR_setPWMFreq(DC_MTR* dc_mtr_ptr, float frequency) {
    /*
    F_PWM = F_CLK / ((ARR + 1) x (PSC + 1))
    Solving for ARR assuming the prescaler PSC and clock frequency F_CLK is set

    ARR = F_CLK/(F_PWM x (PSC + 1)) - 1
    */
    
    // NOTE: Need to overwrite the auto-reload register which stores the counter Period
    // The smaller the value in the ARR register, the higher the frequency (and the lower the resolution)


    // dc_mtr_ptr->PWM_timer->Instance->ARR = (dc_mtr_ptr->PWM_timer->Instance->F_CLK)/(frequency * (dc_mtr_ptr->PWM_timer->Instance->PSC + 1)) - 1;
    __HAL_TIM_SET_AUTORELOAD(dc_mtr_ptr->PWM_timer, (dc_mtr_ptr->PWM_timer->Instance->F_CLK)/(frequency * (dc_mtr_ptr->PWM_timer->Instance->PSC + 1)) - 1);


    // Restart the PWM output
    HAL_TIM_PWM_Start(dc_mtr_ptr->PWM_timer, dc_mtr_ptr->PWM_timer->Channel);

// }

