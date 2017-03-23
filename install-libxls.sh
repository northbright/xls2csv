#! /usr/bin/env sh

wget http://downloads.sourceforge.net/libxls/libxls-0.2.0.tar.gz
tar -xzvf libxls-0.2.0.tar.gz
cd libxls-0.2.0
./configure
make
