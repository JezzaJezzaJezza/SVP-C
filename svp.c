#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "vector.h"

long double svpSolve(basis b, int dim){
    basis mu = (basis)malloc(sizeof(vector) * dim);
    for (int i = 0; i < dim; i++){
        mu[i] = (vector)malloc(sizeof(long double) * dim);
    }

    basis bStar = (basis)malloc(sizeof(vector) * dim);
    for (int i = 0; i < dim; i++){
        bStar[i] = (vector)malloc(sizeof(long double) * dim);
    }
    

    lll(b, dim);

    bStar = gramSchmidt(b, dim, mu, bStar);

    long double R;
    long double rSquared;

    for (int i = 0; i < dim; i++){
        mu[i][i] = 1;
    }
    //printf("%f\n", mu[0][0]);

    R = minkowskiB(bStar, dim);
    //printf("%f\n", R);

    rSquared = pow(R, 2);
    
    //printf("%f\n", R);

    vector rho = (vector)calloc(dim + 1, sizeof(long double));
    vector v = (vector)calloc(dim, sizeof(long double));
    v[0] = 1;
    vector c = (vector)calloc(dim, sizeof(long double));
    vector w = (vector)calloc(dim, sizeof(long double));

    int k = 0;
    int largest = 0;

    //printf("-------------------------------\n");
    while (1){
        //printf("bStar[k] %f\n", bStar[k][0]);
        rho[k] = rho[k + 1] + pow((v[k] - c[k]), 2) * (innerProd(bStar[k], bStar[k], dim));
        //printf("rho[k] = %f\n", rho[k]);
        if (rho[k] < rSquared){ // was <= before but caused inf loop
            //printf("rho[k] < rSquare = %f\n", rSquared);
            if (k == 0){ // could be 1 or 0 ~ 1 indexing is so annoying
            //printf("k = 0 (rSquared = rho[k])\n");
                rSquared = rho[k];
            } else {
                //printf("k (%i) was not == 0\n", k);
                k -= 1;

                //printf("before c[k]: %f\n", c[k]);
                c[k] = muSum(mu, v, dim, k+1);
                //printf("after c[k]: %f\n", c[k]);

                //printf("before v[k]: %f\n", v[k]);
                // printf("c[k] = %f\n", c[k]);
                // printf("v[k] = %f\n", v[k]);
                v[k] = round(c[k]);
                // printf("v[k] = %f\n", v[k]);
                // printf("c[k] = %f\n", c[k]);
                //printf("before v[k] (rounds c[k] to nearest int): %f\n", v[k]);

                //printf("before w[k]: %f\n", w[k]);
                w[k] = 1;
                //printf("after w[k]: %f\n", w[k]);
            }

        } else {
            //printf("rho[k] >= rSquare = %f\n", rSquared);
            k += 1;
            //printf("k = %i\n", k);
            if (k == (dim)){
                //printf("returned\n");
                return sqrt(rSquared);
            }
            if (k >= largest){
                //printf("k >= largest = %i\n", largest);
                largest = k;

                //printf("largest = k\n");
                v[k] += 1;
                //printf("v[k] before: %f\n", v[k]);
            } else {
                //printf("v[k] after: %f\n", v[k]);
                if (v[k] > c[k]){
                //printf("k < largest: %i\n", largest);
                    //printf("c[k] = %f\n", c[k]);
                    //printf("v[k] = %f > ", v[k]);

                    //printf("v[k] -= w[k](%f)\n", w[k]);
                    v[k] -= w[k];
                } else {
                    //printf("v[k] = %f <= ", v[k]);
                    //printf("c[k] = %f\n", c[k]);

                    //printf("v[k] += w[k](%f\n)", w[k]);
                    v[k] += w[k];
                    //printf("w[k] += 1\n");
                    w[k] += 1;
                    //printf("w[k] = %f\n", w[k]);
                }
            }
        }
        //printf("-------------------------------------\n");
        //printf("preloop: rho[k] = %f\n ", rho[k]);
        //printf("k = %i\n", k);
    }
    return rSquared;
}

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
        vector v = malloc(dimension * sizeof(long double));
        //*v = malloc(v * sizeof(long double));
        for (int j = 0; j < dimension; j++){
            
            char *arg = argv[i * dimension + j + 1];

            if (arg[0] == '['){
                arg++;
            }


            if (arg[strlen(arg) - 1] == ']'){
                arg[strlen(arg) - 1] = '\0';
            }
            v[j] = atof(arg);
            //printf("Value:  %f\n", v[j] );
        }
        b[i] = v;

    }
    
    long double out;
    out = svpSolve(b, dimension);
    //printf("%Lf\n", out);
    
    

   for (int i = 0; i < dimension; i++){
        free(b[i]);
   }
   free(b);
    return 0;
}