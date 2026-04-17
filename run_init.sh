#!/bin/sh

sleep 3

mount -o remount,rw /userdata

echo "--- System Boot Launch ---" >> /userdata/debug.log
date >> /userdata/debug.log

/userdata/rv1106_ipc >> /userdata/debug.log 2>&1 &