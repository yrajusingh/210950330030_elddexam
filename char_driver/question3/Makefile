obj-m := main.o
KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o application application.c

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm application

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

