#!/bin/sh

wget http://downloads.sourceforge.net/libxls/libxls-0.2.0.tar.gz
tar -xzvf libxls-0.2.0.tar.gz
cd libxls-0.2.0
./configure
make

cd ../
gcc -o ./src/xls2csv ./src/*.c -I./libxls-0.2.0/include -L./libxls-0.2.0/src/.libs -lxlsreader
