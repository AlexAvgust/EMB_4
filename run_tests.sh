#!/bin/bash
# Test runner script for WiFi RSSI Analyzer
# 
# Usage:
#   ./run_tests.sh              # Run all tests
#   ./run_tests.sh verbose      # Run with verbose output
#   ./run_tests.sh filter NAME  # Run specific test suite

set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$PROJECT_DIR"

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}WiFi RSSI Analyzer - Test Runner${NC}"
echo "=================================="

# Check if platformio is installed
if ! command -v pio &> /dev/null; then
    echo -e "${RED}Error: PlatformIO is not installed${NC}"
    echo "Install it with: pip install platformio"
    exit 1
fi

# Parse arguments
VERBOSE=""
FILTER=""

if [ "$1" == "verbose" ]; then
    VERBOSE="-v"
elif [ "$1" == "filter" ] && [ -n "$2" ]; then
    FILTER="--filter $2"
fi

# Run tests
echo -e "\n${YELLOW}Running tests...${NC}\n"

if pio test -e native_test $VERBOSE $FILTER; then
    echo -e "\n${GREEN}✓ All tests passed!${NC}"
    exit 0
else
    echo -e "\n${RED}✗ Some tests failed${NC}"
    exit 1
fi
