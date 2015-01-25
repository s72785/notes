#!/bin/sh
gcc -g -lm -o apl apl.c 2> err
if [ $? -eq 0 ]; then
	gcc -Wall -g -lm -o apl apl.c 2> err
fi
cat err | wc
if [ $(cat err|wc -w) -eq 0 ]; then
	./apl
	#~ if [ $? -ne 0 ]; then
		#~ gdb ./apl
	#~ fi
else
	less err
fi
