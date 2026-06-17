CC = gcc
LD = ld
STRIP = strip
CFLAGS = -O2 -march=native -Wall -Wextra -Wmaybe-uninitialized -Winit-self -Wpedantic -Wshadow -Wformat=2 -Wformat-security -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wconversion -Wsign-conversion -Wundef -Werror=shadow -Werror=format-security -fno-omit-frame-pointer -Wcast-qual -Wlogical-op -Wduplicated-cond -Wduplicated-branches -Wstrict-overflow=3 -Warray-bounds -Wstringop-overflow -Wnull-dereference -Wwrite-strings -Wold-style-definition -Wredundant-decls -Wnested-externs -Winline -Wdisabled-optimization -Wfloat-equal -Wswitch-default -Wswitch-enum -Wparentheses -Wsequence-point -Wbad-function-cast -Wpointer-arith -Wtype-limits -Wunreachable-code
INCLUDE = -Iinclude
OBJCFLAGS = -c
ARCH = x86_64
BUILD = build
SYSBIN = /usr/bin
OUT = arch/$(ARCH)/out
MEM := setvar getvar setalias getalias
SH := exec_cmd interactive_sh default_vars tokenizer getbuiltin log_hist
DIRS := $(BUILD) $(OUT)
BUILTINS := chdir/change_d exec/exec extern/extern_cmd exit/exit_iact_sh source/source pwd/pwd
MISC := strjoin
ALL_OBJS_TMP := $(addprefix build/,$(MEM)) $(addprefix build/,$(SH)) $(addprefix build/,$(notdir $(BUILTINS))) $(addprefix build/,$(MISC))
ALL_OBJS := $(addsuffix .o, $(ALL_OBJS_TMP))
ALL_OUTS = $(OUT)/mush $(OUT)/mush.unstripped
ALL_SF = $(MEM) $(SH) $(BUILTINS) $(MISC)

all: $(DIRS) $(MEM) $(SH) $(BUILTINS) $(MISC) link
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

$(MISC):
	@printf 'CC\t\t%s\t\t=>\t\t%s\n' "misc/$@.c" "$(BUILD)/$@.o"
	@$(CC) $(OBJCFLAGS) $(CFLAGS) $(INCLUDE) misc/$@.c -o $(BUILD)/$@.o

link: $(ALL_SF)
	@printf 'LINK\t\t%s\n' "$(OUT)/mush.unstripped"
	@printf "ALL_OBJS: %s\n" "$(ALL_OBJS)"
	@$(CC) $(ALL_OBJS) $(INCLUDE) main/mush.c -o $(OUT)/mush.unstripped

strip:
	@printf 'STRIP\t\t%s\n' "$(OUT)/mush"
	@$(STRIP) $(OUT)/mush.unstripped -o $(OUT)/mush || $(MAKE) link

clean:
	@printf 'DEL\t\t%s\n' "$(ALL_OBJS) $(ALL_OUTS)"
	@rm -rf $(ALL_OBJS) $(ALL_OUTS)

run:
	-@exec $(OUT)/mush || exec $(OUT)/mush.unstripped

help:
	@$(MAKE) --no-print-directory -f Makefile.help

install:
	@cp $(OUT)/mush $(SYSBIN)/mush || cp $(OUT)/mush.unstripped $(SYSBIN)/mush

