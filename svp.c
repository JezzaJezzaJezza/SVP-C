#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "vector.h"

int main(int argc, char** argv){
    // Read in command line argument (expects 1)
    // Reading in the input and creating the necessary data to store
    // dimensions are always going to be a whole number when squared because basis vector must form full rank matrix
    // initialise R^n vectors and store pointers for each vector in the basis array.
    int dimension;
    dimension = sqrt(argc - 1);

    basis b = malloc(dimension * sizeof(vector*));

    //printf("%i\n",dimension);


    for (int i = 0; i < dimension; i++){

        vector *v = malloc(sizeof(vector));
        (*v).dim = dimension;
        (*v).vals = malloc((*v).dim * sizeof(double));

        for (int j = 0; j < dimension; j++){

            char *arg = argv[i * dimension + j + 1];

            if (arg[0] == '['){
                //memmove(argv[i * dimension + j + 1][0], argv[i * dimension + j + 1][0] + 1, argc);
                arg++;
            }
            

            printf("%c\n", arg[strlen(arg) - 1]);

            if (arg[strlen(arg) - 1] == ']'){
                //argv[i * dimension + j + 1][strlen(argv[i * dimension + j + 1])] - 1 = "\0";
                //arg++;
                arg[strlen(arg) - 1] = '\0';
            }
            (*v).vals[j] = atof(arg);
        }

        b[i] = *v;

    }
    

    // printf("Vectors:\n");
    // for (int i = 0; i < dimension; i++) {
    //     printf("Vector %d: ", i);
    //     printVector(b[i]);
    // }

    
    for (int i = 0; i < 2; i++){
        printf("Value:  %f\n", b[i].vals[1] );
   }

   for (int i = 0; i < argc - 1; i++){
        free(b[i].vals);
   }
   free(b);
    return 0;


// int parseVector(){
}

