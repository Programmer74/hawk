#!/bin/sh

hawk  -e '
  { ORS="";  print($0); }
  ' /export/labs/bigfile
