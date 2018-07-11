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
**You shold use rec-freq.c insted of this.**

Usage
=====
``./rec-freq.sh [-h] [-i interval sec] [-t end sec] [-o output file] [-c number of your cpu's cores] commands``

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

  time, cpu0 (ondemand), cpu1 (ondemand), cpu2(ondemand), cpu3(ondemand)
  123456.789, 14000, 14000, 14000, 14000

the value in parentheses is the governor used for the cpu.
`time` is in format `%H%M%S.%3N`.

************
 rec-freq.c
************

A program for recording cpu frequency.

Usage
=====
``./rec-freq.o [-h] [-i interval micro sec] [-t end mili sec] [-o output file] [-c number of your cpu's cores]``

* `-i`
  Default value is `8000`.
  The actual interval is a little longer than this.

* `-t`
  Default value is `300000`.

* `-o`
  Default value is `out.csv`.

* `-c`
  Default value is `8`.

Output
======
CPU frequency is recorded in csv format.

example: ::

  time, cpu0 (ondemand), cpu1 (ondemand), cpu2(ondemand), cpu3(ondemand)
  XXX.XXXXXXXXX, 14000, 14000, 14000, 14000

the value in parentheses is the governor used for the cpu.
`time` is in format (`ld.%9ld`, ts.tv_sec, ts.tv_nsec).

**************
 plot_freq.py
**************
A program to make a graph of CPU freqency from csv whose format
is same as output of ``rec-freq.c``.
This programm has a cheap function to calculate the arithmetic mean of the
frequencies.

Dependency
==========
* Python2
* matplotlib

Usage
=====
``python plot_freq [input_file_path] [option: time] [option: line]``

* ``[input_file_path]``
  Path to input csv file

* ``[option: time]``
  If this parameter is given,
  this program print the simple arithmetic mean of the frequencies
  until the given time.

* ``[option: line]``
  This is *the third arg* so time is needed when you give this parameter.
  When you give the parameter, parameter ``time`` is ignored.
  If this parameter is given,
  this program print the simple arithmetic mean of the frequencies
  until the given line.
