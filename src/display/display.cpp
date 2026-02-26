#include <Arduino.h>
#include <TFT_eSPI.h>
#include <esp_wifi.h>

#define WIDTH 240
#define HEIGHT 135
#define GRAPH_HEIGHT 105
#define BOTTOM_Y 135

TFT_eSPI TFT = TFT_eSPI();
TFT_eSprite graph = TFT_eSprite(&TFT);

const int lineHeight = 16;

void initDisplay()
{
    TFT.init();
    TFT.setRotation(1); 
    graph.createSprite(WIDTH, GRAPH_HEIGHT);
}

void showScanningMessage()
{
    const char *msg = "Scanning for WiFi networks...";
    TFT.fillScreen(TFT_BLACK);

    TFT.setTextSize(1);
    TFT.setTextColor(TFT_WHITE, TFT_BLACK);

    int16_t tw = TFT.textWidth(msg);
    int16_t x = (TFT.width() - tw) / 2;
    int16_t y = (TFT.height() - lineHeight) / 2;

    TFT.drawString(msg, x, y);
    delay(100);
}

void drawWifiRow(const wifi_ap_record_t &network, int rowIndex, bool isSelected)
{
    // Skip empty network slots
    if (network.ssid[0] == 0) return;

    // Highlight selected network with blue background
    uint16_t bgColor = isSelected ? TFT_BLUE : TFT_BLACK;
    uint16_t fgColor = TFT_WHITE;

    int yPos = rowIndex * lineHeight;

    // Draw background rectangle for the row
    TFT.fillRect(0, yPos, TFT.width(), lineHeight, bgColor);

    TFT.setTextColor(fgColor, bgColor);
    TFT.setTextSize(1);

    // Draw network SSID (name)
    const char *ssid = (const char *)network.ssid;
    TFT.drawString(ssid, 0, yPos);

    // Draw RSSI value (signal strength) right-aligned
    char rssiStr[16];
    snprintf(rssiStr, sizeof(rssiStr), "%d dBm", network.rssi);

    int16_t tw = TFT.textWidth(rssiStr);
    int16_t x = TFT.width() - tw - 2;
    TFT.drawString(rssiStr, x, yPos);
}

void showAllFoundedWifiNetworks(wifi_ap_record_t *networks, uint16_t apCount, uint8_t selectedIndex)
{
    TFT.fillScreen(TFT_BLACK); 

    for (int i = 0; i < apCount; i++)
    {
        drawWifiRow(networks[i], i, (i == selectedIndex));
    }
}

void updateWifiListSelection(wifi_ap_record_t *networks, uint8_t oldIndex, uint8_t newIndex)
{
    drawWifiRow(networks[oldIndex], oldIndex, false);
    drawWifiRow(networks[newIndex], newIndex, true);
}

void drawWifiGraph(int current_rssi, int (&wifi_history)[WIDTH])
{
    // Shift history buffer left and add new RSSI value at the end
    // This creates a scrolling graph effect
    memmove(&wifi_history[0], &wifi_history[1], (WIDTH - 1) * sizeof(int));
    wifi_history[WIDTH - 1] = current_rssi;

    graph.fillSprite(TFT_BLACK);

    // Draw horizontal grid lines at 20 dBm intervals with labels
    for (int i = -100; i <= -20; i += 20)
    {
        int y = map(i, -120, -30, GRAPH_HEIGHT - 1, 0);
        graph.drawFastHLine(0, y, WIDTH, TFT_DARKGREY);
        graph.setTextColor(TFT_LIGHTGREY);
        graph.drawString(String(i), 2, y > 10 ? y - 10 : y, 1);
    }

    // Draw line connecting RSSI values
    // Only draws between valid points (-120 is initial/invalid value)
    for (int i = 0; i < WIDTH - 1; i++)
    {
        if (wifi_history[i] > -120 && wifi_history[i + 1] > -120)
        {
            int x1 = i;
            int y1 = map(wifi_history[i], -120, -30, GRAPH_HEIGHT - 1, 0);
            int x2 = i + 1;
            int y2 = map(wifi_history[i + 1], -120, -30, GRAPH_HEIGHT - 1, 0);
            graph.drawLine(x1, y1, x2, y2, TFT_GREEN);
        }
    }
    
    // Push sprite to display (at Y offset 30 for title area)
    graph.pushSprite(0, 30); 
}

void drawSelectedWifiNetworkNameRow(const wifi_ap_record_t &network)
{
    TFT.fillRect(0, 0, WIDTH, 30, TFT_BLACK); 
    
    TFT.setTextColor(TFT_WHITE);
    TFT.setTextSize(1);
    char buf[64];
    snprintf(buf, sizeof(buf), "Selected WiFi Network: %s", (const char *)network.ssid);
    TFT.drawString(buf, 0, 0);
}

void drawTargetNetwork(const wifi_ap_record_t &network, int8_t rssi, int (&wifi_history)[WIDTH])
{
    drawSelectedWifiNetworkNameRow(network);
    drawWifiGraph(rssi, wifi_history);
}