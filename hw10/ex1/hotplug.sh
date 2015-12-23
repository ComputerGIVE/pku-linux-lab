#!/bin/bash

for i in `seq 1 500`
	do
		echo "Loop $i"
		if echo "$1" > /sys/bus/usb/drivers/usb/unbind; then
			echo Device unconnected successfully
		else
			echo Device unconnect failed
		fi

		if echo "$1" > /sys/bus/usb/drivers/usb/bind; then
			echo Device connected successfully
		else
			echo Device connect failed
		fi

	done

