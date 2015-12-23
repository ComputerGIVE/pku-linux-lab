ccflags-y := -DDEBUG -DCONFIG_USBIP_DEBUG

obj-m += usbip-core.o
usbip-core-y := usbip_common.o usbip_event.o

obj-m += vhci-hcd.o
vhci-hcd-y := vhci_sysfs.o vhci_tx.o vhci_rx.o vhci_hcd.o

obj-m += usbip-host.o
usbip-host-y := stub_dev.o stub_main.o stub_rx.o stub_tx.o

clean:
	make -C /lib/modules/`uname -r`/build M=$(PWD) clean
	
all:
	make -C /lib/modules/`uname -r`/build M=$(PWD) modules
