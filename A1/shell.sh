#!/bin/sh
echo "BismiAllah"
last --since '-30 days' | awk {'print $1'} | sort | uniq -c | sort -g | tail -1 | awk {'print $2 " " $1'}