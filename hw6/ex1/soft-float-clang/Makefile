obj-m += softfloat.o
ccflags-y:=-msoft-float -O0 -Wno-error

all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules

clean:
	make -C /lib/modules/`uname -r`/build M=$(PWD) clean
