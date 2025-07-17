#!/bin/bash

virt-install \
    --name TinyCoreA \
    --description "TinyCoreA.img is small." \
    --os-variant=linux2024 \
    --ram=512 \
    --vcpus=1 \
    --disk path=/opt/ISO/TinyCoreA.img \
    --graphics none \
    --import \
    --network network=default,model=virtio
