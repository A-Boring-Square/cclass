#include "cclass.h"
#include "../math.h"
#include "types.h"
#include <stdint.h>
#include <stddef.h>
float _exp_float(float x);
double _exp_double(double x);
float _log_float(float x);
double _log_double(double x);
float _sqrt_float(float x);
double _sqrt_double(double x);
float _cbrt_float(float x);
double _cbrt_double(double x);
float _pow_float(float x,float y);
double _pow_double(double x,double y);
float _sin_float(float x){ SIMD_HINT for(;x>PI||x<-PI;) { x-=TAU*(x>PI); x+=TAU*(x<-PI); } float x2=x*x; return x*(1.0f-x2*(1.0f/6.0f-x2*(1.0f/120.0f-x2/5040.0f))); }
double _sin_double(double x){ SIMD_HINT for(;x>PI||x<-PI;) { x-=TAU*(x>PI); x+=TAU*(x<-PI); } double x2=x*x; return x*(1.0-x2*(1.0/6.0+x2*(1.0/120.0-x2*(1.0/5040.0+x2*(1.0/362880.0-x2/39916800.0))))); }
float _cos_float(float x){ SIMD_HINT for(;x>PI||x<-PI;) { x-=TAU*(x>PI); x+=TAU*(x<-PI); } float x2=x*x; return 1.0f-x2*(0.5f-x2*(1.0f/24.0f-x2*(1.0f/720.0f+x2/40320.0f))); }
double _cos_double(double x){ SIMD_HINT for(;x>PI||x<-PI;) { x-=TAU*(x>PI); x+=TAU*(x<-PI); } double x2=x*x; return 1.0-x2*(0.5-x2*(1.0/24.0+x2*(-1.0/720.0+x2*(1.0/40320-x2/3628800.0)))); }
float _tan_float(float x){ return _sin_float(x)/_cos_float(x); }
double _tan_double(double x){ return _sin_double(x)/_cos_double(x); }
float _asin_float(float x){ if(x<-1.0f)x=-1.0f;if(x>1.0f)x=1.0f; float x2=x*x; return x*(1.0f+x2*(1.0f/6.0f+x2*(3.0f/40.0f+x2/112.0f))); }
double _asin_double(double x){ if(x<-1.0)x=-1.0;if(x>1.0)x=1.0; double x2=x*x; return x*(1.0+x2*(1.0/6.0+x2*(3.0/40.0+x2*(5.0/112.0+x2/256.0)))); }
float _acos_float(float x){ return PI/2.0f-_asin_float(x); }
double _acos_double(double x){ return PI/2.0-_asin_double(x); }
float _atan_float(float x){ float absx=x>0?x:-x; float t; if(absx>1.0f) t=PI/2.0f-_atan_float(1.0f/absx); else { float x2=x*x; t=x*(1.0f-x2/3.0f+x2*x2/5.0f-x2*x2*x2/7.0f);} return x<0?-t:t; }
double _atan_double(double x){ double absx=x>0?x:-x; double t; if(absx>1.0) t=PI/2.0-_atan_double(1.0/absx); else { double x2=x*x; t=x*(1.0-x2/3.0+x2*x2/5.0-x2*x2*x2/7.0);} return x<0?-t:t; }
float _atan2_float(float y,float x){ if(x>0) return _atan_float(y/x); if(x<0&&y>=0) return _atan_float(y/x)+PI; if(x<0&&y<0) return _atan_float(y/x)-PI; if(x==0&&y>0) return PI/2.0f; if(x==0&&y<0) return -PI/2.0f; return 0.0f; }
double _atan2_double(double y,double x){ if(x>0) return _atan_double(y/x); if(x<0&&y>=0) return _atan_double(y/x)+PI; if(x<0&&y<0) return _atan_double(y/x)-PI; if(x==0&&y>0) return PI/2.0; if(x==0&&y<0) return -PI/2.0; return 0.0; }
float _exp_float(float x){ const float ln2_inv=1.4426950408889634f; const float ln2=0.6931471805599453f; float n_float=x*ln2_inv; int n=(int)(n_float+(n_float>=0?0.5f:-0.5f)); float r=x-n*ln2; float r2=r*r,r3=r2*r,r4=r3*r,r5=r4*r; float exp_r=1.0f+r+0.5f*r2+0.1666666667f*r3+0.0416666667f*r4+0.0083333333f*r5; return exp_r*(1<<n); }
double _exp_double(double x){ const double ln2_inv=1.4426950408889634074; const double ln2=0.6931471805599453; double n_double=x*ln2_inv; long long n=(long long)(n_double+(n_double>=0?0.5:-0.5)); double r=x-n*ln2; double r2=r*r,r3=r2*r,r4=r3*r,r5=r4*r,r6=r5*r,r7=r6*r; double exp_r=1.0+r+0.5*r2+r3/6.0+r4/24.0+r5/120.0+r6/720.0+r7/5040.0; return exp_r*(1LL<<n); }
float _sinh_float(float x){ register float ex=_exp_float(x); return (ex-ONE/ex)*0.5f; }
double _sinh_double(double x){ register double ex=_exp_double(x); return (ex-ONE/ex)*0.5; }
float _cosh_float(float x){ register float ex=_exp_float(x); return (ex+ONE/ex)*0.5f; }
double _cosh_double(double x){ register double ex=_exp_double(x); return (ex+ONE/ex)*0.5; }
float _tanh_float(float x){ return _sinh_float(x)/_cosh_float(x); }
double _tanh_double(double x){ return _sinh_double(x)/_cosh_double(x); }
float _log_float(float x){ if(x<=0.0f) return -1e30f; union { float f; uint32_t u; } v={x}; int e=((v.u>>23)&0xFF)-127; v.u=(v.u&0x7FFFFF)|0x3F800000; float f=v.f-1.0f,f2=f*f,f3=f2*f; return f-0.5f*f2+f3/3.0f+e*LN2; }
double _log_double(double x){ if(x<=0.0) return -1e300; union { double d; uint64_t u; } v={x}; int e=((v.u>>52)&0x7FF)-1023; v.u=(v.u&0xFFFFFFFFFFFFFull)|0x3FF0000000000000ULL; double f=v.d-1.0,f2=f*f,f3=f2*f; return f-0.5*f2+f3/3.0+e*LN2; }
float _log10_float(float x){ return _log_float(x)*0.4342944819032518f; }
double _log10_double(double x){ return _log_double(x)*0.43429448190325182765; }
float _logn_float(float x,float y){ return _log_float(x)/_log_float(y); }
double _logn_double(double x,double y){ return _log_double(x)/_log_double(y); }
float _pow_float(float x,float y){ int yi=(int)y; if((float)yi==y){ float r=1.0f; int exp=yi>0?yi:-yi; float base=x; while(exp){ if(exp&1) r*=base; base*=base; exp>>=1; } return yi>=0?r:1.0f/r; } return _exp_float(y*_log_float(x)); }
double _pow_double(double x,double y){ long long yi=(long long)y; if((double)yi==y){ double r=1.0; long long exp=yi>0?yi:-yi; double base=x; while(exp){ if(exp&1) r*=base; base*=base; exp>>=1; } return yi>=0?r:1.0/r; } return _exp_double(y*_log_double(x)); }
float _sqrt_float(float x){ if(x<0.0f)return 0.0f; register float guess=x>1.0f?x:1.0f; SIMD_HINT for(int i=0;i<6;i++) guess=0.5f*(guess+x/guess); return guess; }
double _sqrt_double(double x){ if(x<0.0)return 0.0; register double guess=x>1.0?x:1.0; SIMD_HINT for(int i=0;i<6;i++) guess=0.5*(guess+x/guess); return guess; }
float _cbrt_float(float x){ register float guess=x>1.0f?x:1.0f; SIMD_HINT for(int i=0;i<6;i++) guess=(2.0f*guess+x/(guess*guess))/3.0f; return guess; }
double _cbrt_double(double x){ register double guess=x>1.0?x:1.0; SIMD_HINT for(int i=0;i<6;i++) guess=(2.0*guess+x/(guess*guess))/3.0; return guess; }
float _root_float(float x,float n){ if(x<0.0f&&((int)n%2==0)) return 0.0f; return _pow_float(x,1.0f/n); }
double _root_double(double x,double n){ if(x<0.0&&((long long)n%2==0)) return 0.0; return _pow_double(x,1.0/n); }
float _floor_float(float x){ int i=(int)x; return x<i?(float)(i-1):(float)i; }
double _floor_double(double x){ long long i=(long long)x; return x<i?(double)(i-1):(double)i; }
float _ceil_float(float x){ int i=(int)x; return x>i?(float)(i+1):(float)i; }
double _ceil_double(double x){ long long i=(long long)x; return x>i?(double)(i+1):(double)i; }
float _round_float(float x){ return _floor_float(x+0.5f); }
double _round_double(double x){ return _floor_double(x+0.5); }
float _trunc_float(float x){ return (float)((int)x); }
double _trunc_double(double x){ return (double)((long long)x); }
float _fmod_float(float x,float y){ if(y==0.0f) return 0.0f; float div=x/y; return x-y*_trunc_float(div); }
double _fmod_double(double x,double y){ if(y==0.0) return 0.0; double div=x/y; return x-y*_trunc_double(div); }
int _abs_int(int x){ return x<0?-x:x; }
int8_t _abs_int8(int8_t x){ return x<0?-x:x; }
int16_t _abs_int16(int16_t x){ return x<0?-x:x; }
int32_t _abs_int32(int32_t x){ return x<0?-x:x; }
int64_t _abs_int64(int64_t x){ return x<0?-x:x; }
float _abs_float(float x){ return x<0.0f?-x:x; }
double _abs_double(double x){ return x<0.0?-x:x; }
float _clamp_float(float x,float min,float max){ if(x<min)return min; if(x>max)return max; return x; }
double _clamp_double(double x,double min,double max){ if(x<min)return min; if(x>max)return max; return x; }
int _clamp_int(int x,int min,int max){ if(x<min)return min; if(x>max)return max; return x; }
float _lerp_float(float a,float b,float t){ return a+t*(b-a); }
double _lerp_double(double a,double b,double t){ return a+t*(b-a); }
float _sum_float(const float *restrict arr,size_t n){ register float s=0.0f; SIMD_HINT for(size_t i=0;i<n;i++) s+=arr[i]; return s; }
double _sum_double(const double *restrict arr,size_t n){ register double s=0.0; SIMD_HINT for(size_t i=0;i<n;i++) s+=arr[i]; return s; }
float _mean_float(const float *restrict arr,size_t n){ return n?_sum_float(arr,n)/n:0.0f; }
double _mean_double(const double *restrict arr,size_t n){ return n?_sum_double(arr,n)/n:0.0; }
float _stddev_float(const float *restrict arr,size_t n){ if(!n)return 0.0f; register float m=_mean_float(arr,n),s=0.0f; SIMD_HINT for(size_t i=0;i<n;i++){ float d=arr[i]-m; s+=d*d; } return _sqrt_float(s/n); }
double _stddev_double(const double *restrict arr,size_t n){ if(!n)return 0.0; register double m=_mean_double(arr,n),s=0.0; SIMD_HINT for(size_t i=0;i<n;i++){ double d=arr[i]-m; s+=d*d; } return _sqrt_double(s/n); }
float _derivative_float(float (*f)(float),float x,float h){ return (f(x+h)-f(x-h))/(2.0f*h); }
double _derivative_double(double (*f)(double),double x,double h){ return (f(x+h)-f(x-h))/(2.0*h); }
float _integral_float(float (*f)(float),float a,float b,size_t n){ if(n==0)return 0.0f; register float dx=(b-a)/n,sum=0.0f; SIMD_HINT for(size_t i=0;i<n;i++) sum+=f(a+i*dx)*dx; return sum; }
double _integral_double(double (*f)(double),double a,double b,size_t n){ if(n==0)return 0.0; register double dx=(b-a)/n,sum=0.0; SIMD_HINT for(size_t i=0;i<n;i++) sum+=f(a+i*dx)*dx; return sum; }