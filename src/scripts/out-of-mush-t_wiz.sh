#!/bin/sh

BN="`basename $0`"

printf 'Warning: for the builtins to take effect, you have to source the script. you can do so by using one of\n\tsource %s\n\t. %s\n' "$BN" "$BN"

alias cd='chdir'
alias cls='clear'
alias mkdir='mkdir -p'

mkcd() {
	mkdir -p $@
	cd $@
}

tmake() {
	if ! make $@; then
		if ! cmake $@; then
			printf 'Could neither make or cmake %s' "$@"
		else printf 'cmake succeeded'
	else printf 'make succeeded'
}
