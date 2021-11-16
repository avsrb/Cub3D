# !/bin/bash
while true; do
	cub3D_pid=$(pgrep cub3D)
	if [ -n "$cub3D_pid" ]
	then
		leaks_result=$( leaks -q --list cub3D ) 
		echo "                                 LEAKS CHECK"
		echo "$leaks_result"
	fi
	sleep 3
	clear
done
