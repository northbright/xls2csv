#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdarg.h>

#include "appendstr.h"

// appendStr increases the size of buffer to append formated string.
// Params:
//   buf: pointer to the existed allocaled buffer which stores original string or NULL(for 1st time).
//   fmt: format like the one in printf().
// Return:
//   Pointer to the buffer stored new string.
//   It'll call realloc() to change the buffer size internally.
//   Old buffer will be released during realloc() after memory block is moved if it's not large enough.
//   So caller should free the returned buffer after use.
// Example:
//   int main() {
//       char *buf = NULL;
//
//       // Pass NULL pointer for the 1st time.
//       buf = appendStr(NULL, "%d", 1);
//       buf = appendStr(buf, "%f", 3.14);
//       buf = appendStr(buf, "Hello World!")
//
//       free(buf);
//   }
char *appendStr(char *buf, char *fmt, ...) {
    int n, nBytes, l = 0;
    char *newBuf, *tmpBuf = NULL;
    va_list args1, args2;
    char fixedBuf[64] = {0};
    char *inputStr = fixedBuf;

    va_start(args1, fmt);
    va_copy(args2, args1);

    // Get formated input string buffer.
    // If n > 0 and n <= sizeof(fixedBuf), vsnprintf() succeeded,
    // n = the size of formated string(not including '\0').    
    n = vsnprintf(fixedBuf, sizeof(fixedBuf), fmt, args1);

    if (n < 0) {
        printf("appendStr(): vsnprintf() return < 0: %d\n", n);
        goto end;
    }

    // Fixed buffer is not large enough.
    // n = the size of formated string(not including '\0').
    // Use malloc() to allocate a new buffer to store formated input string.
    if (n > sizeof(fixedBuf)) {
        tmpBuf = malloc(sizeof(char) * (n + 1));
        if (tmpBuf == NULL) {
            printf("appendStr() error: tmpBuf = malloc(%d) failed.\n", n + 1);
            goto end;
        }

        nBytes = vsnprintf(tmpBuf, n + 1, fmt, args2);
        if (nBytes != n) {
            printf("appendStr() error: vsnprintf() nBytes(%d) != n(%d)\n", nBytes, n);
            goto end;
        }

        // Make inputStr point to dynamic buffer.
        inputStr = tmpBuf;
    }

    if (buf == NULL) {
        l = 0;
    } else {
        l = strlen(buf);
    }

    // Reallocate buffer to store new string.
    newBuf = realloc(buf, l + n + 1);
    if (newBuf == NULL) {
        printf("appendStr() error: realloc() failed.\n");
        goto end;
    }

    memcpy((void *)(newBuf + l), (void *)inputStr, n);
    memset((void *)(newBuf + l + n), 0, 1);

end:
    if (tmpBuf != NULL) {
        free(tmpBuf);
        tmpBuf = NULL;
    }

    va_end(args1);
    va_end(args2);

    return newBuf;
}
