#ifndef C_CLASS_CORE_SIMD_HCLASS
#define C_CLASS_CORE_SIMD_HCLASS

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
#define SIMD_EXT SCALAR_EMULATION
#endif
#else
#define USE_SIMD 0
#define SIMD_EXT DISABLED
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

// ------------------ HORIZONTAL SUM FALLBACK ------------------
#define SIMD_HSUM_SCALAR(type, a, len) ({ type sum=0; for(size_t i=0;i<(len);i++) sum += (a)[i]; sum; })

#if USE_SIMD && (SIMD_EXT >= SSE2)
// Horizontal sum for int8
static inline int8_t SIMD_HSUM_I8(int8_t* a, size_t len) {
size_t i = 0;
__m128i sum_vec = _mm_setzero_si128();
for (; i+16 <= len; i+=16) sum_vec = _mm_add_epi8(sum_vec, _mm_loadu_si128((__m128i*)(a+i)));
int8_t tmp[16]; _mm_storeu_si128((__m128i*)tmp, sum_vec);
int8_t sum=0; for(int j=0;j<16;j++) sum+=tmp[j];
for(;i<len;i++) sum+=a[i]; return sum;
}
// Horizontal sum for int16
static inline int16_t SIMD_HSUM_I16(int16_t* a, size_t len) {
size_t i=0; __m128i sum_vec=_mm_setzero_si128();
for(; i+8<=len; i+=8) sum_vec=_mm_add_epi16(sum_vec,_mm_loadu_si128((__m128i*)(a+i)));
int16_t tmp[8]; _mm_storeu_si128((__m128i*)tmp,sum_vec);
int16_t sum=0; for(int j=0;j<8;j++) sum+=tmp[j];
for(;i<len;i++) sum+=a[i]; return sum;
}
// Horizontal sum for int32
static inline int32_t SIMD_HSUM_I32(int32_t* a, size_t len) {
size_t i=0; __m128i sum_vec=_mm_setzero_si128();
for(;i+4<=len;i+=4) sum_vec=_mm_add_epi32(sum_vec,_mm_loadu_si128((__m128i*)(a+i)));
int32_t tmp[4]; _mm_storeu_si128((__m128i*)tmp,sum_vec);
int32_t sum=0; for(int j=0;j<4;j++) sum+=tmp[j];
for(;i<len;i++) sum+=a[i]; return sum;
}
// Horizontal sum for int64
static inline int64_t SIMD_HSUM_I64(int64_t* a, size_t len) {
size_t i=0; __m128i sum_vec=_mm_setzero_si128();
for(;i+2<=len;i+=2) sum_vec=_mm_add_epi64(sum_vec,_mm_loadu_si128((__m128i*)(a+i)));
int64_t tmp[2]; _mm_storeu_si128((__m128i*)tmp,sum_vec);
int64_t sum=0; for(int j=0;j<2;j++) sum+=tmp[j];
for(;i<len;i++) sum+=a[i]; return sum;
}
#else
#define SIMD_HSUM_I8(a,len) SIMD_HSUM_SCALAR(int8_t,a,len)
#define SIMD_HSUM_I16(a,len) SIMD_HSUM_SCALAR(int16_t,a,len)
#define SIMD_HSUM_I32(a,len) SIMD_HSUM_SCALAR(int32_t,a,len)
#define SIMD_HSUM_I64(a,len) SIMD_HSUM_SCALAR(int64_t,a,len)
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

#define SIMD_HSUM(a,len) _Generic((a), \
int8_t*: SIMD_HSUM_I8, uint8_t*: SIMD_HSUM_I8, \
int16_t*: SIMD_HSUM_I16, uint16_t*: SIMD_HSUM_I16, \
int32_t*: SIMD_HSUM_I32, uint32_t*: SIMD_HSUM_I32, \
int64_t*: SIMD_HSUM_I64, uint64_t*: SIMD_HSUM_I64 \
)(a,len)

// ------------------ CLEANUP ------------------
#undef SIMD_SCALAR_OP
#undef SIMD_SCALAR_MUL
#undef SIMD_SCALAR_DIV
#undef SIMD_SCALAR_MIN
#undef SIMD_SCALAR_MAX
#undef SIMD_SCALAR_AND
#undef SIMD_SCALAR_OR
#undef SIMD_SCALAR_XOR

#endif // C_CLASS_CORE_SIMD_HCLASS
