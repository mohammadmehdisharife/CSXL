# Compiler flags
CFLAGS = -Oz

# Source files
SRC = function.c utils.c memory.c log.c
MAIN_SRC = csxl.c
REPL_SRC = repl.c

# Build directory
BUILD_DIR = ./build

# Targets
LINUX_MAIN = $(BUILD_DIR)/csxl
LINUX_REPL = $(BUILD_DIR)/repl
WIN32_MAIN = $(BUILD_DIR)/csxl_win32.exe
WIN32_REPL = $(BUILD_DIR)/repl_win32.exe
WIN64_MAIN = $(BUILD_DIR)/csxl_win64.exe
WIN64_REPL = $(BUILD_DIR)/repl_win64.exe

# Default target
all: linux win32 win64

# Linux builds
linux: $(LINUX_MAIN) $(LINUX_REPL)

$(LINUX_MAIN): $(MAIN_SRC) $(SRC)
	@mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) $(MAIN_SRC) $(SRC) -o $@

$(LINUX_REPL): $(REPL_SRC) $(SRC)
	@mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) $(REPL_SRC) $(SRC) -o $@

# Windows 32-bit builds
win32: $(WIN32_MAIN) $(WIN32_REPL)

$(WIN32_MAIN): $(MAIN_SRC) $(SRC)
	@mkdir -p $(BUILD_DIR)
	i686-w64-mingw32-gcc $(CFLAGS) $(MAIN_SRC) $(SRC) -o $@

$(WIN32_REPL): $(REPL_SRC) $(SRC)
	@mkdir -p $(BUILD_DIR)
	i686-w64-mingw32-gcc $(CFLAGS) $(REPL_SRC) $(SRC) -o $@

# Windows 64-bit builds
win64: $(WIN64_MAIN) $(WIN64_REPL)

$(WIN64_MAIN): $(MAIN_SRC) $(SRC)
	@mkdir -p $(BUILD_DIR)
	x86_64-w64-mingw32-gcc $(CFLAGS) $(MAIN_SRC) $(SRC) -o $@

$(WIN64_REPL): $(REPL_SRC) $(SRC)
	@mkdir -p $(BUILD_DIR)
	x86_64-w64-mingw32-gcc $(CFLAGS) $(REPL_SRC) $(SRC) -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Format code
format:
	astyle --style=linux *.c *.h

# Help
help:
	@echo "Targets:"
	@echo "  all, linux, win32, win64"
	@echo "  clean, format"
	@echo ""
	@echo "Output:"
	@echo "  ./build/csxl           - Linux interpreter"
	@echo "  ./build/repl           - Linux REPL"
	@echo "  ./build/csxl_win32.exe - Win32 interpreter"
	@echo "  ./build/repl_win32.exe - Win32 REPL"
	@echo "  ./build/csxl_win64.exe - Win64 interpreter"
	@echo "  ./build/repl_win64.exe - Win64 REPL"

.PHONY: all linux win32 win64 clean format help