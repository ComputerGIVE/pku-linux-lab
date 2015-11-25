obj-m += softfloat.o
ccflags-y:=-msoft-float -O0 -msse

all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules

clean:
	make -C /lib/modules/`uname -r`/build M=$(PWD) clean
