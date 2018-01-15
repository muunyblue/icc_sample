#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main() {
#ifdef _OPENMP
  #pragma omp parallel for
#endif
  for (int i = 0; i < 5; ++i) {
#ifdef _OPENMP
    #pragma omp critical
#endif
    {
      printf("Thread No: %d\n");
    }
  }
}
