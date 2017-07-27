#!/bin/sh

set -e

source ./build.config

if [ ! -d "lib/nbavr/" ]; then
    git clone https://github.com/xenris/nbavr.git lib/nbavr/
fi

tup

avr-size gen/firmware.elf -C --mcu=$mcu

elf="gen/firmware.elf"

if [ "${1}" = "-u" ]; then
    pkill picocom && sleep 1 || true

    avrdude -p $mcu -P $port -c $programmer -e -U flash:w:$elf
elif [ "${1}" == "-d" ]; then
    hash avr-gdb 2>/dev/null || { echo >&2 "avr-gdb is needed for debugging but it's not installed."; exit 1; }
    hash simavr 2>/dev/null || { echo >&2 "simavr is needed for debugging but it's not installed."; exit 1; }
    hash kdbg 2>/dev/null || { echo >&2 "kdbg is needed for debugging but it's not installed."; exit 1; }

    simavr -g -v -t -m $mcu -f $freq $elf &
    kdbg -r localhost:1234 $elf

    pkill simavr
elif [ "${1}" == "-s" ]; then
    hash simavr 2>/dev/null || { echo >&2 "simavr is not installed."; exit 1; }

    echo "---------------------------------"
    echo "Exit simulation with ctrl + c"
    echo "---------------------------------"

    simavr -v -v -t -m $mcu -f $freq $elf
elif [ "${1}" == "-p" ]; then
    hash picocom 2>/dev/null || { echo >&2 "picocom is not installed."; exit 1; }

    echo "---------------------------------"
    echo "Exit picocom with ctrl+a -> ctrl+x)"
    echo "---------------------------------"

    picocom --imap lfcrlf --omap crlf $pico_port
fi
