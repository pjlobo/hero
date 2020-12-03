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
#include "report.h"

int test_omp_barrier();
int test_omp_critical();
int test_omp_master_3();
int test_omp_single();

int main(int argc, char *argv[])
{
  unsigned n_errors = 0;

  n_errors += report_pass_fail(
      test_omp_single, "`omp single`");
  n_errors += report_pass_fail(
      test_omp_critical, "`omp critical`");
  n_errors += report_pass_fail(
      test_omp_master_3, "`omp master`");
  n_errors += report_pass_fail(
      test_omp_barrier, "`omp barrier`");

  assert(n_errors == 0);
  return n_errors;
}
