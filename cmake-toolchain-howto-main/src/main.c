#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include "blas.h"

__attribute__((noinline))
void vv_add_int32(int32_t *v1, int32_t *v2, int32_t *dst, size_t sz)
{
  for (size_t i = 0; i < sz; i++)
  {
    dst[i] = v1[i] + v2[i];
  }
}

int main()
{

  int32_t a[5] = { 1, 2, 3, 4, 5 };
  int32_t b[5] = { 6, 7, 8, 9, 10 };
  int32_t expected[5] = { 7, 9, 11, 13, 15 };
  int32_t result[5] = { 0 };
  size_t N = sizeof(expected) / sizeof(int32_t);


  vv_add_int32(a, b, result, N);

  for (size_t i = 0; i < N; i++)
  {
    if (result[i] != expected[i])
    {
      printf("Failed vv_add_int32! Element mismatch with expected.\n");
      return 1;
    }
  }
  printf("Passed vv_add_int32!\n");

  Vec_f32 a_vec = { N, (float32_t*) a };
  Vec_f32 b_vec = { N, (float32_t*) b };
  Vec_f32 res_vec = { N, (float32_t*) result };
  Vec_f32 exp_vec = { N, (float32_t*) expected };
  
  blas_status status = vv_add_f32(&a_vec, &b_vec, &res_vec);
  if (!status)
  {
    printf("Failed vv_add_f32! BLAS Status indicates error.\n");
    return 1;
  }

  for (size_t i = 0; i < N; i++)
  {
    if (res_vec.data[i] != exp_vec.data[i])
    {
      printf("Failed vv_add_f32! Output mismatch with expected.\n");
      return 1;
    }
  }
  printf("Passed vv_add_f32!\n");
  return 0;
}
