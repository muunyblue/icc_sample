#include <stdio.h>
#include <omp.h>

void critical_session() {
  double global = 0.0;
  #pragma omp parallel for
  for (int i = 0; i < 5; ++i) {
    #pragma omp critical
    {
      if (i != 0) global += 2.0 / (double)(i * i);
    }
  }
  printf("global val: %f\n", global);
}

void atomic() {
  double global = 0.0;
  #pragma omp parallel for
  for (int i = 0; i < 5; ++i) {
    if (i != 0) {
      #pragma omp atomic
      global += 2.0 / (double)(i * i);
    }
  }
  printf("global val: %f\n", global);
}

void reduction() {
  double global = 0.0;
  #pragma omp parallel for reduction(+:global)
  for (int i = 0; i < 5; ++i) {
    if (i != 0) global += 2.0 / (double)(i * i);
  }
  printf("global val: %f\n", global);
}

int main() {
  critical_session();
  atomic();
  reduction();
}
