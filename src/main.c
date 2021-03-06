#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

#include "xls2csv.h"

const char *usage = "Usage:\nxls2csv [XLS file] [-s sheet ID] [-o CSV File]\n-s sheet ID. It's 0-based. Default is 0 if no sheet id specifed.\n-o CSV file to output. If no CSV file is specified, it'll output CSV string to stdout.";
const char *example = "Example:\nxls2csv my.xls\nxls2csv my.xls -s 2 -o my.csv";

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

    // Disable getopt() output error message.
    opterr = 0;
    
    // Use getopt() to parse args.
    // int getopt(int argc, char * const argv[], const char *optstring);
    // params:
    //   optstring:
    //     "x:" means '-x' option should have argument.
    //     "x::" means '-x' option may have argument or not(optional).
    //           In this case, there should NOT be spaces between option and argument. Ex: "-xArg".
    //   if optstring starts with ":", it'll make getopt():
    //     1. not output error messages
    //     2. return '?' if there's invalid option.
    //     3. return ':' if argument if missing for the option.
    //
    // global variables used by getopt():
    // 1. opterr - set to 0 to disable output error messages.
    // 2. optarg - after each call of getopt() it's the argument of specified option(pointer to argv[].
    // 3. optind - after getopt() return -1, argv[] will be re-sorted, non-option arguments will be put to the end of argv[]. optind is the index of first non-option argument.
    //    We can use optind to find all non-option arguments.
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
