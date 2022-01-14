obj-m := jiffie.o

KDIR = /lib/modules/$(shell uname -r)/build


all:
	make -C $(KDIR)  M=$(shell pwd) modules
	gcc -o Application Application.c
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
