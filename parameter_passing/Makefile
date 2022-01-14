obj-m :=param.o

KERNELDIR = /lib/modules/$(shell uname -r)/build/
PWD :=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
prepare:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) module_prepare
install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) module_install
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
