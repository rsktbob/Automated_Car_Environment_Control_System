#!/bin/bash

DEVICE="/dev/ttyACM0"
BAUDRATE="9600"

if [ ! -e "$DEVICE" ]; then
    echo "Device $DEVICE not found. Please check the connection."
    exit 1
fi

stty -F "$DEVICE" "$BAUDRATE"

echo "Reading from $DEVICE at baud rate $BAUDRATE..."
while IFS= read -r line; do
    echo "$line"
done < "$DEVICE"