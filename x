#!/bin/sh

hawk  -e 'BEGIN { i=0; }
  { i = i + 1; }
  END { print(i); }' /export/labs/bigfile
#END { print(i); }' /export/labs/file3
