#!/bin/bash

trap 'echo "zostal uzyty trap"' INT QUIT FPE ILL

while true
do
    echo -n "#"
    date
    sleep 1
done
