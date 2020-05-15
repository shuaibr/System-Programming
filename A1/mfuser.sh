#!/bin/sh
last --since '-1 month' | awk {'print $1'} | sort | uniq -c | sort -g | tail -1 | awk {'print $1 " " $2'}