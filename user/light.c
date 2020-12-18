#include "user_config.h"
#include "light.h"
#include "debug.h"

#include <osapi.h>
#include <c_types.h>
#include <pwm.h>



ICACHE_FLASH_ATTR
void light_density(uint8_t c, uint32_t v) {
    DEBUG("Duty: %d\n", v);
    pwm_set_duty(v , c);
    pwm_start();
}

#define PWM_CHANNELS    2

ICACHE_FLASH_ATTR
void light_init() {
   	uint32 pwmioinfo[][3] = {
        {LIGHT1_MUX, LIGHT1_FUNC, LIGHT1_NUM},
        {LIGHT2_MUX, LIGHT2_FUNC, LIGHT2_NUM},
   //     {LIGHT3_MUX, LIGHT3_FUNC, LIGHT3_NUM},
    };
 
    uint32 pwmdutyinit[PWM_CHANNELS] = {
        LIGHT_INIT_DENSITY, 
        LIGHT_INIT_DENSITY, 
    };
    pwm_init(PWM_PERIOD, pwmdutyinit, PWM_CHANNELS, pwmioinfo);
    os_delay_us(1000);
    //light_density(LIGHT1, LIGHT_INIT_DENSITY);
    //light_density(LIGHT2, LIGHT_INIT_DENSITY);
    //light_density(LIGHT3, LIGHT_INIT_DENSITY);
    pwm_start();
}
