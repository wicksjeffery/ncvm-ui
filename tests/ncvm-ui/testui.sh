#!/bin/bash

if [ "$#" -eq 0 ]; then
	echo "usage: ncvm-ui -t"
	exit 0
fi


startXterm() {
	# Start xterm if it isn't already running.
	if ! ps -ef | grep "xterm" | grep -q "ncvm-ui"; then
		echo "Starting xterm..."
		xterm -xrm 'XTerm.vt100.allowTitleOps: false' \
			-T "ncvm-ui" \
			-geometry 80x30 \
			-bc \
			-e bin/ncvm-ui
	fi
}


while getopts ":t" opt; do
	case ${opt} in
	t)
		startXterm
		;;
    :)
		echo "Option -${OPTARG} requires an argument."
		exit 1
		;;
	esac
done






