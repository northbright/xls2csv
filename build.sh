#!/bin/sh

wget http://downloads.sourceforge.net/libxls/libxls-0.2.0.tar.gz
tar -xzvf libxls-0.2.0.tar.gz
cd libxls-0.2.0
./configure
make
sudo make install

cd ../
gcc -o ./src/xls2csv ./src/*.c -I/usr/local/libxls/include -L/usr/local/libxls/lib -lxlsreader
