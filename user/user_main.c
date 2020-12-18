
// Internal 
#include "user_config.h"
#include "partition.h"
#include "wifi.h"
#include "params.h" 
#include "debug.h"
#include "mdns.h"
#include "status.h"
#include "light.h"

// SDK
#include <ets_sys.h>
#include <osapi.h>
#include <mem.h>
#include <user_interface.h>
#include <driver/uart.h>
#include <upgrade.h>
#include <c_types.h>
#include <ip_addr.h> 


static Params params;
    


void statuscb() {
    INFO("WIFI Connected...\r\n");
    INFO("%s v"__version__" started\r\n", params.device_name);
}


void wifi_connect_cb(uint8_t status) {
    if(status == STATION_GOT_IP) {
        mdns_start(&params);
        status_update(200, 200, 1, statuscb);
    } else {
        espconn_mdns_close();
    }
}


void user_init(void) {
    //system_uart_swap();
    //uart_init(BIT_RATE_115200, BIT_RATE_115200);
    //os_delay_us(60000);
    
    uart_div_modify(UART0, UART_CLK_FREQ / BIT_RATE_115200);
    uart_rx_intr_disable(UART0);
    uart_rx_intr_disable(UART1);

    bool ok = params_load(&params);
    if (!ok) {
        ERROR("Cannot load Params\r\n");
#if !WIFI_ENABLE_SOFTAP
        return;
#endif
        if(!params_defaults(&params)) {
            ERROR("Cannot save params\r\n");
            return;
        }
    }
    
    params_print(&params);
    
    // Disable wifi led before infrared
    wifi_status_led_uninstall();

    // Status LED
    status_init();

    status_update(100, 100, 0, NULL);
    wifi_start(&params, wifi_connect_cb);

    webadmin_start(&params);
    
    light_init();
}


void ICACHE_FLASH_ATTR user_pre_init(void)
{
    if(!system_partition_table_regist(at_partition_table, 
                sizeof(at_partition_table)/sizeof(at_partition_table[0]),
                SPI_FLASH_SIZE_MAP)) {
        FATAL("system_partition_table_regist fail\r\n");
        while(1);
    }
}

