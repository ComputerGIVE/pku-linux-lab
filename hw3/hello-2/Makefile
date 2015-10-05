obj-m += hello-2.o
obj-m += ../hello-1/hello-1.o 

all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules

clean:
	make -C /lib/modules/`uname -r`/build M=$(PWD) clean
