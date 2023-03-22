#!/usr/bin/env bash

set -Eeuo pipefail

nodes=()

case $1 in
	simple)
		echo "running simple case"
		nodes=(3000 3001 3002)
		cp Node.py simple
		cd simple
		;;

	first)
		echo "running first case"
		nodes=(3000 3001 3002 3003 3004 3005)
		cp Node.py first
		cd first
		;;
	second)
		echo "running second case"
		nodes=(3000 3001 3002 3003)
		cp Node.py second
		cd second
		;;
	third)
		echo "running third case"
		nodes=(3000 3001 3002 3003 3004 3005 3006 3007 3008 3009 3010)
		cp Node.py third
		cd third
		;;
	my_case1)
		echo "running my_case_1"
		nodes=(3000 3001 3002 3003 3004 3005 3006 3007 3008)
		cp Node.py my_case1
		cd my_case1
		;;
	my_case2)
		echo "running my_case_2"
		nodes=(3000 3001 3002 3003 3004 3005 3006 3007 3008)
		cp Node.py my_case2
		cd my_case2
		;;
	my_case3)
		echo "running my_case_3"
		nodes=(3000 3001 3002 3003 3004 3005 3006)
		cp Node.py my_case3
		cd my_case3
		;;
	my_case4)
		echo "running my_case_4"
		nodes=(3000 3001 3002 3003)
		cp Node.py my_case4
		cd my_case4
		;;
	*)
		echo 'Select from the list of tests or edit the script'
		printf '\t%s\n' "simple"
		printf '\t%s\n' "first"
		printf '\t%s\n' "second"
		printf '\t%s\n' "third"
		printf '\t%s\n' "my_case1"
		printf '\t%s\n' "my_case2"
		printf '\t%s\n' "my_case3"
        	exit
		;;
esac

for port in "${nodes[@]}"; do
    (python3 Node.py "${port}") &
done

sleep 0.1
wait $(jobs -p)
echo "All done"
