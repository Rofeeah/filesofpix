#include "convert.h"

#include <seq.h>
#include <stdio.h>
#include <stdlib.h>


// main function, calls all others 
void convert(Seq_T *data)
{
        printf("got here\n");
        for (int i = 0; i < Seq_length(*data); i++) {
                for (int p = 1; p < Seq_length(Seq_get(*data, i)); p++) {
                        char *saver = Seq_get(Seq_get(*data, i), p);
                        printf("%c,", *saver);
                }       
                printf("\n");
        }

        

        writeHeader(data, stdout);
        writeRaster(data, stdout);
        


}

void writeHeader(Seq_T *data, FILE *output)
{
        int height = Seq_length(*data); 
        int length = Seq_length(Seq_get(*data, 0)) - 1;
        int maxVal = 255; 
        char magicNum[] = "P5";
        

        printf("Here is the height: %d, and length: %d\n", height, length);
        
        printf("\n");
        putc('P', output);
        printf("\n");

}

void writeRaster(Seq_T *data, FILE *output)
{


}
