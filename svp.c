#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "vector.h"

double svpSolve(basis b, int dim){
    if (dim == 1){
        return b[0][0];
    }

    basis mu = (basis)malloc(sizeof(vector) * dim);
    for (int i = 0; i < dim; i++){
        mu[i] = (vector)malloc(sizeof(double) * dim);
    }

    basis bStar = (basis)malloc(sizeof(vector) * dim);
    for (int i = 0; i < dim; i++){
        bStar[i] = (vector)malloc(sizeof(double) * dim);
    }
    

    lll(b, dim);

    bStar = gramSchmidt(b, dim, mu, bStar);

    double R;
    double rSquared;

    for (int i = 0; i < dim; i++){
        mu[i][i] = 1;
    }


    R = minkowskiB(bStar, dim);


    rSquared = pow(R, 2);
    


    vector rho = (vector)calloc(dim + 1, sizeof(double));
    vector v = (vector)calloc(dim, sizeof(double));
    v[0] = 1;
    vector c = (vector)calloc(dim, sizeof(double));
    vector w = (vector)calloc(dim, sizeof(double));

    int k = 0;
    int largest = 0;


    while (1){

        rho[k] = rho[k + 1] + pow((v[k] - c[k]), 2) * (innerProd(bStar[k], bStar[k], dim));

        if (rho[k] < rSquared){ 

            if (k == 0){ 

                rSquared = rho[k];

            } else {

                k -= 1;
                c[k] = muSum(mu, v, dim, k+1);
                v[k] = round(c[k]);
                w[k] = 1;

            }

        } else {

            k += 1;

            if (k == (dim)){
                
                freeVector(rho);
                freeVector(v);
                freeVector(c);
                freeVector(w);
                freeBasis(bStar, dim);
                freeBasis(mu, dim);
                return sqrt(rSquared);

            }
            if (k >= largest){

                largest = k;
                v[k] += 1;

            } else {

                if (v[k] > c[k]){

                    v[k] -= w[k];

                } else {

                    v[k] += w[k];
                    w[k] += 1;

                }
            }
        }
    }

    freeVector(rho);
    freeVector(v);
    freeVector(c);
    freeVector(w);
    freeBasis(bStar, dim);
    freeBasis(mu, dim);
    
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

        vector v = malloc(dimension * sizeof(double));

        for (int j = 0; j < dimension; j++){
            
            char *arg = argv[i * dimension + j + 1];

            if (arg[0] == '['){
                arg++;
            }


            if (arg[strlen(arg) - 1] == ']'){
                arg[strlen(arg) - 1] = '\0';
            }
            v[j] = atof(arg);
        }
        b[i] = v;
    }
    
    double out;
    out = svpSolve(b, dimension);
   //printf("%f\n", out);
    char *file = "output.txt";

   FILE *fp = fopen(file, "w");
   fprintf(fp, "%f", out);
   fclose(fp);
    
    
   freeBasis(b, dimension);
    return 0;
}