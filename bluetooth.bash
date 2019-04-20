#!/bin/bash
# Bluetooth Script

# Run bluetoothctl as a coprocess
coproc BT { bluetoothctl; }

# Get the file descriptors to communicate
BTOUT="${BT[0]}"
BTIN="${BT[1]}"

# Start the scan
echo "scan on" >&"$BTIN"

# Parse devices until the correct one is found
while true; do
	echo "devices" >&"$BTIN"
	while read a b c BTADDR DEV <&"$BTOUT"; do
		echo "$DEV"
		if [[ "$DEV" == "Xbox Wireless Controller" ]]; then
			break
		fi
	done
	if test -n "$BTADDR"; then
		echo "$BTADDR"
		break
	fi
done

# Stop the scan
echo "scan off" >&"$BTIN"

# Connect to the address
echo "trust $BTADDR" >&"$BTIN"
echo "pair $BTADDR" >&"$BTIN"
echo "connect $BTADDR" >&"$BTIN"

# Quit
while true; do
	read p STATUS <&"$BTOUT"
	echo "${STATUS}"
	if [[ "${STATUS}" == *"Connection successful" ]]; then
		sleep 5s
		if [[ "${STATUS}" == *"Connection successful" ]]; then
			echo "Connected!"
			break
		else
			echo "Connection problem, re-connecting..."
			echo "remove $BTADDR" >&"$BTIN"
			echo "connect $BTADDR" >&"$BTIN"
		fi
	fi
done
echo "quit" >&"$BTIN"
