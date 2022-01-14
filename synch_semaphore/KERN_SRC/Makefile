
obj-m:=synch_semaphore.o


KERN_SRC :=/lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

modules:
	make -C $(KERN_SRC) M=$(PWD) modules
	gcc -o ../app ../app.c -g

install:
	make -C $(KERN_SRC) M=$(PWD) modules_install
	depmod -a

clean:
	make -C $(KERN_SRC) M=$(PWD) clean
	rm -f ../app
