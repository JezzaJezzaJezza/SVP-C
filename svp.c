#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "vector.h"

int main(int argc, char** argv){
    // Read in command line argument (expects 1)
    printf("\n");
    printf("%c", argv[1][0]);
    for (int i = 1; i < argc; i++){
        printf("%s ",argv[i]);
    }

    // Reading in the input and creating the necessary data to store
    // dimensions are always going to be a whole number when squared because basis vector must form full rank matrix
    // initialise R^n vectors and store pointers for each vector in the basis array.
    int dimension;
    dimension = sqrt(argc - 1);

    basis b = malloc(dimension * sizeof(vector*));
    printf("%i",dimension);

    for (int i = 0; i < dimension; i++){

        vector *v = malloc(sizeof(vector));
        (*v).dim = dimension;
        (*v).vals = malloc((*v).dim * sizeof(double));

        for (int j = 0; j < dimension; j++){

            if (argv[i * dimension + j + 1][0] == "["){
                memmove(argv[i * dimension + j + 1][0], argv[i * dimension + j + 1][0] + 1, argc);
            }
            if (argv[i * dimension + j + 1][strlen(argv[i * dimension + j + 1])] - 1 == "]"){
                *argv[i * dimension + j + 1][strlen(argv[i * dimension + j + 1])] - 1 = "\0";
            }
            (*v).vals[j] = atof(argv[i * dimension + j + 1]);
    }

    // basis *b = malloc((argc - 1) * sizeof(vector*));

    for (int i = 1; i < argc; i++) {

        b[i - 1] = (vector*)malloc(sizeof(vector));

        vectorInit(b[i-1], argc - 1);
        // if (!parseVector(argv[i], b[i - 1])){

        // }
   }


   for (int i = 0; i < argc - 1; i++){
        freeVector(b[i]);
        free(b[i]);
   }

   free(b);
    return 0;
}

// int parseVector(){

// }