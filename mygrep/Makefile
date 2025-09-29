#CXX ?= g++
CXX = g++

# path #
SRC_PATH = src
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin
TEST_PATH = tests
TEST_BUILD_PATH = $(BUILD_PATH)/tests
TEST_BIN_PATH = $(BUILD_PATH)/bin

# executable #
BIN_NAME = mygrep
TEST_BIN_NAME = unit_tests

# extensions #
SRC_EXT = cpp

# code lists #
# Find all application source files, excluding main.cpp
APP_SOURCES_NO_MAIN = $(filter-out $(SRC_PATH)/main.$(SRC_EXT), $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)'))
APP_OBJECTS_NO_MAIN = $(APP_SOURCES_NO_MAIN:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)

# Main application's entry point source and object
APP_MAIN_SOURCE = $(SRC_PATH)/main.$(SRC_EXT)
APP_MAIN_OBJECT = $(APP_MAIN_SOURCE:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)

# All application objects (for the main runner)
ALL_APP_OBJECTS = $(APP_MAIN_OBJECT) $(APP_OBJECTS_NO_MAIN)

# Set the dependency files for all application objects
DEPS = $(ALL_APP_OBJECTS:.o=.d)

# Find all test source files
TEST_SOURCES = $(shell find $(TEST_PATH) -name '*_test.$(SRC_EXT)')

# Create object files for each test source file
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_PATH)/%.$(SRC_EXT)=$(TEST_BUILD_PATH)/%.o)

# Set the dependency files for all test objects
TEST_DEPS = $(TEST_OBJECTS:.o=.d)

# flags #
# Define separate sets of flags for release and debug builds
RELEASE_COMPILE_FLAGS = -std=c++17 -Wall -Wextra -O3 -DNDEBUG
DEBUG_COMPILE_FLAGS = -std=c++17 -Wall -Wextra -g

# Common flags for includes and libraries
INCLUDES = -I include/ -I /usr/local/include
LIBS =
TEST_LIBS = -L/usr/local/lib -lgtest -lgtest_main -pthread

# Default target
.PHONY: default_target
default_target: release

# Release build target
.PHONY: release
release: export CXXFLAGS := $(RELEASE_COMPILE_FLAGS) # Removed $(CXXFLAGS) before, as it's the first assignment
release: dirs
	@$(MAKE) all

# Debug build target
.PHONY: debug
debug: export CXXFLAGS := $(DEBUG_COMPILE_FLAGS) # Removed $(CXXFLAGS) before, as it's the first assignment
debug: dirs
	@$(MAKE) all

# Test target - build tests with debug flags by default
.PHONY: test
test: export CXXFLAGS := $(DEBUG_COMPILE_FLAGS) # Use DEBUG_COMPILE_FLAGS for tests
test: dirs_test $(TEST_BIN_PATH)/$(TEST_BIN_NAME) # Direct dependency on the test executable
	@echo "Running unit tests..."
	@$(TEST_BIN_PATH)/$(TEST_BIN_NAME)

.PHONY: dirs
dirs:
	@echo "Creating application directories"
	@mkdir -p $(dir $(ALL_APP_OBJECTS))
	@mkdir -p $(BIN_PATH)

.PHONY: dirs_test
dirs_test: dirs
	@echo "Creating test directories"
	@mkdir -p $(dir $(TEST_OBJECTS))
	@mkdir -p $(TEST_BIN_PATH)

.PHONY: clean
clean:
	@echo "Deleting $(BIN_NAME) symlink"
	@$(RM) $(BIN_NAME)
	@echo "Deleting build directories"
	@$(RM) -r $(BUILD_PATH)

run: all
	@echo "Running application..."
	@$(BIN_PATH)/$(BIN_NAME)

# checks the executable and symlinks to the output
.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Creation of the application executable
$(BIN_PATH)/$(BIN_NAME): $(ALL_APP_OBJECTS)
	@echo "Linking application: $@"
	$(CXX) $(ALL_APP_OBJECTS) -o $@ ${LIBS} $(CXXFLAGS) # Added CXXFLAGS for linking

# Creation of the test executable
$(TEST_BIN_PATH)/$(TEST_BIN_NAME): $(APP_OBJECTS_NO_MAIN) $(TEST_OBJECTS)
	@echo "Linking tests: $@"
	$(CXX) $(APP_OBJECTS_NO_MAIN) $(TEST_OBJECTS) -o $@ $(TEST_LIBS) $(CXXFLAGS) # Added CXXFLAGS for linking

# Add dependency files, if they exist
-include $(DEPS)
-include $(TEST_DEPS)

# Source file rules for application (main.cpp)
$(APP_MAIN_OBJECT): $(APP_MAIN_SOURCE)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

# Source file rules for application (other .cpp files)
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@ # FIXED: Removed redundant $(COMPILE_FLAGS)

# Source file rules for tests
$(TEST_BUILD_PATH)/%.o: $(TEST_PATH)/%.$(SRC_EXT)
	@echo "Compiling test: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@