#!/bin/bash

CORE=8

usage_exit() {
    echo "Usage: $0 [-h] [-c core count] mode" 1>&2
    exit 1
}

while getopts :c:h OPT
do
    case $OPT in
        c)  CORE=$OPTARG
            ;;
        h)  usage_exit
            ;;
        \?) usage_exit
            ;;
    esac
done

CORE=$(($CORE - 1))

for i in $(seq 0 1 $CORE)
do
    echo "cpufreq-set -c $i -g $1"
    cpufreq-set -c $i -g $1
done
