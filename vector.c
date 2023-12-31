#include "vector.h"
#include "math.h"
#include "stdio.h"
#include <string.h>

void vectorInit(vector *v, int len){
  *v = (long double *)malloc(len * sizeof(int));
}

void freeVector(vector *v){
  free(*v);
  *v = NULL;
}




//use inline
long double innerProd(vector v, vector u, int dim){
  long double solution = 0;
  for (int i = 0; i < dim; i++){
    solution += (v[i] * u[i]);
  }
  return solution;
}

vector addV(vector v, vector u, int dim){
  for (int i = 0; i < dim; i++){
    v[i] += u[i];
  }
  return v;
}

void scalarMult(vector v, long double mult, int dim){
  for (int i = 0; i < dim; i++){
    v[i] = v[i] * mult;
  }
}

void subV(long double* v, long double* u, int dim) {
  for (int i = 0; i < dim; i++) v[i] -= u[i];
}

long double norm(vector v, int dim){
  
  vector squaredVals = (vector)malloc(sizeof(long double) * dim);

  for (int i = 0; i < dim; i++){
    squaredVals[i] = pow(v[i], 2);
  }

  long double output = 0;

  for (int i = 0; i < dim; i++){
    output += squaredVals[i];
  }

  output = sqrt(output);
  return output;
}

void copyVec(long double* v, long double* w, int dim) {
    for (int i = 0; i < dim; i++) w[i] = v[i];
}

basis gramSchmidt(basis b, int dim, basis mu, basis bStar){ //DOUBLE CHECK THAT ALL ZEROS ARENT POSITIVE OR NEGATIVE
  vector v = (vector)malloc(sizeof(long double) * dim);
  long double* tmp = malloc(sizeof(long double) * dim);

  copyVec(b[0], bStar[0], dim);

  for (int i = 1; i < dim; i++){

    //copyVec(v, tmp, dim);
    
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

    for (int i = 0; i < dim; i++){
    for (int j = 0; j < dim; j++){
      printf("%Lf ", bStar[i][j]);
    }
    printf("\n");
  }
  }


  return bStar;
}

long double minkowskiB(basis bStar, int dim){
  long double gamma;
  gamma = 1 + ((long double)dim/4);

  gamma = sqrt(gamma);

  vector normArray = (vector)malloc(sizeof(long double) * dim);


  for (int i = 0; i < dim; i++){
    normArray[i] = norm(bStar[i], dim);
  }

  // printf("norm 1: %f\n", normArray[1]);
  // printf("norm 2: %f\n", normArray[2]);
  // printf("norm 3: %f\n", normArray[3]);
  // printf("norm 4: %f\n", normArray[4]);

  long double volume;
  volume = 1;
  for (int i = 0; i < dim; i++){
    volume *= normArray[i];
  }

  volume = pow(volume, (1/(long double)dim));

  long double bound;

  bound = gamma * volume;

  return bound;
}

void lll(basis b, int dim){
  basis lllBStar = (basis)malloc(sizeof(vector) * dim);

  for (int i = 0; i < dim; i++){
    lllBStar[i] = (vector)malloc(sizeof(long double) * dim);
  }

  basis lllMu = (basis)malloc(sizeof(vector) * dim);

  for (int i = 0; i < dim; i++){
    lllMu[i] = (vector)malloc(sizeof(long double) * dim);
  }


  lllBStar = gramSchmidt(b, dim, lllMu, lllBStar);

  int k = 1;
  long double delta = 0.75;
  vector tmpCpy = (vector)malloc(sizeof(long double) * dim);

  while(k <= dim){
    for (int j = k - 1; j <= 0; j--){
      if (fabs(lllMu[k][j]) > 1/2){
        printf("test\n");
        copyVec(b[j], tmpCpy, dim);
        scalarMult(tmpCpy, round(lllMu[k][j]), dim);
        subV(b[k], tmpCpy, dim);

        //naive way
        lllBStar = gramSchmidt(b, dim, lllMu, lllBStar);
      }
    }
    copyVec(lllBStar[k - 1], tmpCpy, dim);
    if (innerProd(lllBStar[k], lllBStar[k], dim) > ((delta - pow(lllMu[k][k - 1], 2)) * innerProd(tmpCpy, tmpCpy, dim))){
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

long double muSum(basis mu, vector v, long double dim, int startBound){
  long double collector = 0;
  for (int i = startBound; i < dim; i++){
    collector -= (mu[i][startBound - 1] * v[i]);
  }
  return collector;
}
