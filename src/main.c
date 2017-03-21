#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

#include "xls2csv.h"

const char *usage = "Usage: xls2csv [-x XLS file] [-c CSV file] [-s sheet ID]";

int main(int argc, char *argv[]) {
    int oc;
    char ec;
    char *opt_arg;
    char *xls_file = NULL;
    char *csv_file = NULL;
    int nSheetId = 0;

    opterr = 0;

    while((oc = getopt(argc, argv, ":x:c:s:")) != -1) {
        switch(oc) {
	    case 'x':
		xls_file = (char*)calloc(strlen(optarg) + 1, sizeof(char));
                strcpy(xls_file, optarg);
		break;
 
            case 'c':
                csv_file = (char*)calloc(strlen(optarg) + 1, sizeof(char));
                strcpy(csv_file, optarg);
                break;

            case 's':
		nSheetId = atoi(optarg);
		break;

	    case '?':
	        ec = (char)optopt;
		printf("Invalid arg: %c.\n", ec);
		break;

	    case ':':
	        printf("Missing argument.\n");
		break;

	    default:
	        printf("Unknown argument.\n");
        }
    }

    printf("xls_file: %s, csv_file: %s, nSheetId: %d\n", xls_file, csv_file, nSheetId);

end:
    if (xls_file != NULL) {
        free(xls_file);
        xls_file = NULL;
    }
}
