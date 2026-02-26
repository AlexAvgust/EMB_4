# Test Execution Examples

## Expected Test Output

When you run `pio test -e native_test`, you should see output similar to this:

```
WiFi RSSI Analyzer - Test Suite Execution
==========================================

[doctest] doctest - 0 tests passed, 0 failed, 0 skipped
[gtest] Running test suite...

[==========] Running 24 tests from 5 test suites.
[----------] Global test environment set-up.
[----------] 5 tests from WiFiUtilityTests
[ RUN      ] WiFiUtilityTests.SetTargetBSSID
[       OK ] WiFiUtilityTests.SetTargetBSSID (0 ms)
[ RUN      ] WiFiUtilityTests.SetTargetRSSI
[       OK ] WiFiUtilityTests.SetTargetRSSI (0 ms)
[ RUN      ] WiFiUtilityTests.RSSIBoundsValid
[       OK ] WiFiUtilityTests.RSSIBoundsValid (0 ms)
[ RUN      ] WiFiUtilityTests.RSSIInitializationValue
[       OK ] WiFiUtilityTests.RSSIInitializationValue (0 ms)
[ RUN      ] WiFiUtilityTests.NetworkCountLimit
[       OK ] WiFiUtilityTests.NetworkCountLimit (0 ms)
[ RUN      ] WiFiUtilityTests.NoNetworksFound
[       OK ] WiFiUtilityTests.NoNetworksFound (0 ms)
[----------] 6 tests from WiFiUtilityTests (1 ms total)

[----------] 6 tests from DisplayTests
[ RUN      ] DisplayTests.HistoryInitialization
[       OK ] DisplayTests.HistoryInitialization (0 ms)
[ RUN      ] DisplayTests.HistoryShift
[       OK ] DisplayTests.HistoryShift (1 ms)
[ RUN      ] DisplayTests.MultipleHistoryUpdates
[       OK ] DisplayTests.MultipleHistoryUpdates (0 ms)
[ RUN      ] DisplayTests.GraphYCoordinateMapping
[       OK ] DisplayTests.GraphYCoordinateMapping (0 ms)
[ RUN      ] DisplayTests.ValidRSSIForGraphDisplay
[       OK ] DisplayTests.ValidRSSIForGraphDisplay (0 ms)
[ RUN      ] DisplayTests.SentinelValueExcludedFromGraph
[       OK ] DisplayTests.SentinelValueExcludedFromGraph (0 ms)
[----------] 6 tests from DisplayTests (1 ms total)

[----------] 6 tests from UIStateTests
[ RUN      ] UIStateTests.NetworkIndexCycling
[       OK ] UIStateTests.NetworkIndexCycling (0 ms)
[ RUN      ] UIStateTests.ScreenTransitionToDetail
[       OK ] UIStateTests.ScreenTransitionToDetail (0 ms)
[ RUN      ] UIStateTests.NoNetworksHandlerCheck
[       OK ] UIStateTests.NoNetworksHandlerCheck (0 ms)
[ RUN      ] UIStateTests.DetailViewHandlerCheck
[       OK ] UIStateTests.DetailViewHandlerCheck (0 ms)
[ RUN      ] UIStateTests.ValidButtonHandlerConditions
[       OK ] UIStateTests.ValidButtonHandlerConditions (0 ms)
[ RUN      ] UIStateTests.IndexBoundsInCycling
[       OK ] UIStateTests.IndexBoundsInCycling (0 ms)
[----------] 6 tests from UIStateTests (0 ms total)

[----------] 3 tests from DataStructureTests
[ RUN      ] DataStructureTests.WiFiHistoryArraySize
[       OK ] DataStructureTests.WiFiHistoryArraySize (0 ms)
[ RUN      ] DataStructureTests.BSSIDArraySize
[       OK ] DataStructureTests.BSSIDArraySize (0 ms)
[ RUN      ] DataStructureTests.SSIDArraySize
[       OK ] DataStructureTests.SSIDArraySize (0 ms)
[----------] 3 tests from DataStructureTests (0 ms total)

[----------] 2 tests from IntegrationTests
[ RUN      ] IntegrationTests.SelectNetworkAndViewRSSI
[       OK ] IntegrationTests.SelectNetworkAndViewRSSI (0 ms)
[ RUN      ] IntegrationTests.ContinuousMonitoring
[       OK ] IntegrationTests.ContinuousMonitoring (0 ms)
[----------] 2 tests from IntegrationTests (1 ms total)

[----------] Global test environment tear-down
[==========] 24 tests from 5 test suites ran. (5 ms total)
[  PASSED  ] 24 tests
[gtest] PASSED
```

## Verbose Output

When running with `-v` flag, you get detailed information:

```bash
$ pio test -e native_test -v

Platform: native
Building for native
Collecting...
Compiling...
Linking...
Running...

[gtest] Running test suite with verbose output...

[----------] 5 tests from WiFiUtilityTests
[ RUN      ] WiFiUtilityTests.SetTargetBSSID
[       OK ] WiFiUtilityTests.SetTargetBSSID (0 ms)
       Details: Successfully copied 6-byte MAC address

[ RUN      ] WiFiUtilityTests.RSSIBoundsValid
[       OK ] WiFiUtilityTests.RSSIBoundsValid (0 ms)
       Details: Tested -120, -100, -75, -55, -30, 0 dBm values
```

## Running Specific Tests

Filter by test class:
```bash
$ pio test -e native_test --filter "WiFiUtilityTests"

[==========] Running 6 tests from 1 test suite.
[----------] 6 tests from WiFiUtilityTests
...
[==========] 6 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 6 tests
```

Filter by specific test:
```bash
$ pio test -e native_test --filter "WiFiUtilityTests.RSSIBoundsValid"

[==========] Running 1 test from 1 test suite.
[----------] 1 test from WiFiUtilityTests
[ RUN      ] WiFiUtilityTests.RSSIBoundsValid
[       OK ] WiFiUtilityTests.RSSIBoundsValid (0 ms)
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test
```

## Test Results Interpretation

### Success (PASSED)
```
[==========] 24 tests from 5 test suites ran. (5 ms total)
[  PASSED  ] 24 tests
```
All tests passed! ✅

### Partial Failure
```
[==========] 24 tests from 5 test suites ran. (7 ms total)
[  FAILED  ] 2 tests, listed below:
[  FAILED  ] WiFiUtilityTests.RSSIBoundsValid
[  FAILED  ] DisplayTests.GraphYCoordinateMapping

2 FAILED TESTS
```
Some tests failed. Review the error messages above.

### Test Failure Example
```
[ RUN      ] WiFiUtilityTests.RSSIBoundsValid
wifi_rssi_tests.cpp:45: Failure
Expected: rssi >= -120
Actual: -127
[ FAILED  ] WiFiUtilityTests.RSSIBoundsValid (1 ms)
```

## Continuous Integration

Add to your CI/CD pipeline:

```yaml
# GitHub Actions example
- name: Run Unit Tests
  run: |
    pip install platformio
    pio test -e native_test -v

- name: Report Test Results
  if: always()
  run: |
    echo "Test Summary:"
    pio test -e native_test
```

## Performance Metrics

Test execution typically takes < 100ms:

```
WiFi Tests:        1 ms
Display Tests:     1 ms
UI State Tests:    0 ms
Data Structure:    0 ms
Integration Tests: 1 ms
─────────────────────
Total:             5 ms
```

## Debugging Failed Tests

If tests fail, use verbose output to get more details:

```bash
$ pio test -e native_test -v
```

Or compile and run directly:

```bash
mkdir build && cd build
cmake ..
make
./wifi_rssi_tests --gtest_filter="WiFiUtilityTests.SetTargetBSSID" -v
```
