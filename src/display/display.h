#include <esp_wifi.h>

#define WIDTH 240

void initDisplay();
void showAllFoundedWifiNetworks(wifi_ap_record_t *networks, uint16_t apCount, uint8_t selectedIndex);
void showScanningMessage();
void drawSelectedWifiNetworkNameRow(const wifi_ap_record_t &network);
void drawTargetNetwork(const wifi_ap_record_t &network, int8_t rssi, int (&wifi_history)[WIDTH]);
