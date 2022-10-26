
#include "vector.h"

struct FVector4
{
    float X;
    float Y;
    float Z;
    float W;

public:
    FVector4();
    FVector4(const FVector& V, float W);
    FVector4(float X, float Y, float Z, float W);
};


inline FVector4::FVector4()
{

}

inline FVector4::FVector4(const FVector& V, float _W)
{
    X = V.X;
    Y = V.Y;
    Z = V.Z;
    W = _W;
}

inline FVector4::FVector4(float _X, float _Y, float _Z, float _W)
{
    X = _X;
    Y = _Y;
    Z = _Z;
    W = _W;
}