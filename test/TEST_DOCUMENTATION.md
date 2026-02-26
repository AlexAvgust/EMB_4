# WiFi RSSI Analyzer - Test Suite Documentation

## Overview

This project includes a comprehensive unit test suite built with Google Test (GTest) framework. The tests cover critical functionality for WiFi scanning, RSSI monitoring, display operations, and UI state management.

## Test Categories

### 1. WiFi Module Tests (`WiFiUtilityTests`)

Tests for WiFi functionality including BSSID management, RSSI tracking, and network discovery.

- **SetTargetBSSID**: Verifies target network MAC address storage
- **SetTargetRSSI**: Validates RSSI value assignment
- **RSSIBoundsValid**: Ensures RSSI values are within valid range (-120 to 0 dBm)
- **RSSIInitializationValue**: Confirms RSSI starts with sentinel value (-127)
- **NetworkCountLimit**: Tests maximum network limit enforcement (20 networks)
- **NoNetworksFound**: Handles zero networks found scenario

### 2. Display Module Tests (`DisplayTests`)

Tests for graph rendering and RSSI history management.

- **HistoryInitialization**: Verifies history buffer initialized with sentinel values
- **HistoryShift**: Tests circular buffer shift operation for scrolling graph
- **MultipleHistoryUpdates**: Validates continuous data updates to history
- **GraphYCoordinateMapping**: Tests conversion of RSSI values to screen coordinates
- **ValidRSSIForGraphDisplay**: Ensures only valid data is displayed
- **SentinelValueExcludedFromGraph**: Confirms invalid/uninitialized data is filtered

### 3. UI State Management Tests (`UIStateTests`)

Tests for user interface logic and state transitions.

- **NetworkIndexCycling**: Verifies upper button cycles through networks correctly
- **ScreenTransitionToDetail**: Tests transition to RSSI graph view
- **NoNetworksHandlerCheck**: Ensures buttons don't respond when no networks available
- **DetailViewHandlerCheck**: Confirms buttons disabled in detail view
- **ValidButtonHandlerConditions**: Tests combined conditions for button handling
- **IndexBoundsInCycling**: Verifies wrap-around behavior at network list boundaries

### 4. Data Structure Tests (`DataStructureTests`)

Validates memory layout and sizes of critical data structures.

- **WiFiHistoryArraySize**: Confirms history array is correct size (240 elements)
- **BSSIDArraySize**: Validates MAC address array (6 bytes)
- **SSIDArraySize**: Checks network name array (32 bytes)

### 5. Integration Tests (`IntegrationTests`)

End-to-end scenario tests simulating real user workflows.

- **SelectNetworkAndViewRSSI**: Complete workflow from network selection to RSSI viewing
- **ContinuousMonitoring**: Simulates sustained monitoring with multiple RSSI updates

## Running Tests

### Using PlatformIO

Run all tests:
```bash
pio test -e native_test
```

Run tests with verbose output:
```bash
pio test -e native_test -v
```

Run specific test suite:
```bash
pio test -e native_test --filter "WiFiUtilityTests"
```

### Using CMake (Alternative)

Build and run tests:
```bash
mkdir build
cd build
cmake ..
make
ctest --output-on-failure
```

## Test Coverage

The test suite covers:
- ✅ WiFi network scanning and BSSID handling
- ✅ RSSI value capture and validation
- ✅ Display history buffer management
- ✅ Graph coordinate mapping
- ✅ UI state transitions
- ✅ Button event handling logic
- ✅ Edge cases (no networks, boundary conditions)
- ✅ Integration scenarios (complete workflows)

## Adding New Tests

To add new tests, follow this pattern:

```cpp
class NewFeatureTests : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize test fixtures
    }
    
    // Test data members
};

TEST_F(NewFeatureTests, SpecificBehavior) {
    // Arrange
    // Act
    // Assert
    EXPECT_EQ(actual, expected);
}
```

## Mock Objects

The test suite uses simplified mock implementations of ESP WiFi structures since full ESP32 SDK is not available in native test environment. Real hardware testing should still be performed before deployment.

### Mocked Structures:
- `wifi_ap_record_t`: Network record structure
- Global test variables for BSSID and RSSI tracking

## Continuous Integration

These tests can be integrated into CI/CD pipelines:

```yaml
# Example GitHub Actions workflow
- name: Run Tests
  run: pio test -e native_test -v
```

## Troubleshooting

**Tests won't compile:**
- Ensure GoogleTest is installed: `pip install platformio[testing]`
- Check that test file is in `test/` directory
- Verify CMakeLists.txt includes all necessary sources

**Tests fail on first run:**
- Check that mock structures match actual ESP WiFi definitions
- Verify test fixture SetUp() initializes all variables
- Run tests with verbose output: `pio test -e native_test -v`

## Future Test Improvements

- [ ] Add performance tests for real-time graph updates
- [ ] Add stress tests for WiFi network scanning with 100+ networks
- [ ] Mock ESP32 WiFi library for more complete testing
- [ ] Add hardware-in-the-loop tests on actual ESP32 board
- [ ] Test power consumption in different monitoring modes
