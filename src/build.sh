#!/bin/sh

gcc -o xls2csv *.c -I/usr/local/libxls/include -L/usr/local/libxls/lib -lxlsreader
