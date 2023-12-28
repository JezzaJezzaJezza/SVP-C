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

// helper functions
vector subV(vector v, vector u, int dim);
vector scalarMult(vector v, double mult, int dim);
vector addV(vector v, vector u, int dim);
double innerProd(vector v, vector u, int dim);
//vector getMax(basis inputVectors, int dim);