#!/bin/bash

now="$(date +%u)"

if [ $now -gt 5 ]
then
    echo 'Jest weekend!'
else
    echo 'Tydzień pracy'
fi
