#include "user_config.h"
#include "light.h"
#include "debug.h"

#include <osapi.h>
#include <c_types.h>
#include <pwm.h>

ICACHE_FLASH_ATTR
uint8_t light_density_get(uint8_t c) {
    uint32_t v = pwm_get_duty(c);
    v = v * 100 / MAXDUTY;
    return v;
}



ICACHE_FLASH_ATTR
void light_density_all(uint32_t v) {
    uint32_t duty = v * MAXDUTY / 100;
    pwm_set_duty(duty, LIGHT1);
    pwm_set_duty(duty, LIGHT2);
    //pwm_set_duty(duty, LIGHT3);
    pwm_start();
}


ICACHE_FLASH_ATTR
void light_density(uint8_t c, uint32_t v) {
    DEBUG("CH: %u, %u", c, v);
    uint32_t duty = v * MAXDUTY / 100;
    pwm_set_duty(duty, c);
    pwm_start();
}

#define PWM_CHANNELS    3

ICACHE_FLASH_ATTR
void light_init() {
    /* PWM will not work with less than 3 channels,
     * So the third channel is dummy here.
     */
   	uint32 pwmioinfo[][3] = {
        {LIGHT1_MUX, LIGHT1_FUNC, LIGHT1_NUM},
        {LIGHT2_MUX, LIGHT2_FUNC, LIGHT2_NUM},
        {LIGHT3_MUX, LIGHT3_FUNC, LIGHT3_NUM},
    };
 
    uint32 pwmdutyinit[PWM_CHANNELS] = {
        LIGHT_INIT_DENSITY, 
        LIGHT_INIT_DENSITY, 
        LIGHT_INIT_DENSITY, 
    };
    pwm_init(PWM_PERIOD, pwmdutyinit, PWM_CHANNELS, pwmioinfo);
    os_delay_us(1000);
    pwm_start();
}

