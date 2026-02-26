# WiFi RSSI Analyzer

A portable WiFi signal strength analyzer built on ESP32 with a TFT display. Monitor real-time RSSI (Received Signal Strength Indicator) values from nearby WiFi networks with a visual graph.

## Features

- **WiFi Network Scanning**: Automatically scans and lists nearby WiFi networks
- **Real-time RSSI Monitoring**: Captures live RSSI values from selected networks using WiFi promiscuous mode
- **Visual Graph**: Displays RSSI history as a scrolling line graph with dBm scale
- **Physical Controls**: Two-button interface for navigation and selection
- **Compact Display**: ST7789 TFT display (135x240) shows network list and detailed RSSI graphs

## Hardware Requirements

- **Microcontroller**: ESP32 (ESP32-WROOM or similar)
- **Display**: ST7789 TFT LCD (135x240 pixels)
- **Buttons**: 2x push buttons
- **Connections**:
  - Display SPI: MOSI=GPIO19, SCLK=GPIO18, CS=GPIO5, DC=GPIO16, RST=GPIO23, BL=GPIO4
  - Buttons: Button 1=GPIO35, Button 2=GPIO0

## Dependencies

- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) - Display driver
- [OneButton](https://github.com/mathertel/OneButton) - Button handling

## Building & Uploading

1. Install [PlatformIO](https://platformio.org/)
2. Clone or download this project
3. Configure display pins in `platformio.ini` if different from defaults
4. Build and upload:
   ```bash
   pio run -t upload
   ```

## Testing

Comprehensive unit tests are included using Google Test framework. Tests cover WiFi scanning, RSSI monitoring, display rendering, and UI logic.

Run all tests:
```bash
pio test -e native_test
```

See [test/TEST_DOCUMENTATION.md](test/TEST_DOCUMENTATION.md) for detailed test information and coverage.

## Usage

1. **Power on** the device - it will automatically scan for WiFi networks
2. **Upper Button**: Cycle through available WiFi networks
3. **Lower Button**: Enter detailed view for the selected network
4. **In Detail View**: Press buttons to switch back to network list
   - Shows real-time RSSI graph with history
   - Graph updates every 50ms
   - Scale: -120 to -30 dBm

## How It Works

### WiFi Scanning
- Uses ESP32's WiFi APIs to scan available networks
- Stores up to 20 networks with SSID, BSSID, and initial RSSI

### RSSI Monitoring
- Enables WiFi promiscuous mode to capture all packets
- Filters packets by target network's BSSID
- Extracts RSSI value from packet metadata
- Updates at high frequency for smooth graph rendering

### Display System
- Uses sprite graphics for efficient rendering
- 50ms update interval prevents excessive CPU usage
- Fixed aspect ratio graph (240x105 pixels)

## Project Structure

```
src/
  ├── main.cpp           - Main application logic and event loop
  ├── globals.h          - Shared data structures (WifiMonitorState)
  ├── wifi/              - WiFi scanning and RSSI monitoring
  ├── display/           - TFT display control and drawing
  ├── ui/                - Button event handlers
  ├── button/            - Button input processing
  └── espnow/            - ESP-NOW protocol support (optional)
```

## License

Open source - feel free to modify and use for your own projects!
