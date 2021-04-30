#!/bin/bash

cc 									\
	--std=gnu99 ./ms.c -o MS				 	\
	-I/opt/wokr/l1nux/muslshell/MUSL_INSTALL/include		\
	-static-pie -nostdlib 						\
	-Wl,./libmc.a							\
	-Wl,--pic-executable,--no-dynamic-linker			\
	-Wl,--noinhibit-exec						\
	-Wl,--script=kopycatim.lds -masm=intel				$1

strip ./MS

#echo '__attribute__((section(".text")))' > ./msxxd.c
MSOFFSET=$(readelf -SW MS|grep "\.text"|awk '{ print "0x" $6 }')
MSSIZE=$(readelf -SW MS|grep "\.text"|awk '{ print "0x" $7 }')

echo $MSOFFSET '|' $MSSIZE

xxd -l $MSSIZE -i -s $MSOFFSET MS | sed 's/MS_raw/MS/g' > msxxd.c

cc ./wrapms.c -o wrapms -ftrampolines -mfentry -mfentry-name=MS

strip ./wrapms
