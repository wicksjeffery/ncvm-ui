#!/bin/bash

if [ "$#" -eq 0 ]; then
	echo "Have a nice day."
	exit 0
fi

runVM() {
	if [ -f ncvm-debugging.run ]; then
		echo "VM is already running."
		return
	fi

	if ! test -e "ncvm-interface-tester.qcow2"; then
		scp jwicks@192.168.0.224:/mnt/Media/ISO/ncvm-interface-tester.qcow2 .
	fi

	qemu-system-x86_64 \
		-name "ncvm-debugging" \
		-cpu qemu64 \
		-smp 2 \
		-m 2G \
		-bios /usr/share/OVMF/OVMF_CODE.fd \
		-hda ncvm-interface-tester.qcow2 \
		-vga std \
		-enable-kvm \
		-usbdevice mouse \
		-net nic -net user,hostfwd=tcp::2222-:22 \
		-pidfile "ncvm-debugging.run"

	#	-virtfs local,path=bin,mount_tag=bin,security_model=mapped-xattr \
	#	-drive file=ncvm-interface-test.img,if=virtio,format=raw \
	#	-cdrom Fedora-Server-dvd-x86_64-42-1.1.iso
}

ShellIntoVM() {
	until ssh -p 2222 localhost exit > /dev/null 2>&1; do
		echo "Please wait for VM to come up."
		sleep 1
	done

	# Start xterm if it isn't already running.
	if ! ps -ef | grep "xterm" | grep -q "ncvm-debugging"; then
		echo "Starting ssh..."
		xterm -xrm 'XTerm.vt100.allowTitleOps: false' \
			-T "ncvm-debugging" \
			-bg darkblue \
			-fg yellow \
			-geometry 50x15+200+20 \
			-fa 'Monospace' \
			-fs 14 \
			-bc \
			-e ssh -p 2222 localhost &
	fi
}

startNCVM() {
	#TODO Kill ncvm then remove bin/ncvm, then copy
	ssh -p 2222 localhost killall -q ncvm
	ssh -p 2222 localhost rm -f bin/ncvm
	scp -P 2222 bin/ncvm localhost:/home/jwicks/bin/
	# Kill ncvm on remote and allow autologin and .bash_pofile to start the new one.
	p=$(ssh -p 2222 localhost ps -A | grep tty1 | cut -d \t -f 1)
	ssh -p 2222 localhost kill -9 "$p"
}

while getopts ":rstk" opt; do
	case ${opt} in
    r)
		runVM&
		;;
    s)
		runVM&
		ShellIntoVM
		;;
	t)
		runVM&
		ShellIntoVM
		startNCVM
		;;
	k)
		ssh -p 2222 localhost rm -f bin/ncvm
		ssh -p 2222 localhost sudo poweroff
		exit 0
		;;
    :)
		echo "Option -${OPTARG} requires an argument."
		exit 1
		;;
	esac
done






