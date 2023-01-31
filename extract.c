#include <stdio.h>
#include <stdlib.h>
#include <except.h>

Except_T CRE;

void extract(int argc, char *argv[]) {

         if (argc > 2) {
                RAISE(CRE);
        }

        char string[80];
        char *input = string; 

        FILE *inputfd;

        if (argc == 2) {
                input = argv[1];
                inputfd = fopen(input, "r");
        }

        else { // TODO
                //scanf("%s", input);
                //inputfd = stdin; 
        }

        

        
}

