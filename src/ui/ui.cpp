#include <Arduino.h>
#include <button/button.h>
#include <display/display.h>
#include <wifi/wifi.h>
#include <globals.h>

// Upper button handler: cycle to next WiFi network
// Only works in network list view (currentScreen == 0)
void handleUpperButtonClick(WifiMonitorState* s) {
    if (s->apCount == 0 || s->currentScreen == 1) return;

    int oldIndex = s->index;
    // Wrap around to first network when reaching the end
    s->index = (oldIndex + 1) % s->apCount;
    
    // Update display to show new selection
    updateWifiListSelection(s->wifiNetworks, oldIndex, s->index);
}

// Lower button handler: enter detailed RSSI view for selected network
// Only works in network list view (currentScreen == 0)
void handleLowerButtonClick(WifiMonitorState* s) {
    if (s->apCount == 0 || s->currentScreen == 1) return;

    // Switch to detailed RSSI graph view
    s->currentScreen = 1;

    // Configure WiFi sniffer for the selected network
    setTargetNetwork(s->wifiNetworks[s->index]);
    
    // Display initial graph screen
    drawTargetNetwork(s->wifiNetworks[s->index], s->rssi, s->wifi_history);
}
