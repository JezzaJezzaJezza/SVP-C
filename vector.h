#include <stdlib.h>

typedef double* vector;

void freeVector(vector v);

typedef vector* basis;

void freeBasis(basis b, int dim);

basis gramSchmidt(basis b, int dim, basis mu, basis bStar);//does gram-schmidt on some input matrix (basis)
double minkowskiB(basis bStar, int dim);//Calculates the bound that will be used in enumeration
double muSum(basis mu, vector v, double dim, int startBound);//specific function used only in SE
void copyVec(vector v, vector u, int dim);//copies some vector v to some other vector u
void lll(basis b, int dim, basis bStar, basis mu);//runs the lll algorithm to get a reduced basis
void subV(vector v, vector u, int dim);//subtract vectors --> v - u
void scalarMult(vector v, double mult, int dim);//multiply some vector v by some double mult
double innerProd(vector v, vector u, int dim);//calculate the inner product of v and u -NOTE- inner product is equal to the norm squared, when using vectors where v = u