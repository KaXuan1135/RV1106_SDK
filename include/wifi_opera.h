#ifndef WIFI_OPERA_H
#define WIFI_OPERA_H

#include <stdbool.h>


typedef enum {
	WIFI_AS_STATTION,
	WIFI_AS_AP,
}WIFI_WORK_MODE;

int wifi_set_work_mode(WIFI_WORK_MODE mode);

int wifi_set_node_name(char*name);

/* 取得wifi ap信息, 耗时2s 左右； 如果得到的AP 不够全面，可以多调用几次 */
int wifi_scan_info(char *buff, int max_len);


int wifi_connect_ap(char * ssid, char *passwd, int is_dhcp);


int wifi_disconnect_ap(void);


int wifi_remove_ap(char * ssid);


// for ap
int wifi_ap_start(char * ssid, char *passwd);

int wifi_ap_start_ex(char * ssid, char *passwd, int channel);
int wifi_ap_stop(void);
bool wifi_is_connected(void);



#endif
