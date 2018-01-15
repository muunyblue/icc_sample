#include <stdio.h>
#include <omp.h>

int atomic() {
  double global = 0.0;
  #pragma omp parallel for
  for (int i = 0; i < 5; ++i) {
    int ithread = omp_get_thread_num();
    printf("atomic[%d]: %p\n", ithread, &global);
    if (i != 0) {
      #pragma omp atomic
      global += 2.0 / (double)(i * i);
    }
  }
  printf("global val: %f\n", global);
}

int reduction() {
  double global = 0.0;
  #pragma omp parallel for reduction(+:global)
  for (int i = 0; i < 5; ++i) {
    int ithread = omp_get_thread_num();
    printf("reduction[%d]: %p\n", ithread, &global);
    if (i != 0) global += 2.0 / (double)(i * i);
  }
  printf("global val: %f\n", global);
}

int main() {
  atomic();
  reduction();
}
