#!/bin/bash

if ! test -e "ncvm-interface-tester.qcow2"; then
	scp jwicks@192.168.0.224:/mnt/Media/ISO/ncvm-interface-tester.qcow2 .
fi

qemu-system-x86_64 \
	-name "ncvm debugging" \
	-cpu qemu64 \
	-smp 2 \
	-m 2G \
	-bios /usr/share/OVMF/OVMF_CODE.fd \
	-hda ncvm-interface-tester.qcow2 \
	-vga std \
	-enable-kvm \
	-virtfs local,path=temp,mount_tag=temp,security_model=mapped-xattr 

#	-drive file=ncvm-interface-test.img,if=virtio,format=raw \
#	-cdrom Fedora-Server-dvd-x86_64-42-1.1.iso
