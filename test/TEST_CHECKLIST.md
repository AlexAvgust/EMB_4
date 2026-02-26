# Test Suite Checklist & Validation Guide

## Pre-Test Setup Checklist

- [ ] PlatformIO installed: `pip install platformio[testing]`
- [ ] GoogleTest framework available
- [ ] CMake installed (optional, for manual builds)
- [ ] Test files in `/test` directory
- [ ] `platformio.ini` has `[env:native_test]` section
- [ ] Test runner scripts have execute permissions (Linux/macOS)

## Running Tests Checklist

### Initial Test Run
- [ ] Navigate to project root directory
- [ ] Run: `pio test -e native_test`
- [ ] All 24 tests pass
- [ ] Execution time < 100ms
- [ ] No compilation errors

### Verbose Testing
- [ ] Run: `pio test -e native_test -v`
- [ ] Review detailed output
- [ ] Verify test names and descriptions match documentation
- [ ] Check for any warnings

### Test Filtering
- [ ] Run WiFi tests only: `pio test -e native_test --filter "WiFiUtilityTests"`
- [ ] Run Display tests: `pio test -e native_test --filter "DisplayTests"`
- [ ] Run UI tests: `pio test -e native_test --filter "UIStateTests"`
- [ ] Run single test: `pio test -e native_test --filter "WiFiUtilityTests.SetTargetBSSID"`

## Test Coverage Validation

### WiFi Module Coverage
- [ ] BSSID storage verified
- [ ] RSSI value assignment tested
- [ ] RSSI bounds validated (-120 to 0)
- [ ] Initialization value correct (-127)
- [ ] Network count limit enforced
- [ ] Zero networks case handled

### Display Module Coverage
- [ ] History buffer initializes with sentinel (-120)
- [ ] Circular shift operation works correctly
- [ ] Multiple updates don't corrupt buffer
- [ ] Y coordinate mapping is accurate
- [ ] Valid data (> -120) displayed
- [ ] Invalid data (≤ -120) filtered out

### UI State Coverage
- [ ] Upper button cycles networks 0→1→2→...→0
- [ ] Lower button transitions to detail view
- [ ] Buttons disabled when no networks found
- [ ] Buttons disabled in detail view
- [ ] Combined conditions work correctly
- [ ] Index wraps correctly at boundaries

### Data Structure Coverage
- [ ] WiFi history array is 240 elements
- [ ] BSSID array is 6 bytes
- [ ] SSID array is 32 bytes
- [ ] No memory padding issues
- [ ] Types are correct

### Integration Coverage
- [ ] Complete workflow: scan → select → monitor
- [ ] Multiple RSSI updates in sequence
- [ ] State transitions work together
- [ ] History updates during monitoring

## Troubleshooting Checklist

### Tests Won't Compile
- [ ] GoogleTest library installed: `pip install platformio[testing]`
- [ ] CMakeLists.txt is in project root
- [ ] Test file is in `test/` directory
- [ ] No syntax errors in test file
- [ ] `platformio.ini` has native_test environment

### Tests Fail
- [ ] Read error message carefully
- [ ] Run with verbose: `pio test -e native_test -v`
- [ ] Check test documentation for expected behavior
- [ ] Verify mock structures match actual definitions
- [ ] Check SetUp() initializes all variables

### Tests Run Slowly
- [ ] Disable antivirus real-time scanning temporarily
- [ ] Check system resources (RAM, CPU)
- [ ] Run tests in SSD directory if possible
- [ ] Verify no other heavy processes running

### Cross-Platform Issues
- [ ] On Windows: Use `run_tests.bat` or `pio` commands
- [ ] On Linux/macOS: Use `run_tests.sh` or `pio` commands
- [ ] Ensure CMake installed (for manual CMake builds)
- [ ] Check line endings (LF vs CRLF) if issues occur

## Test Output Validation

### Expected Output Pattern
```
[==========] Running 24 tests from 5 test suites.
[----------] Global test environment set-up.
[----------] X tests from TestClassName
[ RUN      ] TestClassName.TestMethodName
[       OK ] TestClassName.TestMethodName (X ms)
...
[==========] 24 tests from 5 test suites ran. (X ms total)
[  PASSED  ] 24 tests
```

### Success Indicators
- [ ] All tests show `[OK]`
- [ ] All test suites complete
- [ ] Final line shows `[PASSED] 24 tests`
- [ ] No compilation warnings
- [ ] No runtime errors

### Failure Indicators (Should NOT Appear)
- ❌ `[FAILED]` tag
- ❌ `Segmentation fault`
- ❌ `Assertion failed`
- ❌ Memory leaks reported
- ❌ Test timeout

## Performance Validation

### Acceptable Performance
- [ ] Total execution: < 100ms
- [ ] Per test: < 10ms
- [ ] Compilation: < 30 seconds
- [ ] No memory issues
- [ ] Clean shutdown

### Performance Measurement
```bash
# Measure total time
time pio test -e native_test

# Expected: ~0.5-2 seconds total (including compilation)
```

## Documentation Review

- [ ] README.md mentions testing
- [ ] TESTING.md has quick start instructions
- [ ] TEST_DOCUMENTATION.md explains all tests
- [ ] TEST_EXAMPLES.md shows sample output
- [ ] All documentation is accurate and up-to-date

## Continuous Integration Setup

### GitHub Actions
- [ ] `.github/workflows/test.yml` created (optional)
- [ ] Test job runs on every push
- [ ] Test results reported
- [ ] Failures block merges (if desired)

### Local Pre-commit Hook (Optional)
```bash
#!/bin/bash
pio test -e native_test || exit 1
```

- [ ] Pre-commit hook installed
- [ ] Tests run before commits
- [ ] Failing tests prevent commits

## Test Maintenance Checklist

### When Adding Features
- [ ] New tests written for new functionality
- [ ] Existing tests still pass
- [ ] Tests document expected behavior
- [ ] Edge cases tested

### When Fixing Bugs
- [ ] Write test that reproduces bug
- [ ] Verify test fails with old code
- [ ] Fix bug implementation
- [ ] Verify test passes with fix
- [ ] Add regression test

### Regular Maintenance
- [ ] Monthly: Run full test suite
- [ ] Quarterly: Review test coverage
- [ ] Annually: Update test documentation
- [ ] After major changes: Expand test suite

## Final Validation Checklist

Before considering testing complete:

- [ ] All 24 tests pass locally
- [ ] Tests run on Windows
- [ ] Tests run on macOS/Linux
- [ ] CI/CD integration working (if using)
- [ ] Documentation is complete
- [ ] Test scripts are executable
- [ ] No platform-specific issues
- [ ] Performance is acceptable
- [ ] Ready for production use

## Sign-Off

**Testing Completed**: ___________  Date: ___________

**Approved By**: ___________________

**Notes**:
```
_________________________________________________________________

_________________________________________________________________

_________________________________________________________________
```

---

## Additional Resources

- Test file: `test/wifi_rssi_tests.cpp`
- Documentation: `test/TEST_DOCUMENTATION.md`
- Examples: `test/TEST_EXAMPLES.md`
- Quick start: `TESTING.md`
- Summary: `TESTS_SUMMARY.md`
- Configuration: `platformio.ini`, `CMakeLists.txt`
