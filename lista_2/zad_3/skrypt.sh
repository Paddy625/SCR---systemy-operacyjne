#!/bin/bash

find /home/adam/SCR -type f -name "*$1" -mtime -"$2" -exec tar -rvf "$3.tar" {} \;
