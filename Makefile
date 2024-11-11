# Read configuration values
def_compiler := $(shell cat config/mf.cfg | jq -r .compiler)
def_output_name := $(shell cat config/mf.cfg | jq -r .output_name)

# Shared flags and directories
BUILD_DIR := build
SRC_DIR := src
CONFIG_DIR := config
INCLUDE_DIR := src/include

# Compiler flags for different builds
DEBUG_FLAGS := -g
RELEASE_FLAGS := -O3

# Default target
default: prepare
	$(def_compiler) -o $(BUILD_DIR)/$(def_output_name) $(SRC_DIR)/*

# Debug build
dbg: prepare
	$(def_compiler) $(DEBUG_FLAGS) -o $(BUILD_DIR)/dbg_$(def_output_name) $(SRC_DIR)/*

# Release build
release: prepare
	$(def_compiler) $(RELEASE_FLAGS) -o $(BUILD_DIR)/release_$(def_output_name) $(SRC_DIR)/*

# Update config file - handles both compiler and name in one command
config:
	@if [ -n "$(compiler)" ] || [ -n "$(name)" ]; then \
		cat $(CONFIG_DIR)/mf.cfg | jq \
			$(if $(compiler),'.compiler = "$(compiler)"') \
			$(if $(name),'.output_name = "$(name)"') \
			> $(CONFIG_DIR)/mf.cfg.tmp && \
		mv $(CONFIG_DIR)/mf.cfg.tmp $(CONFIG_DIR)/mf.cfg; \
	fi

# Create necessary directories
prepare:
	@mkdir -p $(BUILD_DIR)

# Clean build artifacts
clean:
	@rm -rf $(BUILD_DIR)

# Initialize config file if it doesn't exist
init:
	@mkdir -p $(CONFIG_DIR)
	@[ -f $(CONFIG_DIR)/mf.cfg ] || echo '{"compiler":"gcc","output_name":"program"}' > $(CONFIG_DIR)/mf.cfg

.PHONY: default dbg release config prepare clean init
