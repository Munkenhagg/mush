#include <mush.h>

void terminal_wiz_alias() {
	setali("cls", "clear");
	setali("mkcd", "mkdir -p $@ && cd $@");
	setali("make", "extern make $@ || extern cmake $@");
	setali("mkdir", "mkdir -p $@");
}
