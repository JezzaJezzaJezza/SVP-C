#include "vector.h"

void vectorInit(vector *v, size_t len){
  (*v).vals = (double *)malloc(len * sizeof(int));
  (*v).dim = len;
}

void freeVector(vector *v){
  free((*v).vals);
  (*v).vals = NULL;
  (*v).dim = 0;
}

// void basisInit(basis *b, size_t dim){

// }

// vector addVect(vector *u, vector *v, size_t len){
//   for (int i=0; i<len; i++) {

//   }
// }