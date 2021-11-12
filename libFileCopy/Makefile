CC=gcc
libFileCopy.so: libFileCopy.o
	$(CC) -shared -o libFileCopy.so libFileCopy.o
libFileCopy.o: libFileCopy.c
	$(CC) -o libFileCopy.o -c libFileCopy.c -shared -Wall
install:
	sudo cp libFileCopy.h /usr/include/
	sudo cp libFileCopy.so /usr/lib/
	sudo ldconfig
clean:
	rm -rf *.o
	rm -rf *.so
