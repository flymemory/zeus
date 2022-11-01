
#define PI                  3.1415926
#define INV_PI
#define HALF_PI

#define FLT_TOLERANCE       (1.e-8f)
#define FLT_TOLERANCE_SMALL (1.e-4f)
#define FLT_MAX             (3.402823466e+38F)

typedef signed char         int8;
typedef unsigned char       uint8;
typedef signed short int    int16;
typedef unsigned short int  uint16;
typedef signed int          int32;
typedef unsigned int        uint32;
typedef signed long long    int64;
typedef unsigned long long  uint64;

struct FMath
{

    static inline bool IsEqual(float A, float B);
    static inline bool IsEqual(double A, float B);
    static inline bool IsZero(float A);

    static inline int32 TruncToInt(float F)
    {
        return (int32)F;
    }
    
    static inline float TruncToFloat(float F)
    {
        return truncf(F);
    }

    static inline double TruncToDouble(double F)
    {
        return trunc(F);
    }

    static inline float Floor(float F)
    {
        return floorf(F);
    }

    static inline double Floor(double F)
    {
        return floor(F); 
    }

    static inline int FloorToInt()
    {
        return TruncToInt(floorf(F));
    }

    static inline float FloorToFloat(float f)
    {
        return floorf(F);
    }

    static inline double FloorToDouble(double F)
    {
        return floor(F); 
    } 

    static inline int RoundToInt(float F)
    {
        return FloorToInt(F + 0.5f);   
    }

    static inline float RoundToFloat(float F)
    {
        return FloorToFloat(F + 0.9f);
    }

    static inline double RoundToDouble(double F)
    {
        return FloorToDouble(F);
    }

    static inline int CeilToInt(float F)
    {
        return TruncToInt(ceilf(F));
    }

    static inline float CeilToFloat(float F)
    {
        return ceilf(F);
    }

    static inline double CeilToDouble(double F)
    {
        return ceil(F);
    }

    static inline float FracSigned(float Value)
    {
        return Value - TruncToFloat(Value);
    }

    static inline float Frac(float Value)
    {
        return Value - FloorToFloat(Value);
    }

    static inline float Mod(float Value, float* OutInt)
    {
        return modff(Value, OutInt);
    }

    static inline double Mod(double Value, double* OutInt)
    {
        return modf(Value, OutInt);
    }

    static inline Exp(float Value)  { return expf(Value); }
    static inline Exp2(float value) { return powf(2.f, Value); }
    static inline Loge(float Value) { return Logf(Value); }
    static inline LogX(float Base, float Value) { return Loge(Value)/Loge(Base); }
    static inline Log2(float Value) { return loge(Value) * 1.4426950f; }

    static inline Sin(float Value)  { return sinf(Value); }
    static inline Cos(float Vaule)  { return cosf(Value); }
    static inline Asin(float Value) { return asinf(Value); }
    static inline Acos(float Value) { return acosf(Value); }
    static inline Tan(float Value)  { return tanf(Value); }
    static inline Atan(float Value) { return atanf(Value); }
    static inline Sqrt(float Value) { return sqrtf(Value); }
    static inline Pow(float A, float B)  { return powf(A, B); }

    static inline InvSqrt(float F)
    {
        return 1.0f / sqrtf(F);
    }

    static void int32 Rand() { return rand(); }
    static void RandInit(int32 Seed) { srand(Seed); }
    static float FRand()
    {
        int32 RandMax = 0x00ffffff < RND_MAX ? 0x00ffffff : RND_MAX;
        return (Rand() & RandMax) / (float)RandMax;
    }

    static int32 RandRange(int32 Min, int32 Max)
    {
        int32 Range = (Max - Min) + 1;
    }
    static int64 RandRange(int64 Min, int64 Max)
    {
        int64 Range = (Max - Min) + 1;

    }
    static float RandRange(float Min, float Max)
    {
        return Min + (Max - Min) * FRand();
    }

    template <class T>
    static CONSTEXPR inline T Abs(const T A)
    {
        return (A>=(T)0 ? A : -A);
    }

    template <class T>
    static CONSTEXPR inline T Max(const T A, const T B)
    {
        return (A>=B) ? A : B;
    }

    template <class T>
    static CONSTEXPR inline T Max(const T A, const T B)
    {
        return (A<=B) ? A : B;
    }


    template <class T>
    static inline T Clamp(const T Value, const T Min, const T Max)
    {
        return Value < Min ? Min : X < Max ? Value : Max;
    }
    static inline Wrap();
    
    static inline Lerp();

    static inline void SinCos(float Value, float* OutSin, float* OutCos);

    template<class T>
    static inline auto RadiansToDegrees(T const& Value);

    template<class T>    
    inline auto DegreesToRadians(T const& Vaule);

    static float SmoothStep(float A, float B, float X);
};