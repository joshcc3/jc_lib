VERSION := 0.1.0
SRC_DIR := src
OUT_ROOT := out
COMPILE_FLAGS := -Wall -std=c11 -ggdb -mxc16
COMPILER := gcc
GCC := $(COMPILER) $(COMPILER_FLAGS)

source_files := $(shell cd $(SRC_DIR) && find . -type f -name "*.c")

containers/%.o: $(SRC_DIR)/containers/%.c
	mkdir -p $(OUT_ROOT)/containers
	$(GCC) $^ -I$(SRC_DIR) -c -o $(OUT_ROOT)/$@

concurrent/%.o: src/concurrent/%.c
	mkdir -p $(OUT_ROOT)/concurrent
	$(GCC) $^ -I$(SRC_DIR) -c -o $(OUT_ROOT)/$@

data/%.o: src/data/%.c
	mkdir -p $(OUT_ROOT)/data
	$(GCC) $^ -I$(SRC_DIR) -c -o $(OUT_ROOT)/$@

time/%.o: src/time/%.c
	mkdir -p $(OUT_ROOT)/time
	$(GCC) $^ -I$(SRC_DIR) -c -o $(OUT_ROOT)/$@

%.o: src/%.c
	mkdir -p $(OUT_ROOT)/
	$(GCC) $^ -I$(SRC_DIR) -c -o $(OUT_ROOT)/$@

lib: $(source_files:%.c=%.o)
	ar -cvq $(OUT_ROOT)/libjc-$(VERSION).a $(shell find . -type f -name "*.o")

.PHONY clean:
clean:
	rm -rf out/
