
#include "mdns.h"
#include "user_config.h"

#include <espconn.h>


static struct mdns_info mdns;


ICACHE_FLASH_ATTR 
void mdns_start(Params *params) {
    struct ip_info ipconfig;
    wifi_set_broadcast_if(STATIONAP_MODE);
    wifi_get_ip_info(STATION_IF, &ipconfig);
    mdns.ipAddr = ipconfig.ip.addr; //ESP8266 Station IP
    mdns.host_name = params->device_name;
    mdns.server_name = params->device_name;
    mdns.server_port = 80;
    mdns.txt_data[0] = "version = "__version__;
    espconn_mdns_init(&mdns);
}
