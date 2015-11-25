obj-m += hardfloat.o
ccflags-y:=-mhard-float -O0

all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules

clean:
	make -C /lib/modules/`uname -r`/build M=$(PWD) clean
