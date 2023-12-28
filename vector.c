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

// vector getMax(basis inputVectors, int dim){
//     vector largestVector = malloc(dim * sizeof(double));

//     for (int i = 0; i < dim; i++){
//       for (int j = 0; j < dim; j++){
//         if (fabs(largestVector[i]) < fabs(inputVectors[j][i])){
//           largestVector[i] = inputVectors[j][i];
//         }
//       }
//     }

//     return largestVector;
// }


//use inline
double innerProd(vector v, vector u, int dim){
  double solution = 0;
  for (int i = 0; i < dim; i++){
    solution += v[i] * u[i];
  }
  return solution;
// def innerProd(v,u):
//     solution = 0
//     for i in range(len(v)):
//         solution += v[i] * u[i]
//     return solution
}

vector addV(vector v, vector u, int dim){
  for (int i = 0; i < dim; i++){
    v[i] += u[i];
  }
  return v;
// def addVectors(currentVector, possibleVector):
//     for i in range(len(currentVector)):
//         currentVector[i] += possibleVector[i]
//     return currentVector
}

vector scalarMult(vector v, double mult, int dim){
  for (int i = 0; i < dim; i++){
    v[i] = v[i] * mult;
  }
  return v;
// def multVector(vector, multiplier):
//     for i in range(vector):
//         vector[i] = vector[i] * multiplier
}

vector subV(vector v, vector u, int dim){
  for (int i = 0; i < dim; i++){
    v[i] -= u[i];
  }
  return v;
// def subVectors(currentVector, possibleVector):
//     for i in range(len(currentVector)):
//         currentVector[i] -= possibleVector[i]
//     return currentVector
}

double norm(vector v, int dim){
  
  vector squaredVals = (vector)malloc(sizeof(double) * dim);

  for (int i = 0; i < dim; i++){
    squaredVals[i] = v[i] * v[i];
  }

  double output;

  for (int i = 0; i < dim; i++){
    output += squaredVals[i];
  }

  output = sqrt(output);
  return output;
}

basis gramSchmidt(basis b, int dim, basis mu, basis bStar){

  int i,j,k;
  for (i = 0; i < dim; i++){
    for (j = 0; j < dim; j++){
      mu[i][j] = 0;
      bStar[i][j] = (double)b[i][j];
    }
    for (k = 0; k < i; k++){
      mu[i][k] = innerProd(b[i], bStar[k], dim)/norm(bStar[k], dim);
      for(j = 0; j < dim; j++){
        bStar[i][j] -= mu[i][k] * bStar[k][j];
      }
    }
  }
  return bStar;
}

double minkowskiB(basis bStar, int dim){
  double gamma;
  gamma = 1 + (dim/4);

  gamma = sqrt(gamma);

  vector normArray = (vector)malloc(sizeof(double) * dim);

  for (int i = 0; i < dim; i++){
    normArray[i] = norm(bStar[i], dim);
  }

  double volume;
  volume = 1;
  for (int i = 0; i < dim; i++){
    volume *= normArray[i];
  }

  volume = pow(volume, (1/dim));

  double bound;

  bound = gamma * volume;

  return bound;
}
