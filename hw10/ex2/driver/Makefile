ccflags-y := -DDEBUG -DCONFIG_USBIP_DEBUG

obj-m += usb-skeleton.o

all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules
clean:
	make -C /lib/modules/`uname -r`/build M=$(PWD) clean
	
