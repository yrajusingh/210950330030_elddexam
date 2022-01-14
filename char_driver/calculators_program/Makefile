obj-m := calc_driver2.o
KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

install:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules_install
	depmod -a

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
	rm -rf /lib/modules/$(shell uname -r)/extra/

mknodes:
	sudo mknod -m 666 /dev/Add c 451 0
	sudo mknod -m 666 /dev/Sub c 451 0
	sudo mknod -m 666 /dev/Mul c 451 0
	sudo mknod -m 666 /dev/Div c 451 0
