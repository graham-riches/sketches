.DEFAULT_GOAL:=help
CMAKE:=cmake
NINJA:=ninja
OUTPUT_DIR:=cmake-build-deploy
TOOLCHAIN:=toolchain.cmake
PASSWORD:="RickyDusty"
PI_IP:=pi@10.0.0.201

.PHONY: help
help:
    @LC_ALL=C $(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'

$(OUTPUT_DIR)/CMakeCache.txt:
	$(CMAKE) -B $(OUTPUT_DIR) -S . -DCMAKE_BUILD_TYPE=Release -GNinja -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)

.PHONY: build
build: $(OUTPUT_DIR)/CMakeCache.txt  ## Build the project
	$(NINJA) -C $(OUTPUT_DIR)

.PHONY: clean
clean: 
	rm -r $(OUTPUT_DIR)/**

PHONY: load
load:
	sshpass -p $(PASSWORD) scp $(OUTPUT_DIR)/halloween $(PI_IP):/home/pi/halloween
	sshpass -p $(PASSWORD) scp config/config.json $(PI_IP):/home/pi/halloween
	sshpass -p $(PASSWORD) scp -r images/ $(PI_IP):/home/pi/halloween/