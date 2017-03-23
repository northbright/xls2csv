#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

#include "xls2csv.h"

const char *usage = "Usage: xls2csv [XLS file] [-s sheet ID(0-based)] [-o CSV File]";
const char *example = "Example: xls2csv my.xls -s 2 -o my.csv";

int main(int argc, char *argv[]) {
    int oc;
    char ec;
    char *optArg;
    char *xlsFile = NULL;
    char *csvFile = NULL;
    int nSheetId = 0;
    int fInvalidArgs = 0;
    int nRet = EXIT_FAILURE;
    char *buf = NULL;
    FILE *f = NULL;
    opterr = 0;
    
    // Use getopt() to parse args.
    while((oc = getopt(argc, argv, ":s:o:")) != -1) {
        switch(oc) {
            case 's':
                nSheetId = atoi(optarg);
                break;

            case 'o':
                csvFile = optarg;
                break;

	    case '?':
	        fInvalidArgs = 1;
	        ec = (char)optopt;
		printf("Invalid arg: %c.\n", ec);
		goto end;

	    case ':':
		fInvalidArgs = 1;
	        printf("Missing argument.\n");
                goto end;

	    default:
		fInvalidArgs = 1;
	        printf("Unknown argument.\n");
		goto end;
        }
    }

    // Check if XLS file is specified.
    // After getopt() exited, optind is where non-opt arg begins.
    if (optind != argc - 1) {
	fInvalidArgs = 1;
        printf("Please specify one(and only one) XLS file.\n");
	goto end;
    }

    // Get XLS file name.
    xlsFile = argv[optind];

    // Call xls2csv() to get CSV string.
    buf = xls2csv(xlsFile, nSheetId);
    if (buf == NULL) {
	goto end;
    }

    // Just output CSV string to stdout if no CSV file arg specified.
    if (csvFile == NULL) {
	printf(buf);
	nRet = EXIT_SUCCESS;
	goto end;
    }

    // Write converted CSV string to output CSV file.
    if (strlen(csvFile) == 0) {
	printf("CSV file name is empty.\n");
	goto end;
    }

    f = fopen(csvFile, "w");
    if (f == NULL) {
	printf("Open CSV file: %s failed.\n", csvFile);
	goto end;
    }

    fputs(buf, f);

    if (fclose(f) != 0) {
	printf("Close CSV file: %s failed.\n", csvFile);
	goto end;
    }

    nRet = EXIT_SUCCESS;

end:
    if (fInvalidArgs) {
        printf("%s\n%s\n", usage, example);
    }

    if (buf != NULL) {
	free(buf);
	buf = NULL;
    }

    return nRet;
}
