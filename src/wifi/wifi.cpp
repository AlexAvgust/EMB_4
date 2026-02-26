#include <Arduino.h>
#include <esp_wifi.h>
#include "nvs_flash.h"
#include <wifi/wifi.h>

#define MAX_WIFI_NETWORKS 20

// Target network BSSID (MAC address) for RSSI monitoring
uint8_t target_bssid[6] = {0};

// Current RSSI value from sniffer (volatile due to interrupt context)
volatile int8_t target_rssi = -127;

// Callback for WiFi promiscuous mode packet reception
// Extracts RSSI from packets matching the target network's BSSID
void wifi_sniffer_packet_handler(void *buff, wifi_promiscuous_pkt_type_t type)
{
    // Only process management frames (beacon, probe response, etc.)
    if (type != WIFI_PKT_MGMT) return;

    wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buff;
    mac_header_t *mac_hdr = (mac_header_t *)pkt->payload;

    // Check if packet is from our target network (MAC address match)
    if (memcmp(mac_hdr->addr2, target_bssid, 6) == 0)
    {
        // Extract RSSI (signal strength) from packet metadata
        target_rssi = pkt->rx_ctrl.rssi;
    }
}

void initWIFI()
{
    // Initialize NVS (Non-Volatile Storage) for WiFi configuration
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        // Erase and reinitialize NVS if corrupted
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize WiFi with default configuration
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Start WiFi in monitor mode (no connection needed)
    ESP_ERROR_CHECK(esp_wifi_start());
    
    // Enable promiscuous mode to capture all WiFi packets
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous(true));
    
    // Register callback to process captured packets
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous_rx_cb(&wifi_sniffer_packet_handler));
}


void scanWifiNetworks(wifi_ap_record_t *networks, uint16_t &count)
{
    // Configure WiFi scan parameters
    wifi_scan_config_t scan_config = {
        .show_hidden = false,
        .scan_type = WIFI_SCAN_TYPE_ACTIVE,
    };

    // Perform synchronous WiFi scan (blocks until complete)
    esp_err_t err = esp_wifi_scan_start(&scan_config, true);
    if (err != ESP_OK)
    {
        Serial.printf("esp_wifi_scan_start failed: %d\n", err);
        count = 0;
        return;
    }

    // Get total number of networks found
    uint16_t number = 0;
    esp_wifi_scan_get_ap_num(&number);
    
    // Limit to array size to prevent buffer overflow
    count = (number > MAX_WIFI_NETWORKS) ? MAX_WIFI_NETWORKS : number;

    if (count == 0)
    {
        Serial.println("No WiFi networks found.");
        return;
    }

    // Retrieve network records into the provided buffer
    esp_err_t res = esp_wifi_scan_get_ap_records(&count, networks);
    if (res != ESP_OK)
    {
        Serial.printf("esp_wifi_scan_get_ap_records failed: %d\n", res);
        return;
    }
    Serial.printf("WiFi scan complete: %u AP(s) found\n", count);
}

int8_t getSelectedWifiNetworkRssi()
{
    return target_rssi;
}


void setTargetNetwork(const wifi_ap_record_t &network)
{
    // Copy target network's MAC address for packet filtering
    memcpy(target_bssid, network.bssid, 6);
    
    // Lock WiFi radio to the target network's channel for better RSSI accuracy
    esp_wifi_set_channel(network.primary, network.second);
    
    // Initialize RSSI with the scan value (will be updated by sniffer)
    target_rssi = network.rssi;
    Serial.printf("Selected WiFi Network: %s, with rssi %d\n", network.ssid, target_rssi);
}