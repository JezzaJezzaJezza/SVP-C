#include "vector.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

void vectorInit(vector *v, int len){
  *v = (double *)malloc(len * sizeof(int));
}

void freeVector(vector v){
  free(v);
  v = NULL;
}

void freeBasis(basis b, int dim){
  for (int i = 0; i < dim; i++){
      freeVector(b[i]);
   }
   free(b);
}





double innerProd(vector v, vector u, int dim){
  double solution = 0;
  for (int i = 0; i < dim; i++){
    solution += (v[i] * u[i]);
  }
  return solution;
}

// vector scalarMult(vector v, double mult, int dim){
//   vector output = (vector)malloc(sizeof(double) * dim);
//   for (int i = 0; i < dim; i++){
//     output[i] = v[i] * mult;
//   }
//   return output;
// }

void scalarMult(vector v, double mult, int dim){
  for (int i = 0; i < dim; i++){
    v[i] = v[i] * mult;
  }
}

void subV(vector v, vector u, int dim) {
  for (int i = 0; i < dim; i++) {
    v[i] -= u[i];
  }
}

void copyVec(vector v, vector w, int dim) {
    for (int i = 0; i < dim; i++){
      w[i] = v[i];
    }
}

basis gramSchmidt(basis b, int dim, basis mu, basis bStar){
  int i,j,k;
  for(i=0; i < dim; i++){

    for(j=0; j < dim; j++){
      mu[i][j] = 0;
      bStar[i][j] = b[i][j];
    }

    for(k=0; k < i; k++){
      mu[i][k] = innerProd(b[i], bStar[k], dim)/innerProd(bStar[k], bStar[k], dim);
      for(j=0; j < dim; j++){
        bStar[i][j] -=mu[i][k] * bStar[k][j];
      }
    }

  }

  return bStar;
}

double minkowskiB(basis bStar, int dim){
  double gamma;
  gamma = 1 + ((double)dim/4);

  gamma = sqrt(gamma);

  double volume;
  volume = 1;
  for (int i = 0; i < dim; i++){
    volume *= sqrt(innerProd (bStar[i], bStar[i], dim));;
  }

  //freeVector(normArray);

  volume = pow(volume, (1/(double)dim));

  double bound;

  bound = gamma * volume;

  return bound;
}

void lll(basis b, int dim, basis bStar, basis mu){

  bStar = gramSchmidt(b, dim, mu, bStar);

  int k = 1;
  double delta = 0.99;
  vector tmpCpy = (vector)malloc(sizeof(double) * dim);

  while(k < dim){ //was k<= dim
    for (int j = k - 1; j >= 0; j--){
      if (fabs(mu[k][j]) > 1/2){

        copyVec(b[j], tmpCpy, dim);
        scalarMult(tmpCpy, round(mu[k][j]), dim);
        subV(b[k], tmpCpy, dim);

        double tmpMu = mu[k][j];
        mu[k][j] = mu[k][j] - round(mu[k][j]);


        for(int i=0; i < j; i++){
          mu[k][i] = mu[k][i] - tmpMu * mu[j][i];
        }
      }
    }

    //copyVec(lllBStar[k - 1], tmpCpy, dim);
    if (innerProd(bStar[k], bStar[k], dim) > ((delta - pow(mu[k][k - 1], 2)) * innerProd(bStar[k - 1], bStar[k - 1], dim))){

      k += 1;

    } else {
      
      copyVec(b[k], tmpCpy, dim);
      
      copyVec(b[k - 1], b[k], dim);
      
      copyVec(tmpCpy, b[k - 1], dim);

      //lllBStar[k - 1]

      bStar = gramSchmidt(b, dim, mu, bStar);
      
      k = fmax(k - 1, 1); //was fmax(k - 1, 2)
    }
  }

  freeVector(tmpCpy);
}

double muSum(basis mu, vector v, double dim, int startBound){
  double collector = 0;
  for (int i = startBound; i < dim; i++){
    collector -= (mu[i][startBound - 1] * v[i]);
  }
  return collector;
}
