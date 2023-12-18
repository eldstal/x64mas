# The directory where this include file is
ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

# Our own, homegrown Ä runtime
ÄRT_DIR := $(ROOT_DIR)/_ärt

# The directory where the application is
APP_DIR := $(PWD)


APP_SRC:=$(wildcard $(APP_DIR)/*.s)
ÄRT_SRC:=$(wildcard $(ÄRT_DIR)/*.s)

APP_O=$(patsubst %.s,%.o,$(APP_SRC))
ÄRT_O=$(patsubst %.s,%.o,$(ÄRT_SRC))


all: runme
	
run: runme
	./runme
	@echo ""
	
debug: runme
	gdb -ex start ./runme

runme: $(ÄRT_O) $(APP_O)
	ld $^ -o $@

clean:
	-rm $(ÄRT_O) $(APP_O) runme

%.o: %.s
	nasm -I$(ÄRT_DIR) -f elf64 $< -o $@
