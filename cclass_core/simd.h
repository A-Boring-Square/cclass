#ifndef C_CLASS_CORE_SIMD_FULL_HCLASS
#define C_CLASS_CORE_SIMD_FULL_HCLASS

#include "cclass.h"
#include <stddef.h>
#include <stdint.h>


// ------------------ SIMD DETECTION ------------------
#if C_CLASS_USE_SIMD
#if defined(__AVX512F__)
    #define USE_SIMD 1
    #define SIMD_EXT AVX512
    #include <immintrin.h>
#elif defined(__AVX2__)
    #define USE_SIMD 1
    #define SIMD_EXT AVX2
    #include <immintrin.h>
#elif defined(__AVX__)
    #define USE_SIMD 1
    #define SIMD_EXT AVX
    #include <immintrin.h>
#elif defined(__SSE4_1__)
    #define USE_SIMD 1
    #define SIMD_EXT SSE41
    #include <smmintrin.h>
#elif defined(__SSE2__)
    #define USE_SIMD 1
    #define SIMD_EXT SSE2
    #include <emmintrin.h>
#else
    #define USE_SIMD 0
#endif
#else
    #define USE_SIMD 0
#endif

// ------------------ PUBLIC API ------------------
#define SIMD_ARRAY(name,type,len) type name[len]

// ------------------ GENERIC SCALAR FALLBACK ------------------
#define SIMD_SCALAR_OP(op,dest,a,b,len) do{for(size_t i=0;i<(len);i++) (dest)[i]=(a)[i] op (b)[i];}while(0)
#define SIMD_SCALAR_MUL(dest,a,b,len) do{for(size_t i=0;i<(len);i++) (dest)[i]=(a)[i]*(b)[i];}while(0)
#define SIMD_SCALAR_DIV(dest,a,b,len) do{for(size_t i=0;i<(len);i++) (dest)[i]=(a)[i]/(b)[i];}while(0)
#define SIMD_SCALAR_MIN(dest,a,b,len) do{for(size_t i=0;i<(len);i++) (dest)[i]=((a)[i]<(b)[i]?(a)[i]:(b)[i]);}while(0)
#define SIMD_SCALAR_MAX(dest,a,b,len) do{for(size_t i=0;i<(len);i++) (dest)[i]=((a)[i]>(b)[i]?(a)[i]:(b)[i]);}while(0)
#define SIMD_SCALAR_AND(dest,a,b,len) do{for(size_t i=0;i<(len);i++) (dest)[i]=(a)[i] & (b)[i];}while(0)
#define SIMD_SCALAR_OR(dest,a,b,len) do{for(size_t i=0;i<(len);i++) (dest)[i]=(a)[i] | (b)[i];}while(0)
#define SIMD_SCALAR_XOR(dest,a,b,len) do{for(size_t i=0;i<(len);i++) (dest)[i]=(a)[i] ^ (b)[i];}while(0)

// ------------------ FLOAT / DOUBLE SIMD ------------------
#if USE_SIMD
// float
#if SIMD_EXT >= AVX
#define SIMD_ADD_F32(dest,a,b,len) do{size_t i=0; for(;i+8<=(len);i+=8){__m256 va=_mm256_loadu_ps(a+i); __m256 vb=_mm256_loadu_ps(b+i); _mm256_storeu_ps(dest+i,_mm256_add_ps(va,vb));} for(;i<(len);i++) dest[i]=a[i]+b[i];}while(0)
#define SIMD_SUB_F32(dest,a,b,len) do{size_t i=0; for(;i+8<=(len);i+=8){__m256 va=_mm256_loadu_ps(a+i); __m256 vb=_mm256_loadu_ps(b+i); _mm256_storeu_ps(dest+i,_mm256_sub_ps(va,vb));} for(;i<(len);i++) dest[i]=a[i]-b[i];}while(0)
#define SIMD_MUL_F32(dest,a,b,len) do{size_t i=0; for(;i+8<=(len);i+=8){__m256 va=_mm256_loadu_ps(a+i); __m256 vb=_mm256_loadu_ps(b+i); _mm256_storeu_ps(dest+i,_mm256_mul_ps(va,vb));} for(;i<(len);i++) dest[i]=a[i]*b[i];}while(0)
#define SIMD_DIV_F32(dest,a,b,len) do{size_t i=0; for(;i+8<=(len);i+=8){__m256 va=_mm256_loadu_ps(a+i); __m256 vb=_mm256_loadu_ps(b+i); _mm256_storeu_ps(dest+i,_mm256_div_ps(va,vb));} for(;i<(len);i++) dest[i]=a[i]/b[i];}while(0)
#elif SIMD_EXT >= SSE2
#define SIMD_ADD_F32(dest,a,b,len) do{size_t i=0; for(;i+4<=(len);i+=4){__m128 va=_mm_loadu_ps(a+i); __m128 vb=_mm_loadu_ps(b+i); _mm_storeu_ps(dest+i,_mm_add_ps(va,vb));} for(;i<(len);i++) dest[i]=a[i]+b[i];}while(0)
#define SIMD_SUB_F32(dest,a,b,len) do{size_t i=0; for(;i+4<=(len);i+=4){__m128 va=_mm_loadu_ps(a+i); __m128 vb=_mm_loadu_ps(b+i); _mm_storeu_ps(dest+i,_mm_sub_ps(va,vb));} for(;i<(len);i++) dest[i]=a[i]-b[i];}while(0)
#define SIMD_MUL_F32(dest,a,b,len) do{size_t i=0; for(;i+4<=(len);i+=4){__m128 va=_mm_loadu_ps(a+i); __m128 vb=_mm_loadu_ps(b+i); _mm_storeu_ps(dest+i,_mm_mul_ps(va,vb));} for(;i<(len);i++) dest[i]=a[i]*b[i];}while(0)
#define SIMD_DIV_F32(dest,a,b,len) do{size_t i=0; for(;i+4<=(len);i+=4){__m128 va=_mm_loadu_ps(a+i); __m128 vb=_mm_loadu_ps(b+i); _mm_storeu_ps(dest+i,_mm_div_ps(va,vb));} for(;i<(len);i++) dest[i]=a[i]/b[i];}while(0)
#endif

// double
#if SIMD_EXT >= AVX
#define SIMD_ADD_F64(dest,a,b,len) do{size_t i=0; for(;i+4<=(len);i+=4){__m256d va=_mm256_loadu_pd(a+i); __m256d vb=_mm256_loadu_pd(b+i); _mm256_storeu_pd(dest+i,_mm256_add_pd(va,vb));} for(;i<(len);i++) dest[i]=a[i]+b[i];}while(0)
#define SIMD_SUB_F64(dest,a,b,len) do{size_t i=0; for(;i+4<=(len);i+=4){__m256d va=_mm256_loadu_pd(a+i); __m256d vb=_mm256_loadu_pd(b+i); _mm256_storeu_pd(dest+i,_mm256_sub_pd(va,vb));} for(;i<(len);i++) dest[i]=a[i]-b[i];}while(0)
#define SIMD_MUL_F64(dest,a,b,len) do{size_t i=0; for(;i+4<=(len);i+=4){__m256d va=_mm256_loadu_pd(a+i); __m256d vb=_mm256_loadu_pd(b+i); _mm256_storeu_pd(dest+i,_mm256_mul_pd(va,vb));} for(;i<(len);i++) dest[i]=a[i]*b[i];}while(0)
#define SIMD_DIV_F64(dest,a,b,len) do{size_t i=0; for(;i+4<=(len);i+=4){__m256d va=_mm256_loadu_pd(a+i); __m256d vb=_mm256_loadu_pd(b+i); _mm256_storeu_pd(dest+i,_mm256_div_pd(va,vb));} for(;i<(len);i++) dest[i]=a[i]/b[i];}while(0)
#elif SIMD_EXT >= SSE2
#define SIMD_ADD_F64(dest,a,b,len) do{size_t i=0; for(;i+2<=(len);i+=2){__m128d va=_mm_loadu_pd(a+i); __m128d vb=_mm_loadu_pd(b+i); _mm_storeu_pd(dest+i,_mm_add_pd(va,vb));} for(;i<(len);i++) dest[i]=a[i]+b[i];}while(0)
#define SIMD_SUB_F64(dest,a,b,len) do{size_t i=0; for(;i+2<=(len);i+=2){__m128d va=_mm_loadu_pd(a+i); __m128d vb=_mm_loadu_pd(b+i); _mm_storeu_pd(dest+i,_mm_sub_pd(va,vb));} for(;i<(len);i++) dest[i]=a[i]-b[i];}while(0)
#define SIMD_MUL_F64(dest,a,b,len) do{size_t i=0; for(;i+2<=(len);i+=2){__m128d va=_mm_loadu_pd(a+i); __m128d vb=_mm_loadu_pd(b+i); _mm_storeu_pd(dest+i,_mm_mul_pd(va,vb));} for(;i<(len);i++) dest[i]=a[i]*b[i];}while(0)
#define SIMD_DIV_F64(dest,a,b,len) do{size_t i=0; for(;i+2<=(len);i+=2){__m128d va=_mm_loadu_pd(a+i); __m128d vb=_mm_loadu_pd(b+i); _mm_storeu_pd(dest+i,_mm_div_pd(va,vb));} for(;i<(len);i++) dest[i]=a[i]/b[i];}while(0)
#endif
#else
#define SIMD_ADD_F32 SIMD_SCALAR_OP
#define SIMD_SUB_F32 SIMD_SCALAR_OP
#define SIMD_MUL_F32 SIMD_SCALAR_MUL
#define SIMD_DIV_F32 SIMD_SCALAR_DIV
#define SIMD_ADD_F64 SIMD_SCALAR_OP
#define SIMD_SUB_F64 SIMD_SCALAR_OP
#define SIMD_MUL_F64 SIMD_SCALAR_MUL
#define SIMD_DIV_F64 SIMD_SCALAR_DIV
#endif

// ------------------ INTEGER OPS ------------------
#define SIMD_ADD_I8   SIMD_SCALAR_OP
#define SIMD_SUB_I8   SIMD_SCALAR_OP
#define SIMD_ADD_I16  SIMD_SCALAR_OP
#define SIMD_SUB_I16  SIMD_SCALAR_OP
#define SIMD_ADD_I32  SIMD_SCALAR_OP
#define SIMD_SUB_I32  SIMD_SCALAR_OP
#define SIMD_ADD_I64  SIMD_SCALAR_OP
#define SIMD_SUB_I64  SIMD_SCALAR_OP

#define SIMD_MUL_I8   SIMD_SCALAR_MUL
#define SIMD_MUL_I16  SIMD_SCALAR_MUL
#define SIMD_MUL_I32  SIMD_SCALAR_MUL
#define SIMD_MUL_I64  SIMD_SCALAR_MUL

#define SIMD_DIV_I8   SIMD_SCALAR_DIV
#define SIMD_DIV_I16  SIMD_SCALAR_DIV
#define SIMD_DIV_I32  SIMD_SCALAR_DIV
#define SIMD_DIV_I64  SIMD_SCALAR_DIV

#define SIMD_MIN_I8   SIMD_SCALAR_MIN
#define SIMD_MIN_I16  SIMD_SCALAR_MIN
#define SIMD_MIN_I32  SIMD_SCALAR_MIN
#define SIMD_MIN_I64  SIMD_SCALAR_MIN

#define SIMD_MAX_I8   SIMD_SCALAR_MAX
#define SIMD_MAX_I16  SIMD_SCALAR_MAX
#define SIMD_MAX_I32  SIMD_SCALAR_MAX
#define SIMD_MAX_I64  SIMD_SCALAR_MAX

#define SIMD_AND_I8   SIMD_SCALAR_AND
#define SIMD_AND_I16  SIMD_SCALAR_AND
#define SIMD_AND_I32  SIMD_SCALAR_AND
#define SIMD_AND_I64  SIMD_SCALAR_AND

#define SIMD_OR_I8    SIMD_SCALAR_OR
#define SIMD_OR_I16   SIMD_SCALAR_OR
#define SIMD_OR_I32   SIMD_SCALAR_OR
#define SIMD_OR_I64   SIMD_SCALAR_OR

#define SIMD_XOR_I8   SIMD_SCALAR_XOR
#define SIMD_XOR_I16  SIMD_SCALAR_XOR
#define SIMD_XOR_I32  SIMD_SCALAR_XOR
#define SIMD_XOR_I64  SIMD_SCALAR_XOR

// ------------------ GENERIC DISPATCH ------------------
#define SIMD_ADD(dest,a,b,len) _Generic((a), \
    float*: SIMD_ADD_F32, double*: SIMD_ADD_F64, \
    int8_t*: SIMD_ADD_I8, uint8_t*: SIMD_ADD_I8, \
    int16_t*: SIMD_ADD_I16, uint16_t*: SIMD_ADD_I16, \
    int32_t*: SIMD_ADD_I32, uint32_t*: SIMD_ADD_I32, \
    int64_t*: SIMD_ADD_I64, uint64_t*: SIMD_ADD_I64)(dest,a,b,len)

#define SIMD_SUB(dest,a,b,len) _Generic((a), \
    float*: SIMD_SUB_F32, double*: SIMD_SUB_F64, \
    int8_t*: SIMD_SUB_I8, uint8_t*: SIMD_SUB_I8, \
    int16_t*: SIMD_SUB_I16, uint16_t*: SIMD_SUB_I16, \
    int32_t*: SIMD_SUB_I32, uint32_t*: SIMD_SUB_I32, \
    int64_t*: SIMD_SUB_I64, uint64_t*: SIMD_SUB_I64)(dest,a,b,len)

#define SIMD_MUL(dest,a,b,len) _Generic((a), \
    float*: SIMD_MUL_F32, double*: SIMD_MUL_F64, \
    int8_t*: SIMD_MUL_I8, uint8_t*: SIMD_MUL_I8, \
    int16_t*: SIMD_MUL_I16, uint16_t*: SIMD_MUL_I16, \
    int32_t*: SIMD_MUL_I32, uint32_t*: SIMD_MUL_I32, \
    int64_t*: SIMD_MUL_I64, uint64_t*: SIMD_MUL_I64)(dest,a,b,len)

#define SIMD_DIV(dest,a,b,len) _Generic((a), \
    float*: SIMD_DIV_F32, double*: SIMD_DIV_F64, \
    int8_t*: SIMD_DIV_I8, uint8_t*: SIMD_DIV_I8, \
    int16_t*: SIMD_DIV_I16, uint16_t*: SIMD_DIV_I16, \
    int32_t*: SIMD_DIV_I32, uint32_t*: SIMD_DIV_I32, \
    int64_t*: SIMD_DIV_I64, uint64_t*: SIMD_DIV_I64)(dest,a,b,len)

#define SIMD_MIN(dest,a,b,len) _Generic((a), \
    float*: SIMD_SCALAR_MIN, double*: SIMD_SCALAR_MIN, \
    int8_t*: SIMD_MIN_I8, uint8_t*: SIMD_MIN_I8, \
    int16_t*: SIMD_MIN_I16, uint16_t*: SIMD_MIN_I16, \
    int32_t*: SIMD_MIN_I32, uint32_t*: SIMD_MIN_I32, \
    int64_t*: SIMD_MIN_I64, uint64_t*: SIMD_MIN_I64)(dest,a,b,len)

#define SIMD_MAX(dest,a,b,len) _Generic((a), \
    float*: SIMD_SCALAR_MAX, double*: SIMD_SCALAR_MAX, \
    int8_t*: SIMD_MAX_I8, uint8_t*: SIMD_MAX_I8, \
    int16_t*: SIMD_MAX_I16, uint16_t*: SIMD_MAX_I16, \
    int32_t*: SIMD_MAX_I32, uint32_t*: SIMD_MAX_I32, \
    int64_t*: SIMD_MAX_I64, uint64_t*: SIMD_MAX_I64)(dest,a,b,len)

#define SIMD_AND(dest,a,b,len) _Generic((a), \
    int8_t*: SIMD_AND_I8, uint8_t*: SIMD_AND_I8, \
    int16_t*: SIMD_AND_I16, uint16_t*: SIMD_AND_I16, \
    int32_t*: SIMD_AND_I32, uint32_t*: SIMD_AND_I32, \
    int64_t*: SIMD_AND_I64, uint64_t*: SIMD_AND_I64)(dest,a,b,len)

#define SIMD_OR(dest,a,b,len) _Generic((a), \
    int8_t*: SIMD_OR_I8, uint8_t*: SIMD_OR_I8, \
    int16_t*: SIMD_OR_I16, uint16_t*: SIMD_OR_I16, \
    int32_t*: SIMD_OR_I32, uint32_t*: SIMD_OR_I32, \
    int64_t*: SIMD_OR_I64, uint64_t*: SIMD_OR_I64)(dest,a,b,len)

#define SIMD_XOR(dest,a,b,len) _Generic((a), \
    int8_t*: SIMD_XOR_I8, uint8_t*: SIMD_XOR_I8, \
    int16_t*: SIMD_XOR_I16, uint16_t*: SIMD_XOR_I16, \
    int32_t*: SIMD_XOR_I32, uint32_t*: SIMD_XOR_I32, \
    int64_t*: SIMD_XOR_I64, uint64_t*: SIMD_XOR_I64)(dest,a,b,len)

// ------------------ CLEANUP ------------------
#undef SIMD_SCALAR_OP
#undef SIMD_SCALAR_MUL
#undef SIMD_SCALAR_DIV
#undef SIMD_SCALAR_MIN
#undef SIMD_SCALAR_MAX
#undef SIMD_SCALAR_AND
#undef SIMD_SCALAR_OR
#undef SIMD_SCALAR_XOR
#undef SIMD_ADD_F32
#undef SIMD_SUB_F32
#undef SIMD_MUL_F32
#undef SIMD_DIV_F32
#undef SIMD_ADD_F64
#undef SIMD_SUB_F64
#undef SIMD_MUL_F64
#undef SIMD_DIV_F64
#undef SIMD_ADD_I8
#undef SIMD_SUB_I8
#undef SIMD_ADD_I16
#undef SIMD_SUB_I16
#undef SIMD_ADD_I32
#undef SIMD_SUB_I32
#undef SIMD_ADD_I64
#undef SIMD_SUB_I64
#undef SIMD_MUL_I8
#undef SIMD_MUL_I16
#undef SIMD_MUL_I32
#undef SIMD_MUL_I64
#undef SIMD_DIV_I8
#undef SIMD_DIV_I16
#undef SIMD_DIV_I32
#undef SIMD_DIV_I64
#undef SIMD_MIN_I8
#undef SIMD_MIN_I16
#undef SIMD_MIN_I32
#undef SIMD_MIN_I64
#undef SIMD_MAX_I8
#undef SIMD_MAX_I16
#undef SIMD_MAX_I32
#undef SIMD_MAX_I64
#undef SIMD_AND_I8
#undef SIMD_AND_I16
#undef SIMD_AND_I32
#undef SIMD_AND_I64
#undef SIMD_OR_I8
#undef SIMD_OR_I16
#undef SIMD_OR_I32
#undef SIMD_OR_I64
#undef SIMD_XOR_I8
#undef SIMD_XOR_I16
#undef SIMD_XOR_I32
#undef SIMD_XOR_I64

#endif // C_CLASS_CORE_SIMD_FULL_HCLASS
