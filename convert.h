#ifndef CONVERT_H
#define CONVERT_H

#include <seq.h>
#include <stdio.h>
#include <stdlib.h>

// main function, calls all others 
void convert(Seq_T *data);

void writeHeader(Seq_T *data, FILE *output);

void writeRaster(Seq_T *data, FILE *output);

#endif