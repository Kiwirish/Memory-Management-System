MODULE_NAME = memdrv

obj-m	:= $(MODULE_NAME).o

KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

CFLAGS := -W -Wall -pedantic -g

all: module debug retrieve store

retrieve: libmemdrv.c libmemdrv.h fs.h retrieve.c
	gcc $(CFLAGS) -o retrieve retrieve.c libmemdrv.c

store: libmemdrv.c libmemdrv.h fs.h store.c
	gcc $(CFLAGS) -o store store.c libmemdrv.c

module:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

debug: debug.c libmemdrv.c libmemdrv.h fs.h
	gcc $(CFLAGS) -o debug debug.c libmemdrv.c

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f debug

