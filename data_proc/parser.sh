#!/bin/bash
if [[ $# -ne 1 ]]; then
  echo "give data log file"
  exit 1
fi

# remove first line (garbage) and keep only
# measurements and possible GPS data
sed '1d' < $1 | grep -E 'GPRMC|m:' > temp
