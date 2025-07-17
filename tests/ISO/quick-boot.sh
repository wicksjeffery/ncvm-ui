#!/bin/bash

	qemu-system-x86_64 \
                -name "TISO" \
                -cpu qemu64 \
                -smp 1 \
                -m 512M \
                -enable-kvm \
                -hda TinyCoreA.img \
                -vga std \
                -usbdevice mouse \
                -net nic -net user,hostfwd=tcp::2223-:22 \
                -pidfile "TISO.run"

