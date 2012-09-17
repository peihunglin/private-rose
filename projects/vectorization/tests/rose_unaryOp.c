/*
  Test vectorization for simple arithemetic statements.
*/
#include "rose_simd.h" 

int main()
{
  int i_nom_1_strip_7;
  int i_nom_1;
  float a[16UL];
  __SIMD *a_SIMD;
  int n = 16;
  a_SIMD = ((__SIMD *)a);
  for (i_nom_1 = 0, i_nom_1_strip_7 = i_nom_1; i_nom_1 <= n - 1; (i_nom_1 += 4 , i_nom_1_strip_7 += 1)) {
    a_SIMD[i_nom_1_strip_7] = _SIMD_neg_ps(a_SIMD[i_nom_1_strip_7]);
    a_SIMD[i_nom_1_strip_7] = a_SIMD[i_nom_1_strip_7];
  }
  return 0;
}
