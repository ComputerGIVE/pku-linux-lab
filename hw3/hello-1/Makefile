obj-m = hello-1.o
KVERSION = $(shell uname -r)

all: 
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules

help:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) help
    
clean: 
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
