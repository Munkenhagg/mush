CC = gcc
LD = ld
STRIP = strip
CFLAGS = -O2 -march=native -Wall -Wextra
INCLUDE = -Iinclude
OBJCFLAGS = -c
ARCH = x86_64
BUILD = build
SYSBIN = /usr/bin
OUT = arch/$(ARCH)/out
MEM := setvar getvar setalias getalias
SH := exec_cmd interactive_sh default_vars
DIRS := $(BUILD) $(OUT)
BUILTINS := chdir/change_d exec/exec extern/extern_cmd
ALL_OBJS = build/setalias.o build/getalias.o build/setvar.o build/getvar.o build/exec_cmd.o build/interactive_sh.o build/exec.o build/default_vars.o
ALL_OUTS = $(OUT)/mush $(OUT)/mush.unstripped
ALL_SF = $(MEM) $(SH)

all: $(DIRS) $(MEM) $(SH) $(BUILTINS) link
.PHONY: help link strip install run clean

$(DIRS):
	@printf 'DIR\t\t%s\n' "$@"
	@mkdir -p "$@"

$(MEM):
	@printf 'CC\t\t%s\t\t=>\t\t%s\n' "memory/$@.c" "$(BUILD)/$@.o"
	@$(CC) $(OBJCFLAGS) $(CFLAGS) $(INCLUDE) memory/$@.c -o $(BUILD)/$@.o

$(SH):
	@printf 'CC\t\t%s\t\t=>\t\t%s\n' "shell/$@.c" "$(BUILD)/$@.o"
	@$(CC) $(OBJCFLAGS) $(CFLAGS) $(INCLUDE) shell/$@.c -o $(BUILD)/$@.o

$(BUILTINS):
	@printf 'CC\t\t%s\t\t=>\t\t%s\n' "builtins/$@.c" "$(BUILD)/$$(basename $@).o"
	@$(CC) $(OBJCFLAGS) $(CFLAGS) $(INCLUDE) builtins/$@.c -o $(BUILD)/$$(basename $@).o

link: $(ALL_SF)
	@printf 'LINK\t\t%s\n' "$(OUT)/mush.unstripped"
	@$(CC) $(ALL_OBJS) $(INCLUDE) main/mush.c -o $(OUT)/mush.unstripped

strip:
	@printf 'STRIP\t\t%s\n' "$(OUT)/mush"
	@$(STRIP) $(OUT)/mush.unstripped -o $(OUT)/mush || $(MAKE) link

clean:
	@printf 'DEL\t\t%s\n' "$(ALL_OBJS)$(EXTRA_OBJS)$(ALL_OUTS)"
	@rm -rf $(ALL_OBJS) $(EXTRA_OBJS) $(ALL_OUTS)

run:
	-@exec $(OUT)/mush || exec $(OUT)/mush.unstripped

help:
	@$(MAKE) --no-print-directory -f Makefile.help

install:
	@cp $(OUT)/mush $(SYSBIN)/mush || cp $(OUT)/mush.unstripped $(SYSBIN)/mush

