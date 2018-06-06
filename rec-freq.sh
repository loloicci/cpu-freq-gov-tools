#!/bin/bash

INTERVAL=0.1 # seconds
OUT=./out.csv
TIME=300
CORE=8


usage_exit() {
    echo "Usage: $0 [-h] [-i interval sec] [-t time sec] [-o output file] commands" 1>&2
    exit 1
}

echo_first_line() {
    OUTPUT="time"
    for c in $(seq 0 1 $CORE)
    do
        OUTPUT="$OUTPUT, cpu${c} (`tail -1 /sys/devices/system/cpu/cpu${c}/cpufreq/scaling_governor`)"
    done
    echo $OUTPUT
}

echo_freqs() {
    OUTPUT="`date +%H%M%S.%3N`, "
    for c in $(seq 0 1 $CORE)
    do
        OUTPUT="$OUTPUT, `tail -1 /sys/devices/system/cpu/cpu${c}/cpufreq/scaling_cur_freq`"
    done
    echo $OUTPUT
}

while getopts :o:i:t:c:h OPT
do
    case $OPT in
        o)  OUT=$OPTARG
            ;;
        i)  INTERVAL=$OPTARG
            ;;
        t)  TIME=$OPTARG
            ;;
        c)  CORE=$OPTARG
            ;;
        h)  usage_exit
            ;;
        \?) usage_exit
            ;;
    esac
done

shift $((OPTIND - 1))
CORE=$(($CORE - 1))
INTERVAL=`echo "$INTERVAL - 0.01" | bc`
echo $INTERVAL

echo_first_line > $OUT

NOW=0

echo "start: $@"
$@ &

for i in $(seq 0 $INTERVAL $TIME)
do
    echo_freqs >> $OUT &
    sleep $INTERVAL
done

echo "rec-freq: Done."
