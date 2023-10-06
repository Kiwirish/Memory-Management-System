#!/bin/bash

sudo rmmod memdrv

make
sudo insmod memdrv.ko
sudo chown mal:mal /dev/memdrv

