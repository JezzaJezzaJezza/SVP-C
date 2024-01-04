#include "vector.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

void freeVector(vector v){//free vectors
  free(v);
  v = NULL;
}

void freeBasis(basis b, int dim){//frees basis
  for (int i = 0; i < dim; i++){
      freeVector(b[i]);
   }
   free(b);
}

double innerProd(vector v, vector u, int dim){//see vector.h
  double solution = 0;
  for (int i = 0; i < dim; i++){
    solution += (v[i] * u[i]);
  }
  return solution;
}

void scalarMult(vector v, double mult, int dim){//see vector.h
  for (int i = 0; i < dim; i++){
    v[i] = v[i] * mult;
  }
}

void subV(vector v, vector u, int dim) {//see vector.h
  for (int i = 0; i < dim; i++) {
    v[i] -= u[i];
  }
}

void copyVec(vector v, vector u, int dim) {//see vector.h
    for (int i = 0; i < dim; i++){
      u[i] = v[i];
    }
}

basis gramSchmidt(basis b, int dim, basis mu, basis bStar){//main gram-schmidt function, written as shown in the paper "Efficient Implementations of Sieving and Enumeration Algorithms for Lattice-Based Cryptography", https://www.mdpi.com/2227-7390/9/14/1618, Code 1., Viewed on Dec 28th 2023, Authors: Mr. Hami Satılmış, Dr. Sedat Akleylek and Prof. Dr. Cheng-Chi Lee
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

double minkowskiB(basis bStar, int dim){//Used formula from Yasuda, Masaya. (2021). A Survey of Solving SVP Algorithms and Recent Strategies for Solving the SVP Challenge. 10.1007/978-981-15-5191-8_15. https://www.researchgate.net/publication/346358063_A_Survey_of_Solving_SVP_Algorithms_and_Recent_Strategies_for_Solving_the_SVP_Challenge
  double gamma;
  gamma = 1 + ((double)dim/4);

  gamma = sqrt(gamma);

  double volume;
  volume = 1;
  for (int i = 0; i < dim; i++){
    volume *= sqrt(innerProd (bStar[i], bStar[i], dim));;
  }

  volume = pow(volume, (1/(double)dim));

  double bound;

  bound = gamma * volume;

  return bound;
}

void lll(basis b, int dim, basis bStar, basis mu){//lll algorithm adapted from Sanjay Bhattacherjee, Julio Hernandez-Castro, Jack Moyler. A Greedy Global Framework for LLL. Algorithm 2. - https://eprint.iacr.org/2023/261.pdf

  bStar = gramSchmidt(b, dim, mu, bStar);

  int k = 1;
  double delta = 0.99;//delta is well defined for (0.25,1], and after experimenting with different test cases, setting delta to 0.99 yielded the best results for higher dimensions, however, since we will be dealing with smaller dimensions, 0.85 seemed to be a better balance
  vector tmpCpy = (vector)malloc(sizeof(double) * dim);

  while(k < dim){
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
    if (innerProd(bStar[k], bStar[k], dim) > ((delta - pow(mu[k][k - 1], 2)) * innerProd(bStar[k - 1], bStar[k - 1], dim))){

      k += 1;

    } else {
      
      copyVec(b[k], tmpCpy, dim);
      
      copyVec(b[k - 1], b[k], dim);
      
      copyVec(tmpCpy, b[k - 1], dim);

      bStar = gramSchmidt(b, dim, mu, bStar);
      
      k = fmax(k - 1, 1);
    }
  }
  freeVector(tmpCpy);
}

double muSum(basis mu, vector v, double dim, int startBound){//returns the negation of a sum shown below
  double collector = 0;
  for (int i = startBound; i < dim; i++){
    collector -= (mu[i][startBound - 1] * v[i]);
  }
  return collector;
}
