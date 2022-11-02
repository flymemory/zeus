
#include "vector.h"

struct FVector2D
{
    float X, Y;

public:
    inline FVector2D();
    inline FVector2D(float _X, float _Y);

    inline FVector2D    operator/(float Scale) const;
    inline FVector2D    operator+(const FVector& V) const;
    inline FVector2D    operator-(const FVector& V) const;
    inline FVector2D    operator*(float F) const;
    /**
     * @brief Calculates dot product with another vector.
     * 
     * @param V The other vector.
     * @return The dot product.
     */
    inline float    operator|(const FVector2D& V) const;
    /**
     * @brief Calculates cross product with another vector.
     * 
     * @param V The other vector.
     * @return The cross product.
     */
    inline float    operator^(const FVector2D& V) const;

    inline float DotProduct() const;
    inline float CrossProduct() const;

    inline static float Distance(const FVector2D& A, const FVector2D& B);
    inline static float DistanceSquared(const FVector2D& A, const FVector2D& B);

    inline float Size() const;
    inline float SizeSquared() const;

    inline void Normalize();

    inline FVector2D GetRotated(float Degree) const;

    inline bool  IsNearlyZero(float Tolerance);
};

inline float FVector2D::operator|(const FVector2D& V) const
{
    return (X*V.X + Y*V.Y);
}

inline float FVector2D::operator^(const FVector2D& V) const
{
    return (Y*V.X - X*V.Y);
}

inline float FVector2D::Distance(const FVector2D& A, const FVector2D& B)
{
    return FMath::Sqrt( DistanceSquared(A, B) );
}

inline float FVector2D::DistanceSquared(const FVector2D& A, const FVector2D& B)
{
    return (A.X-B.X)*(A.X-B.X) + (A.Y-B.Y)*(A.Y-B.Y);
}

inline float FVector2D::SizeSquared() const
{
    return X*X + Y*Y;
}

inline float FVector2D::Size() const
{
    return FMath::Sqrt( X*X + Y*Y );
}

inline void FVector2D::Normalize()
{
    float Square = X*X + Y*Y;

    if ( Square > FLT_TOLERANCE )
    {
        float InvSqaure = FMath::InvSqrt(Square);

        X *= InvSqaure;
        Y *= InvSqaure;

        return;
    }

    X = 0.f;
    Y = 0.f;
}

