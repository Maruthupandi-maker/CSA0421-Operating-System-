CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
LDFLAGS = -ldl

all: libencrypt.a libencrypt.so bank_static bank_dynamic bank_runtime inspect_maps

libencrypt.a: encrypt.c
	$(CC) $(CFLAGS) -c encrypt.c -o encrypt.o
	ar rcs libencrypt.a encrypt.o

libencrypt.so: encrypt.c
	$(CC) $(CFLAGS) -fPIC -shared encrypt.c -o libencrypt.so

bank_static: main_static.c libencrypt.a
	$(CC) $(CFLAGS) -static main_static.c -L. -lencrypt -o bank_static

bank_dynamic: main_dynamic.c libencrypt.so
	$(CC) $(CFLAGS) main_dynamic.c -L. -lencrypt -Wl,-rpath,. -o bank_dynamic

bank_runtime: main_runtime_dl.c libencrypt.so
	$(CC) $(CFLAGS) main_runtime_dl.c $(LDFLAGS) -o bank_runtime

inspect_maps: inspect_maps.c
	$(CC) $(CFLAGS) inspect_maps.c -o inspect_maps

clean:
	rm -f *.o *.a *.so bank_static bank_dynamic bank_runtime inspect_maps
