# xls2csv

[![Build Status](https://travis-ci.org/northbright/xls2csv.svg?branch=master)](https://travis-ci.org/northbright/xls2csv)

xls2csv is a program which converts XLS files to CSV files. It's based on `xls2csv.c` of [libxls](http://libxls.sourceforge.net/).

#### Features
* Specify sheet by given sheet ID.
* Convert CSV in the same way as Excel's "Save as CSV".
  * Use ',' as separator.
  * No "" for string.
  * Keep data if rowspan > 1(original xls2csv.c will stop and return).

#### Build
* Run `./build.sh` to get `./src/xls2csv`.

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
* Thanks powerful [libxls](http://libxls.sourceforge.net/) to give it a chance that we can still operate on XLS file.

