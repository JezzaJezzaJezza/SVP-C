#include <stdlib.h>
typedef struct{
    double *vals;
    size_t dim;
} vector;

void vectorInit(vector *v, size_t len);
void freeVector(vector *v);

typedef vector* basis;

// void basisInit(vector *v, size_t len);
// void freeBasis(vector *v);