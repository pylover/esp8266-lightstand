#include "params.h"
#include "httpserver.h"
#include "multipart.h"
#include "querystring.h"

#include <osapi.h>
#include <upgrade.h>
#include <mem.h>


#define FAVICON_SIZE    495
#define FAVICON_FLASH_SECTOR    0x200    
#define HTML_HEADER \
    "<!DOCTYPE html><html>" \
    "<head>" \
    "<title>Power Amplifier</title>" \
    "</head><body>\r\n" 

#define HTML_FOOTER "\r\n</body></html>\r\n"

#define HTML_INDEX \
    HTML_HEADER \
    "<h4>Welcome to Power Amplifier Web Administration</h4><br />" \
    HTML_FOOTER

static char h1[32] = {"Access-Control-Allow-Origin: *\0"};
static char h2[128] = {
    "Access-Control-Allow-Methods: FOTA, GET, MUTE, UNMUTE, NEXT, " \
     "PREVIOUS, OPTIONS, PLAYPAUSE\0"
};
#define RESPONSEHEADERSCOUNT 2
static char * responseheaders[RESPONSEHEADERSCOUNT] = {h1, h2};

#define httpresponse(req, status, type, content, content_length) \
    httpserver_response(req, status, type, content, content_length, \
            responseheaders, RESPONSEHEADERSCOUNT)

#define httpresponse_text(req, status, content, content_length) \
    httpresponse(req, status, HTTPHEADER_CONTENTTYPE_TEXT, content, \
            content_length)

#define httpresponse_html(req, status, content, content_length) \
    httpresponse(req, status, HTTPHEADER_CONTENTTYPE_HTML, content, \
            content_length)


static ETSTimer ff;

#define RB_BUFFSIZE       (2048 * 3)

static ICACHE_FLASH_ATTR
void all_set(Request *req, char *body, uint32_t length, uint32_t more) {
   uint32_t density = atoi(body);
   light_density_all(density);
   httpresponse_text(req, HTTPSTATUS_OK, NULL, NULL);
}


static ICACHE_FLASH_ATTR
void light1_set(Request *req, char *body, uint32_t length, uint32_t more) {
   uint32_t density = atoi(body);
   light_density(LIGHT1, density);
   httpresponse_text(req, HTTPSTATUS_OK, NULL, NULL);
}


static ICACHE_FLASH_ATTR
void light2_set(Request *req, char *body, uint32_t body_length, 
        uint32_t more) {
   uint32_t density = atoi(body);
   light_density(LIGHT2, density);
   httpresponse_text(req, HTTPSTATUS_OK, NULL, NULL);
}


static ICACHE_FLASH_ATTR
void fota_reboot(Request *req, char *body, uint32_t body_length, 
        uint32_t more) {
    char buffer[256];
    system_upgrade_flag_set(UPGRADE_FLAG_FINISH);
    int len = os_sprintf(buffer, "Rebooting to fota mode...\r\n");
    httpresponse_text(req, HTTPSTATUS_OK, buffer, len);
    os_delay_us(2000);
    system_upgrade_reboot();
}


static ICACHE_FLASH_ATTR
void webadmin_favicon(Request *req, char *body, uint32_t body_length, 
        uint32_t more) {
    
    char buffer[4 * 124];
    int result = spi_flash_read(
            FAVICON_FLASH_SECTOR * SPI_FLASH_SEC_SIZE,
            (uint32_t*) buffer,
            4 * 124
        );
    if (result != SPI_FLASH_RESULT_OK) {
        os_printf("SPI Flash write failed: %d\r\n", result);
        httpserver_response_notok(req, HTTPSTATUS_SERVERERROR);
        return;
    }
    httpserver_response(req, HTTPSTATUS_OK, "image/x-icon", buffer, 495, 
            NULL, 0);
}


static ICACHE_FLASH_ATTR
void webadmin_options(Request *req, char *body, uint32_t body_length, 
        uint32_t more) {
    httpresponse_html(req, HTTPSTATUS_OK, NULL, 0);
}


static ICACHE_FLASH_ATTR
void webadmin_index(Request *req, char *body, uint32_t body_length, 
        uint32_t more) {
    char buffer[1024];
    int len = os_sprintf(buffer, HTML_INDEX);
    httpresponse_html(req, HTTPSTATUS_OK, buffer, len);
}


static HttpRoute routes[] = {
    {"SET",       "/",            all_set            },
    {"SET",       "/1",           light1_set         },
    {"SET",       "/2",           light2_set         },
    {"FOTA",      "/",            fota_reboot        },
    {"OPTIONS",   "/",            webadmin_options   },
    {"GET",       "/",            webadmin_index     },
    {"GET",       "/favicon.ico", webadmin_favicon   },
    { NULL }
};


int ICACHE_FLASH_ATTR
webadmin_start() {
    httpserver_init(80, routes);
    return OK;
}


void ICACHE_FLASH_ATTR
webadmin_stop() {
    httpserver_stop();
}

