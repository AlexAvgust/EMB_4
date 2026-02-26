#pragma once
#include "esp_wifi.h"

#define WIDTH 240

struct WifiMonitorState; 

// Function pointer type for button event callbacks
typedef void (*ButtonClickCb)(WifiMonitorState *state);

// Central state structure for the entire application
// Stores the current UI view, selected network, RSSI history, and callbacks
struct WifiMonitorState {
    uint8_t index;                              // Currently selected network index
    wifi_ap_record_t *wifiNetworks;             // Pointer to network array
    uint16_t apCount;                           // Number of discovered networks
    ButtonClickCb upperButtonCb = nullptr;      // Upper button click handler
    ButtonClickCb lowerButtonCb = nullptr;      // Lower button click handler
    uint8_t currentScreen;                      // 0=network list, 1=RSSI graph view
    wifi_ap_record_t selectedNetwork;           // Details of selected network
    int8_t rssi;                                // Current RSSI value
    int wifi_history[WIDTH];                    // RSSI history for graph (scrolling buffer)
};
