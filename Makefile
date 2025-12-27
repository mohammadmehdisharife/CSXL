# Compiler flags
CCFLAGS = -Oz

# Source files
SRC = csxl.c function.c utils.c memory.c log.c

# Build directory
BUILD_DIR = ./build

# Targets
LINUX_TARGET = $(BUILD_DIR)/csxl
WIN32_TARGET = $(BUILD_DIR)/csxl_win32.exe
WIN64_TARGET = $(BUILD_DIR)/csxl_win64.exe

# Default target
all: build_linux build_win32 build_win64

# Linux build
build_linux: $(LINUX_TARGET)

$(LINUX_TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	gcc $(CCFLAGS) $(SRC) -o $(LINUX_TARGET)

# Windows 32-bit build
build_win32: $(WIN32_TARGET)

$(WIN32_TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	i686-w64-mingw32-gcc $(CCFLAGS) $(SRC) -o $(WIN32_TARGET)

# Windows 64-bit build
build_win64: $(WIN64_TARGET)

$(WIN64_TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	x86_64-w64-mingw32-gcc $(CCFLAGS) $(SRC) -o $(WIN64_TARGET)

# Clean
clean:
	rm -rf $(BUILD_DIR) *.zip *.tar*

# Format code
format:
	astyle --style=linux *.c
	astyle --style=linux *.h

# Help
help:
	@echo "Available targets:"
	@echo "  all          - Build all platforms (default)"
	@echo "  build_linux  - Build for Linux"
	@echo "  build_win32  - Build for Windows 32-bit"
	@echo "  build_win64  - Build for Windows 64-bit"
	@echo "  clean        - Remove build files and archives"
	@echo "  format       - Format source code with astyle"
	@echo "  help         - Show this help message"
