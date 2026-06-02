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
MEM := setvar getvar setalias
SH := exec_cmd interactive_sh
DIRS := $(BUILD) $(OUT)
ALL_OBJS = build/setalias.o build/setvar.o build/getvar.o build/exec_cmd.o build/interactive_sh.o
ALL_OUTS = $(OUT)/mush $(OUT)/mush.unstripped
ALL_SF = $(MEM) $(SH)

all: $(DIRS) $(MEM) $(SH) link
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

link: $(ALL_SF)
	@printf 'LINK\t\t%s\n' "$(OUT)/mush.unstripped"
	@$(CC) $(ALL_OBJS) $(INCLUDE) main/mush.c -o $(OUT)/mush.unstripped

strip: link
	@printf 'STRIP\t\t%s\n' "$(OUT)/mush"
	@$(STRIP) $(OUT)/mush.unstripped -o $(OUT)/mush

clean:
	@printf 'DEL\t\t%s\n' "$(ALL_OBJS)$(EXTRA_OBJS)$(ALL_OUTS)"
	@rm -rf $(ALL_OBJS) $(EXTRA_OBJS) $(ALL_OUTS)

run:
	@exec $(OUT)/mush || exec $(OUT)/mush.unstripped

help:
	@$(MAKE) --no-print-directory -f Makefile.help

install:
	@cp $(OUT)/mush $(SYSBIN)/mush || cp $(OUT)/mush.unstripped $(SYSBIN)/mush

