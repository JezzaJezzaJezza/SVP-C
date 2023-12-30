#include "vector.h"
#include "math.h"
#include "stdio.h"
#include <string.h>

void vectorInit(vector *v, int len){
  *v = (double *)malloc(len * sizeof(int));
}

void freeVector(vector *v){
  free(*v);
  *v = NULL;
}




//use inline
double innerProd(vector v, vector u, int dim){
  double solution = 0;
  for (int i = 0; i < dim; i++){
    solution += (v[i] * u[i]);
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

void scalarMult(vector v, double mult, int dim){
  for (int i = 0; i < dim; i++){
    v[i] = v[i] * mult;
  }
// def multVector(vector, multiplier):
//     for i in range(vector):
//         vector[i] = vector[i] * multiplier
}

// vector subV(vector v, vector u, int dim){
//   for (int i = 0; i < dim; i++){
//     v[i] -= u[i];
//   }
// // def subVectors(currentVector, possibleVector):
// //     for i in range(len(currentVector)):
// //         currentVector[i] -= possibleVector[i]
// //     return currentVector
// }

void subV(double* v, double* u, int dim) {
  for (int i = 0; i < dim; i++) v[i] -= u[i];
}

double norm(vector v, int dim){
  
  vector squaredVals = (vector)malloc(sizeof(double) * dim);

  for (int i = 0; i < dim; i++){
    squaredVals[i] = pow(v[i], 2);
  }

  double output = 0;

  for (int i = 0; i < dim; i++){
    output += squaredVals[i];
  }

  output = sqrt(output);
  return output;
}

void copyVec(double* v, double* w, int dim) {
    for (int i = 0; i < dim; i++) w[i] = v[i];
}

basis gramSchmidt(basis b, int dim, basis mu, basis bStar){
  
  vector v = (vector)malloc(sizeof(double) * dim);
  double* tmp = malloc(sizeof(double) * dim);
 
  for (int i = 0; i < dim; i++){
          bStar[0][i] = b[0][i];
      }

  for (int i = 1; i < dim; i++){

    copyVec(v, tmp, dim);
    
    copyVec(b[i], v, dim);
    
    
    for (int j = i - 1; j >= 0; j--){
        //printf("j = %i\n",j);
    
      mu[i][j] = innerProd(b[i], bStar[j], dim)/innerProd(bStar[j], bStar[j], dim);
      
      copyVec(bStar[j], tmp, dim);
      
   
      //printf("tmp = %f\n", tmp[0]);
      scalarMult(tmp, mu[i][j], dim);
      //printf("tmp = %f\n", tmp[0]);
    
      
      subV(v, tmp, dim);
      //printf("v = %f\n", v[0]);
    }
    copyVec(v, bStar[i], dim);

    // for (int i = 0; i < dim; i++){
    // for (int j = 0; j < dim; j++){
    //   printf("%f ", bStar[i][j]);
    // }
    // printf("\n");
  //}
  }


  return bStar;
}

double minkowskiB(basis bStar, int dim){
  double gamma;
  gamma = 1 + ((double)dim/4);

  gamma = sqrt(gamma);

  vector normArray = (vector)malloc(sizeof(double) * dim);


  for (int i = 0; i < dim; i++){
    normArray[i] = norm(bStar[i], dim);
  }

  // printf("norm 1: %f\n", normArray[1]);
  // printf("norm 2: %f\n", normArray[2]);
  // printf("norm 3: %f\n", normArray[3]);
  // printf("norm 4: %f\n", normArray[4]);

  double volume;
  volume = 1;
  for (int i = 0; i < dim; i++){
    volume *= normArray[i];
  }

  volume = pow(volume, (1/(double)dim));

  double bound;

  bound = gamma * volume;

  return bound;
}

void lll(basis b, int dim){
  basis lllBStar = (basis)malloc(sizeof(vector) * dim);

  for (int i = 0; i < dim; i++){
    lllBStar[i] = (vector)malloc(sizeof(double) * dim);
  }

  basis lllMu = (basis)malloc(sizeof(vector) * dim);

  for (int i = 0; i < dim; i++){
    lllMu[i] = (vector)malloc(sizeof(double) * dim);
  }

  lllBStar = gramSchmidt(b, dim, lllMu, lllBStar);

  int k = 1;
  double delta = 0.75;
  vector tmpCpy = (vector)malloc(sizeof(double) * dim);

  while(k <= dim){
    for (int j = k - 1; j <= 0; j--){
      if (fabs(lllMu[k][j]) > 1/2){
        scalarMult(b[j], round(lllMu[k][j]), dim);
        subV(b[k], b[j], dim);

        //naive way
        lllBStar = gramSchmidt(b, dim, lllMu, lllBStar);
      }
    }
    if (innerProd(lllBStar[k], lllBStar[k], dim) > ((delta - pow(lllMu[k][k - 1], 2)) * innerProd(lllBStar[k - 1], lllBStar[k - 1], dim))){
      k += 1;
    } else {
      copyVec(b[k], tmpCpy, dim);
      copyVec(b[k - 1], b[k], dim);
      copyVec(tmpCpy, b[k], dim);


      lllBStar = gramSchmidt(b, dim, lllMu, lllBStar);
      k = fmax(k - 1, 2);
    }


  }
  //return b;
}

double muSum(basis mu, vector v, double dim, int startBound){
  double collector = 0;
  for (int i = startBound; i < dim; i++){
    collector -= (mu[i][startBound - 1] * v[i]);
  }
  return collector;
}
