#include <stdlib.h>
// typedef struct{
//     long double *vals;
//     size_t dim;
// } vector;


typedef long double* vector;

void vectorInit(vector *v, int len);
void freeVector(vector *v);


typedef vector* basis;


basis gramSchmidt(basis b, int dim, basis mu, basis bStar);
long double minkowskiB(basis bStar, int dim);
long double norm(vector v, int dim);
long double muSum(basis mu, vector v, long double dim, int startBound);
void copyVec(long double* v, long double* w, int dim);
void lll(basis b, int dim);
// helper functions
void subV(long double* v, long double* u, int dim);
void scalarMult(vector v, long double mult, int dim);
vector addV(vector v, vector u, int dim);
long double innerProd(vector v, vector u, int dim);
//vector getMax(basis inputVectors, int dim);