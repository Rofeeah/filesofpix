#include <stdio.h>
#include <stdlib.h>
#include <except.h>

#include <seq.h>
#include <set.h>
#include <atom.h>

#include <ctype.h>
#include <string.h>

#include "decoder.h"

Except_T BAD;
void decode(Seq_T *data) 
{
        const char *infusion = findInfusion(data);
        *data = *cleanData(data, infusion);
        
}

// uses getNonDigits() to find infused char sequence 
// might not be checking empty rows -> put a condition to check 
const char *findInfusion(Seq_T *data) 
{
        Set_T checked = Set_new(0, NULL, NULL);

        const char *nonDigits;

        for (int i = 0; i < Seq_length(*data); i ++) { 
                nonDigits = getNonDigits(data, i);
                // printf("here is nonDigits: %s\n", nonDigits);
                nonDigits = Atom_string(nonDigits);
                // printf("print the set memeber check value %d \n", Set_member(checked, nonDigits));
                if (Set_member(checked, nonDigits)) {
                        // printf("found it!! returning: %s\n", nonDigits);
                        return nonDigits;
                }
                else {
                        // printf("didn't find it, here's nondigits: %s\n", nonDigits);
                        Set_put(checked, nonDigits);
                }
        }

        return nonDigits;
}


// returns char array of all non-digits in a single sequence
char *getNonDigits(Seq_T *data, int idx)
{
        int cap = 1;
        char *nonDigits = (char*)calloc(cap, sizeof(char));
        int count = 0;

        for (int i = 0; i < Seq_length(Seq_get(*data, idx)); i++) {
                char *saver = Seq_get(Seq_get(*data, idx), i);
                if (!isdigit(*saver) && !isspace(*saver)) {
                        if (count >= cap) {
                                cap = cap * 2;
                                nonDigits = realloc(nonDigits, cap);
                                if (nonDigits == NULL) {
                                        RAISE(BAD);
                                }
                         }

                        nonDigits[count] = *saver;
                        count++;
                }
        }    

        return nonDigits;
}

// returns 1 if nondigits in row don't match infusion, 0 if they do
int isFake(Seq_T *data, int idx, const char *infusion)
{
        const char *rowInfusion = getNonDigits(data, idx);
        if (strcmp(rowInfusion, infusion) == 0) {
                return 0;
        }
        return 1;
}

// removes fake rows and cleans real rows
Seq_T *cleanData(Seq_T *data, const char *infusion) 
{
        Seq_T fake = Seq_new(0); 
        Seq_T *newData = &fake;

        for (int i = 0; i < Seq_length(*data); i++) {
                // printf("Checking row %d\n", i);
                if (!isFake(data, i, infusion)) {
                        Seq_T *newRow = cleanRow(data, i);
                        for (int p = 0; p < Seq_length(*newRow); p++) {
                                char *saver = Seq_get(*newRow, p);
                                // if (isspace(*saver)) { 
                                //         printf("(found space: )");
                                // }
                                printf("%c,", *saver);
                        }
                        Seq_addhi(*newData, *newRow);
                }
        }

        printf("\nStarting new printout of newData:\n");

        // newData is not reflecting our newRow changes
        // it does show that there is a value -> NULL 
        // but it does not have the value -> space or 32
        for (int i = 0; i < Seq_length(*newData); i++) {
                for (int p = 1; p < Seq_length(Seq_get(*newData, i)); p++) {
                        char *saver = Seq_get(Seq_get(*newData, i), p);
                        if (isspace(*saver)) { 
                                printf("(space: )"); 
                        }
                        printf("%c,", *saver);
                }       
                printf("\n");
        }

        /* Clean up data here */
        // data = newData;

        return newData;
}

// remove any non-digit sequences in a row, replaces row with a new row that has
// one whitespace char between each digit
Seq_T *cleanRow(Seq_T *data, int idx)
{
        Seq_T clean = Seq_new(0);
        Seq_T *cleanReturn = &clean;

        // printf("\nThe length is: %d\n", Seq_length(Seq_get(*data, idx)));

        // printf("Here is the initial row:\n");
        // for (int i = 0; i < Seq_length(Seq_get(*data, idx)); i++) {
        //         char *saver = Seq_get(Seq_get(*data, idx), i);
        //         printf("%c", *saver);
        
        // }
        // printf("\n");

        for (int i = 0; i < Seq_length(Seq_get(*data, idx)) - 1; i++) {

                // for (int p = 0; p < Seq_length(clean); p++) {
                //         char *saver = Seq_get(clean, p);
                //         printf("%c", *saver);
                // }
                // printf("\n");

                char *saver = Seq_get(Seq_get(*data, idx), i);
                // printf("The index is %d, and saver is %c\n", i, *saver);
                if (!isdigit(*saver)) {
                        while (!isdigit(*saver) && i < Seq_length(Seq_get(*data, idx))) {
                                i++;
                                saver = Seq_get(Seq_get(*data, idx), i);
                        }
                        // char whiteSpace = ' ';
                        // char *space;
                        // space = &whiteSpace;
                        char whiteSpace = 32;
                        char *space;
                        space = &whiteSpace;
                        // if (isspace(*space)) { 
                        //         printf("(space)\n");
                        // }
                        // Seq_addhi(clean, &space);
                        // Seq_addhi(clean, space);
                        // char *saver2 = Seq_get(clean, Seq_length(clean) - 1);
                        // if (isspace(*saver2)) { 
                        //         printf("clean[hi] is a space./n");
                        // }
                        // Seq_addhi(clean, space);
                        Seq_addhi(clean, saver);
                        
                }
                else {
                        Seq_addhi(clean, saver);
                        // printf("I am here\n");

                }
        }    

        return cleanReturn;
}