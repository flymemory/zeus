#include "math.h"

#pragma once

struct FVector
 {
    /** X Component of Vector. */
    float X;
    /** Y Component of Vector. */
    float Y;
    /** Z Component of Vector. */
    float Z;

public:
    FVector();
    FVector(float _X, float _Y, float _Z);

public:
    /**
     * @brief Calculate the dot product.
     * 
     * @param V The other vector.
     * @return Result of the dot product. 
     */
    inline float    operator|(const FVector& V) const;
    /**
     * @brief Calculate the cross product. 
     * 
     * @param V The other vector.  
     * @return Result vector of the cross product.
     */
    inline FVector  operator^(const FVector& V) const; 

    inline FVector  operator+(const FVector& V) const;
    inline FVector  operator-(const FVector& V) const;
    inline FVector  operator*(float V) const;
    inline FVector  operator/(float V) const;

    /**
     * @brief Normailize this vector.
     * 
     */
    inline void Normalize();

    /**
     * @brief Is this vector normalized. 
     * 
     * @return true This vector is normalized. 
     * @return false This vector is NOT normalized.
     */
    inline bool IsNormalized() const;

    /**
     * @brief Get the length of this vector. 
     * 
     * @return The length of this vector.
     */
    inline float Size() const;

    /**
     * @brief Get the squared length of this vector. 
     * 
     * @return The squared length of this vector. 
     */
    inline float SizeSquared() const;

    inline static float Distance(const FVector& A, const FVector& B);
    inline static float DistanceSquared(const FVector& A, const FVector& B);

    /**
     * @brief Calculate dot product of two vectors.
     * 
     * @param A First vector.
     * @param B Second vector.
     * @return Result of the dot product.
     */
    inline static float DotProduct(const FVector& A, const FVector& B);

    /**
     * @brief Calculate cross product of two vectors. 
     * 
     * @param A First vector. 
     * @param B Second vector.
     * @return Result vector of the cross product.
     */
    inline static FVector CrossProduct(const FVector& A, const FVector& B);


public:
    FVector RotateAngleAxis();

    /**
     * @brief Project the vector to another vector.
     * 
     * @param V The another vector. 
     * @return Result vector of projected vector.
     */
    inline FVector ProjectOn(const FVector& V);
    /**
     * @brief Project the vector to another normalized vector.
     * 
     * @param VN The another normalized vector. 
     * @return Result vector of projected vector.
     */
    inline FVector ProjectOnNormal(const FVector& VN);

    /**
     * @brief Test if the another point on the left side.
     * 
     * @param point The another point. 
     * @return true The point is on the left side.
     * @return false The point is not on the left side.
     */
    bool    ToLeft(const FVector& point);
    /**
     * @brief Get the intersection point of a line and a plane. 
     * 
     * @param PointStart The start point of the line.
     * @param PointEnd  The end point of the line. 
     * @param PlaneOrigin The origin point of the plane.
     * @param PlaneNormal The normal of the the plane.
     * @return Result the point of intersection.
     */
    static FVector LinePlaneIntersection(const FVector& PointStart, const FVector& PointEnd, const FVector& PlaneOrigin, const FVector& PlaneNormal);
    /**
     * @brief Get the intersection point of a line and a shpere.
     * 
     * @param PointStart The start point of the line.
     * @param PointEnd  The end point of the line. 
     * @param Origin The origin point of the sphere.
     * @param Radius The radius of the sphere.
     * @param Result1 The first point of intersection.
     * @param Result2 The second point of intersection (if exist).
     * @return true Intersection exists.
     * @return false Intersection not exists.
     */
    static bool    LineSphereIntersection(const FVector& PointStart, const FVector& PointEnd, const FVector& Origin, float Radius, float *const Result1, float *const Result2);
};

inline FVector::FVector()
{

}

inline FVector::FVector(float _X, float _Y, float _Z) 
: X(_X), Y(_Y), Z(_Z)
{

}

inline float FVector::operator|(const FVector& V) const
{
    return (X*V.X + Y*V.Y + Z*V.Z);    
}

inline float FVector::DotProduct(const FVector& A, const FVector& B)
{
    return A|B;
}

inline FVector FVector::operator^(const FVector& V) const
{
    return FVector(
        Y*V.Z - Z*V.Y,
        Z*V.X - X*V.Z,
        X*V.Y - Y*V.X
    );
}

inline FVector  FVector::operator+(const FVector& V) const
{
    return FVector(
        X + V.X, 
        Y + V.Y,
        Z + V.Z
    );
}

inline FVector  FVector::operator-(const FVector& V) const
{
    return FVector(
        X - V.X, 
        Y - V.Y,
        Z - V.Z
    );
}
    
inline FVector  FVector::operator*(float V) const
{
     return FVector(
        X * V, 
        Y * V,
        Z * V
    );   
}

inline FVector  FVector::operator/(float V) const
{
    return FVector(
        X / V, 
        Y / V,
        Z / V
    );
}


inline FVector FVector::CrossProduct(const FVector& A, const FVector& B)
{
    return A^B;
}

inline float FVector::Size() const
{
    return FMath::Sqrt(X*X + Y*Y + Z*Z);
}

inline float FVector::SizeSquared() const
{
    return X*X + Y*Y + Z*Z;
}

inline float FVector::Distance(const FVector& A, const FVector& B)
{
    return FMath::Sqrt(FVector::DistanceSquared(A, B));
}

inline float FVector::DistanceSquared(const FVector& A, const FVector& B)
{
    return (B.X*B.X-A.X*A.X)*(B.X*B.X-A.X*A.X)+(B.Y*B.Y-A.Y*A.Y)*(B.Y*B.Y-A.Y*A.Y)+(B.Z*B.Z-A.Z*A.Z)*(B.Z*B.Z-A.Z*A.Z);
}

inline FVector FVector::ProjectOn(const FVector& V)
{
    return (V*((*this|V)/(V|V)));
}

inline FVector FVector::ProjectOnNormal(const FVector& VN)
{
    return (VN*(*this|VN));
}

inline bool FVector::ToLeft(const FVector& pointToTest)
{
    // normal of the two vectors.
    FVector N = *this ^ pointToTest;

    if (N.Z > 0) 
        return true;

    return false;
}

FVector FVector::LinePlaneIntersection(const FVector& PointStart, const FVector& PointEnd, const FVector& PlaneOrigin, const FVector& PlaneNormal)
{
    FVector LineDirection = PointEnd - PointStart;

    return PointStart + LineDirection * ((PlaneOrigin - PointStart) | PlaneNormal) / (PlaneNormal | LineDirection); 
}

bool FVector::LineSphereIntersection(const FVector&PointStart, const FVector& PointEnd, const FVector& Origin, float Radius, float *const Result1, float *const Result2)
{
    FVector LineNormal = PointEnd - PointStart;
    FVector PO = PointStart  - Origin;

    float a = LineNormal | LineNormal;
    float b = (PO * 2.0f) | LineNormal;
    float c = (PO | PO) - Radius * Radius;

    float B = b * b - 4 * a * c;

    if (FMath::Abs(a) == 0 || B < 0)
    {
        return false;
    }

    if (Result1 != nullptr)
        *Result1 = (-b + FMath::Sqrt(B)) / (2 * a);
    if (Result2 != nullptr)
        *Result1 = (-b - FMath::Sqrt(B)) / (2 * a);

    return true;
}