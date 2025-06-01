#!/bin/bash

function printHeader() {
    clear
    echo "Press \"c\" to build or \"t\" to test it."
}

printHeader

while true
do
    read -n 1 -s -r input

    case $input in
        [Cc]* )
            printHeader
            make
            continue;;
        [Tt]* )
            printHeader
            bin/ncvm
            exit;;
        [Qq]* )
            exit;;
        * ) echo "Invalid";;
    esac
done
