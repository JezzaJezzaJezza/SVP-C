#include <stdio.h>
#include <math.h>
#include <string.h>
#include "vector.h"

double svpSolve(basis b, int dim) {
    if (dim == 1) {  // Check if the input is one dimensional.
        return b[0][0];
    }


    basis mu = (basis)malloc(sizeof(vector) * dim);
    for (int i = 0; i < dim; i++) {
        mu[i] = (vector)malloc(sizeof(double) * dim);
    }

    basis bStar = (basis)malloc(sizeof(vector) * dim);
    for (int i = 0; i < dim; i++) {
        bStar[i] = (vector)malloc(sizeof(double) * dim);
    }

    lll(b, dim, bStar, mu);  // Run the lll algorithm

    bStar = gramSchmidt(b, dim, mu, bStar);  // recompute the b*

    double R;
    double rSquared;

    for (int i = 0; i < dim; i++) {  // make diagonals of mu matrix equal to 1
        mu[i][i] = 1;
    }

    R = minkowskiB(bStar, dim);  // find a suitable bound

    rSquared = pow(R, 2);

    // Delcaration for variables that will be used
    vector rho = (vector)calloc(dim + 1, sizeof(double));
    vector v = (vector)calloc(dim, sizeof(double));
    v[0] = 1;
    vector c = (vector)calloc(dim, sizeof(double));
    vector w = (vector)calloc(dim, sizeof(double));

    int k = 0;
    int largest = 0;
    double tmpInner = 0;

    while (1) {  // The main loop for Schnorr-Euchner enumeration (SE)
        tmpInner = innerP(bStar[k], bStar[k], dim);
        rho[k] = rho[k+1] + pow((v[k] - c[k]), 2) * tmpInner;

        if (rho[k] < rSquared) {
            if (k == 0) {
                rSquared = rho[k];

            } else {
                k -= 1;
                c[k] = muSum(mu, v, dim, k+1);
                v[k] = round(c[k]);
                w[k] = 1;
            }

        } else {
            k += 1;

            if (k == dim) {
                // shortest vector found --> return and free variables
                freeVector(rho);
                freeVector(v);
                freeVector(c);
                freeVector(w);
                freeBasis(bStar, dim);
                freeBasis(mu, dim);
                return sqrt(rSquared);
            }
            if (k >= largest) {
                largest = k;
                v[k] += 1;

            } else {
                if (v[k] > c[k]) {
                    v[k] -= w[k];

                } else {
                    v[k] += w[k];
                }
                w[k] += 1;
                }
            }
        }
}

int main(int argc, char** argv) {
    // Read in command line argument (expects 1).
    // Reading in the input.
    // Dimensions will always be a whole number
    // as the basis should be a square matrix.
    int dimension;
    dimension = sqrt(argc - 1);
    basis b = (basis)malloc(dimension * sizeof(vector*));

    for (int i = 0; i < dimension; i++) {
        // Ensure that each vector starts with [
        if (argv[i*dimension + 1][0] != '[') {
            printf("Invalid input.\n");
            return 1;
        }

        vector v = (vector)malloc(dimension * sizeof(double));

        for (int j = 0; j < dimension; j++) {
            char *arg = argv[i * dimension + j + 1];

            if (arg[0] == '[') {  // skip over [
                arg++;
            }

            if (arg[strlen(arg) - 1] == ']') {  // change ] to \0
                arg[strlen(arg) - 1] = '\0';
            }
            v[j] = atof(arg);  // convert string to float and store
        }
        b[i] = v;  // store the vector in the basis
    }

    double out;
    out = svpSolve(b, dimension);  // call SE

    char *file = "result.txt";

    FILE *fp = fopen(file, "w");  // write to file
    fprintf(fp, "%f", out);
    fclose(fp);

    freeBasis(b, dimension);
    return 0;
}
