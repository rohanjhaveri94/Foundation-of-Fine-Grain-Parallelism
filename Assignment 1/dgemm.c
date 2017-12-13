/* gemm.c: this file is part of PolyBench/C */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/** Change this to modify the problem size. **/
#define N 2048
#include <time.h>




static
void*
xmalloc(size_t alloc_sz)
{
  void* ret = NULL;
  /** Polybench allocator. **/
  /* int err = posix_memalign (&ret, 4096, alloc_sz); */
  /** Default allocator. **/
  int err = 0;
  ret = (void*) malloc (alloc_sz);

  if (! ret || err)
    {
      fprintf (stderr, "[PolyBench] posix_memalign: cannot allocate memory");
      exit (1);
    }
  
  return ret;
}

void* polybench_alloc_data(unsigned long long int n, int elt_size)
{
  size_t val = n;
  val *= elt_size;
  void* ret = xmalloc (val);

  return ret;
}



static
void init_array(int ni, int nj, int nk,
  double *alpha,
  double *beta,
  double C[ ni + 0][nj + 0],
  double A[ ni + 0][nk + 0],
  double B[ nk + 0][nj + 0])
{
  int i, j;

  *alpha = 1.5;
  *beta = 1.2;
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++)
      C[i][j] = (double) ((i*j+1) % ni) / ni;
  for (i = 0; i < ni; i++)
    for (j = 0; j < nk; j++)
      A[i][j] = (double) (i*(j+1) % nk) / nk;
  for (i = 0; i < nk; i++)
    for (j = 0; j < nj; j++)
      B[i][j] = (double) (i*(j+2) % nj) / nj;
}




static
void print_array(int ni, int nj,
   double C[ ni + 0][nj + 0])
{
  int i, j;

  fprintf(stderr, "==BEGIN DUMP_ARRAYS==\n");
  fprintf(stderr, "begin dump: %s", "C");
  for (i = 0; i < ni; i++)
    for (j = 0; j < nj; j++) {
 if ((i * ni + j) % 20 == 0) fprintf (stderr, "\n");
 fprintf (stderr, "%0.2lf ", C[i][j]);
    }
  fprintf(stderr, "\nend   dump: %s\n", "C");
  fprintf(stderr, "==END   DUMP_ARRAYS==\n");
}




static
void dgemm_kernel(int ni, int nj, int nk,
   double alpha,
   double beta,
   double C[ ni + 0][nj + 0],
   double A[ ni + 0][nk + 0],
   double B[ nk + 0][nj + 0])
{
  int i, j, k;
  for (i = 0; i < ni; i+=2) {
    for (j = 0; j < nj; j+=2)
        C[i][j] *= beta;
        C[i+1][j+1] *= beta;
      for (k = 0; k < nk; k+=2) {
      for (j = 0; j < nj; j+=2)
        
	C[i][j] += alpha * A[i][k] * B[k][j];
        C[i][j+1] += alpha * A[i][k+1] * B[k+1][j+1];


    }
  }
}


int main(int argc, char** argv)
{

  int ni = N;
  int nj = N;
  int nk = N;


  double alpha;
  double beta;
  double (*C)[ni + 0][nj + 0]; C = (double(*)[(unsigned long long int )(ni) + 0][(unsigned long long int )(nj) + 0])polybench_alloc_data (((unsigned long long int )(ni) + 0) * ((unsigned long long int )(nj) + 0), sizeof(double));
  double (*A)[ni + 0][nk + 0]; A = (double(*)[(unsigned long long int )(ni) + 0][(unsigned long long int )(nk) + 0])polybench_alloc_data (((unsigned long long int )(ni) + 0) * ((unsigned long long int )(nk) + 0), sizeof(double));
  double (*B)[nk + 0][nj + 0]; B = (double(*)[(unsigned long long int )(nk) + 0][(unsigned long long int )(nj) + 0])polybench_alloc_data (((unsigned long long int )(nk) + 0) * ((unsigned long long int )(nj) + 0), sizeof(double));


  init_array (ni, nj, nk, &alpha, &beta, *C, *A, *B);
  double time_spent;
  clock_t begin,end;
  begin = clock();
 
  dgemm_kernel (ni, nj, nk,
        alpha, beta,
        *C,
        *A,
        *B);
  end = clock();
  time_spent = ((double) (end - begin));
  time_spent = time_spent/CLOCKS_PER_SEC;
  printf ("time spent = %f\n", time_spent);
  /** Prevent DCE **/
  if (argc > 42 && ! strcmp(argv[0], "")) print_array(ni, nj, *C);


  free((void*)C);
  free((void*)A);
  free((void*)B);

  printf ("All done.\n");
  
  return 0;
}
