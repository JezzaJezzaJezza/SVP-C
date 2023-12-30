#include <stdlib.h>
// typedef struct{
//     double *vals;
//     size_t dim;
// } vector;


typedef double* vector;

void vectorInit(vector *v, int len);
void freeVector(vector *v);


typedef vector* basis;


basis gramSchmidt(basis b, int dim, basis mu, basis bStar);
double minkowskiB(basis bStar, int dim);
double norm(vector v, int dim);
double muSum(basis mu, vector v, double dim, int startBound);
void copyVec(double* v, double* w, int dim);
void lll(basis b, int dim);
// helper functions
void subV(double* v, double* u, int dim);
void scalarMult(vector v, double mult, int dim);
vector addV(vector v, vector u, int dim);
double innerProd(vector v, vector u, int dim);
//vector getMax(basis inputVectors, int dim);