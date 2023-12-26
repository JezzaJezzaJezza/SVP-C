#include <stdlib.h>
// typedef struct{
//     double *vals;
//     size_t dim;
// } vector;


typedef double* vector;

void vectorInit(vector *v, int len);
void freeVector(vector *v);


typedef vector* basis;

vector getMax(basis, int dim);
// void basisInit(vector *v, size_t len);
// void freeBasis(vector *v);