#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#define USE_OPTIMIZE_PRINTF

#define __name__ "esp8266-lightstand"
#define __version__ "0.1.0"

#define PARAMS_DEFAULT_ZONE "dev"
#define PARAMS_DEFAULT_NAME __name__

#define PWM_PERIOD            2000
#define MAXDUTY               (1000*PWM_PERIOD/45)
#define LIGHT_INIT_DENSITY    0


// LED
#define LED_NUM                0
#define LED_FUNC               FUNC_GPIO0
#define LED_MUX                PERIPHS_IO_MUX_GPIO0_U     

#define LIGHT1                 0
#define LIGHT1_NUM		       2
#define LIGHT1_FUNC		       FUNC_GPIO2
#define LIGHT1_MUX             PERIPHS_IO_MUX_MTDO_U

#define LIGHT2                 1
#define LIGHT2_NUM		       3
#define LIGHT2_FUNC		       FUNC_GPIO3
#define LIGHT2_MUX             PERIPHS_IO_MUX_U0RXD_U

#define LIGHT3                 2
#define LIGHT3_NUM		       4
#define LIGHT3_FUNC		       FUNC_GPIO4
#define LIGHT3_MUX             PERIPHS_IO_MUX_GPIO4_U


#endif

