#!/bin/sh
#~ cc=gcc
cc=clang
${cc} -g -lm -o apl apl.c 2> err
if [ $? -eq 0 ]; then
	${cc} -Wall -g -lm -o apl apl.c 2> err
fi
if [ $(cat err|wc -w) -eq 0 ]; then
	./apl
	#~ if [ $? -ne 0 ]; then
		#~ gdb ./apl
	#~ fi
else
	less err
fi
echo -n Zeilen in Fehlermeldungen:
cat err | wc -l
echo --------------------------
