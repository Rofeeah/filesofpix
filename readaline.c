#include "readaline.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <except.h>

Except_T ERROR;

size_t readaline(FILE *inputfd, char **datapp)
{
        if ((datapp == NULL)) {
                RAISE(ERROR);
        }

        if ((inputfd == NULL)) {
                RAISE(ERROR);
        }

        int cap = 2;
        int seekPtr = 0;

        *datapp = (char*)malloc(cap * sizeof(char));

        if (datapp == NULL) {
                RAISE(ERROR);
        }

        char test;

        int i = 0;
        
        while(test != '\n') {
                test = getc(inputfd);
                if (test == EOF) {
                        datapp = NULL; 
                        return 0;
                }

                if (i >= cap) {
                        cap = cap * 2;
                        *datapp = realloc(*datapp, cap);
                        if (datapp == NULL) {
                                RAISE(ERROR);
                        }
                }

                (*datapp)[i] = test;

                i++;
                seekPtr++;
        }

        cap = i;
        *datapp = realloc(*datapp, cap);

        // for (int p = 0; p < cap; p++) {
        //         printf("%c, ", (*datapp)[p]);
        // }

        size_t x = (size_t) cap;

        // printf("\n x is: %ld\n", x);
        return x;
}
