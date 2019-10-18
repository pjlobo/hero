/*
 * Copyright 2019 ETH Zurich, University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h> // abort()
#include "tests.h"

void __assert_func(const char* file, int line, const char* funcname, const char* assertion) {
  printf("Assertion `%s' in %s (%s:%d) failed!\n", assertion, funcname, file, line);
  abort();
}

int main(int argc, char *argv[])
{
  unsigned n_errors = 0;

  n_errors += test_m_instrs();
  n_errors += test_dma();
  n_errors += test_hero_64();
  n_errors += test_atomic();

  printf("Testing `omp for` with static schedule ..\n");
  n_errors += !test_omp_for_schedule_static();
  printf("Testing `omp for` with dynamic schedule ..\n");
  n_errors += !test_omp_for_schedule_dynamic();
  printf("Testing `omp parallel for reduction` ..\n");
  n_errors += !test_omp_parallel_for_reduction();
  printf("Testing `omp atomic` ..\n");
  n_errors += !test_omp_atomic();
  n_errors += !test_omp_barrier();
  n_errors += !test_omp_parallel_for_private();
  n_errors += !test_omp_parallel_for_firstprivate();
  n_errors += !test_omp_parallel_for_lastprivate();
  n_errors += !test_omp_single();
  n_errors += !test_omp_critical();
  n_errors += !test_omp_master_3();

  printf("All OpenMP tests completed.\n");


  assert(n_errors == 0);
  return n_errors;
}
