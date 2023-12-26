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

//MAKE TEMPLATE STYLE FOR EACH DIM UPTO 10, THEN DO A GENERIC ONE LIKE YOU DID HERE.

    for (int i = 0; i < dimension; i++){
        //vector *v = malloc(sizeof(vector));
        vector v = malloc(dimension * sizeof(double));
        //*v = malloc(v * sizeof(double));
        for (int j = 0; j < dimension; j++){
            
            char *arg = argv[i * dimension + j + 1];

            if (arg[0] == '['){
                arg++;
            }


            if (arg[strlen(arg) - 1] == ']'){
                arg[strlen(arg) - 1] = '\0';
            }
            v[j] = atof(arg);
            printf("Value:  %f\n", v[j] );
        }
        b[i] = v;

    }
    

    vector largest = getMax(b, dimension);


    for (int i = 0; i < dimension; i++){
        printf("%f\n",largest[i]);
    }
    

   for (int i = 0; i < argc - 1; i++){
        free(b[i]);
   }
   free(b);
    return 0;
}

