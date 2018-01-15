#include <stdio.h>
#include <omp.h>

#define LOOP_NUM 1000

void atomic() {
  double global = 0.0;
  #pragma omp parallel for
  for (int i = 0; i < LOOP_NUM; ++i) {
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
  for (int i = 0; i < LOOP_NUM; ++i) {
    if (i != 0) global += 2.0 / (double)(i * i);
  }
  printf("global val: %f\n", global);
}

void measure_and_print_time(const char* message, void (*func)()) {
  double start_time = omp_get_wtime();
  func();
  double end_time = omp_get_wtime();
  printf("%s: TIME %f(sec)\n", message, end_time - start_time);
}

int main() {
  measure_and_print_time("atomic", atomic);
  measure_and_print_time("reduction", reduction);
}
