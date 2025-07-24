# xls2csv

[![Build Status](https://travis-ci.org/northbright/xls2csv.svg?branch=master)](https://travis-ci.org/northbright/xls2csv)

Update: This program is broken and just use the [xls2csv.c](https://github.com/libxls/libxls/blob/dev/src/xls2csv.c) comes from latest [libxls](https://github.com/libxls/libxls/).

xls2csv is a program which converts XLS files to CSV files. It's based on `xls2csv.c` of [libxls](https://github.com/libxls/libxls/).

#### Features
* Specify sheet by given sheet ID.
* Convert CSV in the same way as Excel's "Save as CSV".
  * Use ',' as separator.
  * No "" for string.
  * Keep data if rowspan > 1(original xls2csv.c will stop and return).

#### Build
* xls2csv requires [libxls](https://github.com/libxls/libxls/) to be installed.
  * Install libxls
        
          wget http://downloads.sourceforge.net/libxls/libxls-0.2.0.tar.gz
          tar -xzvf libxls-0.2.0.tar.gz
          cd libxls-0.2.0
          ./configure
          make
          sudo make install
  * Add libxls lib path to `LD_LIBRARY_PATH`
    * Create a new `/etc/ld.so.conf.d/libxls.conf`
    
              sudo vi /etc/ld.so.conf.d/libxls.conf

              // Add path of libxls to this file
              /usr/local/libxls/lib

    * Update `LD_LIBRARY_PATH`

            sudo ldconfig
            // Check libxlsreader.so
            sudo ldconfig -p | grep libxls

* Build xls2csv

        git clone https://github.com/northbright/xls2csv.git
        cd xls2csv/src
        gcc -o xls2csv *.c -I/usr/local/libxls/include -L/usr/local/libxls/lib -lxlsreader

#### Usage
    xls2csv [XLS file] [-s sheet ID(0-based)] [-o CSV File]
    
    -s sheet ID. It's 0-based. Default is 0 if no sheet id specifed.
    -o CSV file to output. If no CSV file is specified, it'll output CSV string to stdout.

#### Example:
    xls2csv my.xls 
    xls2csv my.xls -s 2 -o my.csv

#### License
* [MIT License](./LICENSE)

#### Thanks
* Thanks powerful [libxls](https://github.com/libxls/libxls/) to give it a chance that we can still operate on XLS file.

