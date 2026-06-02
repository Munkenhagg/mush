if [ "$1" = "-f" ] || [ "$1" = "--force" ]; then
	:
else
	printf 'Only use this script when make is not accessible. exiting. pass -f/--force to run anyways\n'
	exit 1
fi
CC="gcc"
LD="ld"
CFLAGS="-Wall -Wextra"
SRC="memory/setvar memory/getvar main/mush"

for file in $SRC; do
	$CC -c $CFLAGS $file.c -o build/$(basename $file).o
done

$LD build/*.o -o arch/x86_64/out/mush.unstripped
strip arch/x86_64/out/mush.unstripped
