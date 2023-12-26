#include "vector.h"
#include "math.h"
#include "stdio.h"

void vectorInit(vector *v, int len){
  *v = (double *)malloc(len * sizeof(int));
}

void freeVector(vector *v){
  free(*v);
  *v = NULL;
}

vector getMax(basis inputVectors, int dim){
    vector largestVector = malloc(dim * sizeof(double));

    for (int i = 0; i < dim; i++){
      for (int j = 0; j < dim; j++){
        if (fabs(largestVector[i]) < fabs(inputVectors[j][i])){
          largestVector[i] = inputVectors[j][i];
        }
      }
    }

    return largestVector;
    //   largestVector = [0] * len(inputBasis)

    // for i in range(len(inputBasis)):
    //     for j in range(len(inputBasis)):
    //         if abs(largestVector[i]) < abs(inputBasis[j][i]):
    //             largestVector[i] = inputBasis[j][i]
    // return largestVector
}

// void basisInit(basis *b, size_t dim){

// }

// vector addVect(vector *u, vector *v, size_t len){
//   for (int i=0; i<len; i++) {

//   }
// }