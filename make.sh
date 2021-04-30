#!/bin/bash
	rm -rf ./MUSL* ./MS
	mkdir MUSL_INSTALL
	mkdir MUSL_BUILD
	mkdir MS
	CFLAGS+="-static -fPIE -pie -fno-pic -finline -finline-functions -maddress-mode=long -m64 -static-pie -Wl,--no-dynamic-linker" \
	LDFLAGS+="-dn -static -fno-shared -Bstatic -pie " \
	./configure  --prefix=`pwd`/MUSL_INSTALL --exec-prefix=MUSL_BUILD && make -j12 && make install

	ar q ./MS/libmc.a `ls ./obj/src/stdio/*.lo ./obj/src/stdlib/*.lo ./obj/src/internal/*.lo ./obj/src/string/*.lo ./obj/src/malloc/*.lo ./obj/src/malloc/mallocng/*.lo ./obj/src/errno/*.lo ./obj/src/string/x86_64/*.lo ./obj/src/mman/*.lo ./obj/src/unistd/*.lo ./obj/src/time/*.lo ./obj/src/multibyte/*.lo ./obj/src/stat/*.lo ./obj/src/process/*.lo ./obj/src/signal/*.lo ./obj/src/thread/*.lo ./obj/src/fcntl/*.lo ./obj/src/linux/*.lo ./obj/src/exit/*.lo ./obj/src/thread/x86_64/*.lo ./obj/src/setjmp/x86_64/*.lo ./obj/src/env/*.lo ./obj/src/signal/x86_64/*.lo ./obj/src/locale/*.lo ./obj/src/misc/*.lo ./obj/src/dirent/*.lo ./obj/src/network/*.lo ./obj/src/select/*.lo ./obj/src/ctype/*.lo ./obj/src/temp/*.lo ./obj/src/complex/*.lo ./obj/src/math/*.lo ./obj/src/math/x86_64/*.lo ./obj/src/passwd/*.lo ./obj/src/termios/*.lo ./obj/src/fenv/*.lo ./obj/src/fenv/x86_64/*.lo`
	tar xf ./MS.tgz
	cd MS && ./msmake.sh
	
