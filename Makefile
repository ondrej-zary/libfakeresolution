CFLAGS=-Wall -Wextra -O2

libfakeresolution.so: libfakeresolution.c
	cc $(CFLAGS) libfakeresolution.c -ldl -fPIC -o libfakeresolution.so -shared

clean:
	rm -f libfakeresolution.so
