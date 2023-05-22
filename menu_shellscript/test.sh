#!/usr/bin/env bash

CONFIG_FILE="./.menuConfig"
validCodes=("1234" "4321")
USERNAME=""

isValidCode() {
	# Returns 0 if code is valid, 1 otherwise
	# "$1": The code to check
	code="$1"
	# DEBUG: echo "isValidCode: Checking: $1"
	for validCode in "${validCodes[@]}"; do
		if [[ "$code" == "$validCode" ]]; then
			return 0
		fi
	done
	return 1
}

login() {
	# Returns 0 if login success, 1 otherwise
	read -p "Enter Username: " USERNAME
	read -sp "Enter Code: " pw
	isValidCode "$pw"
	isValid=$?
	if [[ isValid -eq 0 ]]; then
		return 0
	else
		return 1
	fi
}

options=("Echo Name" "Echo Config File" "Quit")

# LOGIN CHECK
login
loginSuccess=$?
if [[ loginSuccess -eq 0 ]]; then
	echo "Welcome, $USERNAME."
else
	echo "Invalid code."
	exit
fi

# OPTIONS
select answer in "${options[@]}"
do
	case "${answer}" in
		"Echo Name")
			echo "Your username is $USERNAME."
		;;
		"Echo Config File")
			cat "${CONFIG_FILE}"
		;;
		"Quit")
			break
		;;
		*)
			echo "Unknown command, please try again."
		;;
	esac
done
