#ifndef DECODER_H
#define DECODER_H

#include <seq.h>

// main function, calls all others
void decode(Seq_T *data);

// uses getNonDigits() to find infused char sequence 
const char *findInfusion(Seq_T *data); 

// returns char array of all non-digits in a single sequence
char *getNonDigits(Seq_T *data, int idx);

// removes fake rows and cleans real rows, replaces data with a new data sequence
Seq_T *cleanData(Seq_T *data, const char *infusion);

// remove any non-digit sequences in a row, replaces row with a new row that has
// one whitespace char between each digit
Seq_T *cleanRow(Seq_T *data, int idx);

// returns 1 if nondigits in row don't match infusion, 0 if they do
int isFake(Seq_T *data, int idx, const char *infusion);


#endif