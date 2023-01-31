#include "readaline.h"
#include "decoder.h"
#include "convert.h"


#include <stdio.h>
#include <stdlib.h>
#include <except.h>
#include <seq.h>

Except_T CRE;

void convertToSeq(char **datapp, Seq_T *data, size_t size);
int main(int argc, char *argv[])
{
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
                // scanf("%s", input);
                inputfd = stdin; 
        }

        Seq_T data; 
        data = Seq_new(0);

        int run = 1;
        while (run) {
                char *datapp;
                run = readaline(inputfd, &datapp);
                // printf()
                convertToSeq(&datapp, &data, run);

                // free (datapp);

        }

        // for (int p = 0; p < Seq_length(data); p++) {
        //         printf("About to print a sequence of length %d\n", Seq_length(Seq_get(data, p)));

        //         for (int i = 0; i < Seq_length(Seq_get(data, p)); i++) {

        //                 char *saver = Seq_get(Seq_get(data, p), i);
        //                 printf("here is what's in data[%d][%d]: %c\n", p, i, *saver);
        //         }
        // }

        printf("\nwe have returned\n");

        fclose(inputfd);


        // extract(int argc, char *argv[]);

        decode(&data); 
        convert(&data);

        return 0;
}

void convertToSeq(char **datapp, Seq_T *data, size_t size) {

        // printf("Converting new sequence of size %ld.\n", size);
        Seq_T tempSeq;
        tempSeq = Seq_new(0);
        
        
        for (size_t i = 0; i < size; i++) {
                Seq_addhi(tempSeq, &(*datapp)[i]); // possible problem here
                // printf("here is what's in datapp[%ld]: %c\n", i, (*datapp)[i]); 

        }

        Seq_addhi(*data, tempSeq);

        // printf("this is the big seq_lenth: %d \n", Seq_length(data));

        // for (int i = 0; i < Seq_length(tempSeq); i++) {
        //         char *saver = Seq_get(tempSeq, i);
        //      printf("here is what's in the sequence[%d]: %c\n", i, *saver);
        // }

        // printf("-----Data has a length of------- %d.\n", Seq_length(*data));

        // for (int p = 0; p < Seq_length(*data); p++) {
        //         printf("About to print a sequence of length %d\n", Seq_length(Seq_get(*data, p)));

        //         for (int i = 0; i < Seq_length(Seq_get(*data, p)); i++) {

        //                 char *saver = Seq_get(Seq_get(*data, p), i);
        //                 printf("here is what's in data[%d][%d]: %c\n", p, i, *saver);
        //         }
        // }
}