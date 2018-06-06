####################
 cpu-freq-gov-tools
####################

Utilities for tuning cpu freq governor.

**********
 chgov.sh
**********

A script for changing governor of each cpu.

Dependency
==========
* cpufreq-set
  install with `apt install cpufrequtils`

Usage
=====
`sudo ./chgov.sh [-h] [-c number of your cpu's cores] governor-name`

* `-c`
  Default value is `8`.

*************
 rec-freq.sh
*************

A script for recording cpu frequency.

Usage
=====
`./rec-freq.sh [-h] [-i interval sec] [-t end sec] [-o output file] [-c number of your cpu's cores] commands`

* `-i`
  Default value is `0.1`.
  Actually, time to sleep is used `(value of -i) - 0.01`.

* `-t`
  Default value is `300`.

* `-o`
  Default value is `out.csv`.

* `-c`
  Default value is `8`.

* `commands`
  Executed when the script starts.

Output
======
CPU frequency is recorded in csv format.

example: ::

  time, cpu0 (ondemand), cpu1 (ondemand), cpu2(ondemand), cpu3(ondemand), cpu4(ondemand)
  123456.789, 14000, 14000, 14000, 14000

the value in parentheses is the governor used for the cpu.
`time` is in format `%H%M%S.%3N`.
