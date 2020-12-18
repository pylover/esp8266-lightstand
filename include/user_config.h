#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

#include <eagle_soc.h>

#define __version__     "0.1.0"

#define USE_OPTIMIZE_PRINTF
#define WIFI_ENABLE_SOFTAP  true


#define PWM_PERIOD            2000
#define MAXDUTY               (1000*PWM_PERIOD/45)
#define LIGHT_INIT_DENSITY    (MAXDUTY / 10)


// LED
#define LED_MUX                PERIPHS_IO_MUX_GPIO0_U     
#define LED_NUM                0
#define LED_FUNC               FUNC_GPIO0

#define LIGHT1                 0
#define LIGHT1_MUX             PERIPHS_IO_MUX_MTDO_U
#define LIGHT1_NUM		       2
#define LIGHT1_FUNC		       FUNC_GPIO2

#define LIGHT2                 1
#define LIGHT2_MUX             PERIPHS_IO_MUX_U0RXD_U
#define LIGHT2_NUM		       3
#define LIGHT2_FUNC		       FUNC_GPIO3

//#define LIGHT3           2
//#define LIGHT3_MUX       PERIPHS_IO_MUX_MTCK_U
//#define LIGHT3_NUM		 13
//#define LIGHT3_FUNC		 FUNC_GPIO13

#endif

/*
#define PERIPHS_IO_MUX_MTDI_U           (PERIPHS_IO_MUX + 0x04)
#define FUNC_GPIO12                     3
#define PERIPHS_IO_MUX_MTCK_U           (PERIPHS_IO_MUX + 0x08)
#define FUNC_GPIO13                     3
#define PERIPHS_IO_MUX_MTMS_U           (PERIPHS_IO_MUX + 0x0C)
#define FUNC_GPIO14                     3
#define PERIPHS_IO_MUX_MTDO_U           (PERIPHS_IO_MUX + 0x10)
#define FUNC_GPIO15                     3
#define FUNC_U0RTS                      4
#define PERIPHS_IO_MUX_U0RXD_U          (PERIPHS_IO_MUX + 0x14)
#define FUNC_GPIO3                      3
#define PERIPHS_IO_MUX_U0TXD_U          (PERIPHS_IO_MUX + 0x18)
#define FUNC_U0TXD                      0
#define FUNC_GPIO1                      3
#define PERIPHS_IO_MUX_SD_CLK_U         (PERIPHS_IO_MUX + 0x1c)
#define FUNC_SDCLK                      0
#define FUNC_SPICLK                     1
#define PERIPHS_IO_MUX_SD_DATA0_U       (PERIPHS_IO_MUX + 0x20)
#define FUNC_SDDATA0                    0
#define FUNC_SPIQ                       1
#define FUNC_U1TXD                      4
#define PERIPHS_IO_MUX_SD_DATA1_U       (PERIPHS_IO_MUX + 0x24)
#define FUNC_SDDATA1                    0
#define FUNC_SPID                       1
#define FUNC_U1RXD                      4
#define FUNC_SDDATA1_U1RXD              7
#define PERIPHS_IO_MUX_SD_DATA2_U       (PERIPHS_IO_MUX + 0x28)
#define FUNC_SDDATA2                    0
#define FUNC_SPIHD                      1
#define FUNC_GPIO9                      3
#define PERIPHS_IO_MUX_SD_DATA3_U       (PERIPHS_IO_MUX + 0x2c)
#define FUNC_SDDATA3                    0
#define FUNC_SPIWP                      1
#define FUNC_GPIO10                     3
#define PERIPHS_IO_MUX_SD_CMD_U         (PERIPHS_IO_MUX + 0x30)
#define FUNC_SDCMD                      0
#define FUNC_SPICS0                     1
#define PERIPHS_IO_MUX_GPIO0_U          (PERIPHS_IO_MUX + 0x34)
#define FUNC_GPIO0                      0
#define PERIPHS_IO_MUX_GPIO2_U          (PERIPHS_IO_MUX + 0x38)
#define FUNC_GPIO2                      0
#define FUNC_U1TXD_BK                   2
#define FUNC_U0TXD_BK                   4
#define PERIPHS_IO_MUX_GPIO4_U          (PERIPHS_IO_MUX + 0x3C)
#define FUNC_GPIO4                      0
#define PERIPHS_IO_MUX_GPIO5_U          (PERIPHS_IO_MUX + 0x40)
#define FUNC_GPIO5                      0
*/
