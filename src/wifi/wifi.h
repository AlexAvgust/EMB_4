#include <esp_wifi.h>

typedef struct
{
    uint16_t frame_ctrl;
    uint16_t duration;
    uint8_t addr1[6];
    uint8_t addr2[6];
    uint8_t addr3[6];
} mac_header_t;

void scanWifiNetworks(wifi_ap_record_t *networks, uint16_t &count);
int8_t getSelectedWifiNetworkRssi();
void initWIFI();
void setTargetNetwork(const wifi_ap_record_t &network);
void updateWifiListSelection(wifi_ap_record_t *networks, uint8_t oldIndex, uint8_t newIndex);