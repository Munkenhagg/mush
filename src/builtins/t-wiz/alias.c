#include <mush.h>

void terminal_wiz_alias() {
	setalias("cls", "clear");
	setalias("mkcd", "mkdir -p $@ && cd $@");
	setalias("make", "make $@ || cmake $@");
	setalias("mkdir", "mkdir -p $@");
}
