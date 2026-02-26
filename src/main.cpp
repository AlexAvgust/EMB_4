#include <Arduino.h>
#include <esp_wifi.h>
#include <OneButton.h>
#include <display/display.h>
#include <wifi/wifi.h>
#include <button/button.h>
#include <ui/ui.h>
#include <globals.h>

#define MAX_WIFI_NETWORKS 10
#define RENDER_INTERVAL_MS 50  // Update graph every 50ms for smooth animation
#define WIDTH 240

// Global application state
WifiMonitorState state;
uint32_t lastRenderTick = 0;

// WiFi network storage
wifi_ap_record_t wifiNetworks[MAX_WIFI_NETWORKS];
uint16_t apCount = MAX_WIFI_NETWORKS;

// Button pin definitions
#define BTN_PIN_1 35  // Upper button (cycle networks)
#define BTN_PIN_2 0   // Lower button (select/view RSSI)

// Button objects with inverted logic (active low)
OneButton BTN_1(BTN_PIN_1, true);
OneButton BTN_2(BTN_PIN_2, true);

void setup()
{
    Serial.begin(115200);
    initWIFI();
    initDisplay();

    // Initialize WiFi history with invalid RSSI values
    // (-120 dBm is below normal range and used as a sentinel value)
    for (int i = 0; i < WIDTH; i++)
    {
        state.wifi_history[i] = -120;
    }

    showScanningMessage();

    // Setup event callbacks and initial state
    state.upperButtonCb = handleUpperButtonClick;
    state.lowerButtonCb = handleLowerButtonClick;
    state.index = 0;
    state.apCount = apCount;
    state.wifiNetworks = wifiNetworks;
    state.currentScreen = 0;  // Start in network list view

    // Perform initial WiFi network scan
    scanWifiNetworks(state.wifiNetworks, state.apCount);
    
    // Attach button click handlers
    BTN_1.attachClick(upperButtonClick, &state);
    BTN_2.attachClick(lowerButtonClick, &state);

    // Display scan results
    if (state.apCount != 0)
    {
        Serial.printf("Found %d WiFi networks\n", state.apCount);
        showAllFoundedWifiNetworks(state.wifiNetworks, state.apCount, state.index);
    }
}

void loop()
{
    // Process button inputs
    BTN_1.tick();
    BTN_2.tick();

    // Update RSSI graph in detailed view
    if (state.currentScreen == 1)
    {
        uint32_t currentMillis = millis();
        if (currentMillis - lastRenderTick >= RENDER_INTERVAL_MS)
        {
            lastRenderTick = currentMillis;
            
            // Get latest RSSI from WiFi sniffer
            int8_t rssi = getSelectedWifiNetworkRssi();
            
            // Update and display graph
            drawTargetNetwork(state.wifiNetworks[state.index], rssi, state.wifi_history);
        }
    }
}