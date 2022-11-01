
#include "math.h"
#include "vector.h"
#include "vector4.h"

struct FMatrix
{
    union 
    {
        float M[4][4];
    };


public:
    FMatrix();
    FMatrix(const FVector& XAxis, const FVector& YAxis, const FVector& ZAxis, const FVector& WAxis);

    inline void SetIndentity();

    inline FMatrix operator *(const FMatrix& Other) const;
    inline void operator *=(const FMatrix& Other);

    inline FMatrix operator*(float Scale) const;
    inline void operator*=(float Scale);

    inline bool operator ==(const FMatrix& Other) const;

public:
    inline FVector4 TransformVector(const FVector4& V) const;
    inline FVector4 TransformVector(const FVector& V) const;
    inline FVector  InverseTransformVector(const FVector& V) const;
    inline FVector4 TransformPosition(const FVector& V) const;
    inline FVector  InverseTransfromPosition(const FVector& V) const;

    inline float Determinant() const;
    inline FMatrix Inverse() const;
    inline FMatrix Transposed() const;

    inline void RemovingScaling();
    inline FMatrix RemovingTranslation() const;

    inline FMatrix ApplyScale(float Scale) const;
    inline FVector GetScale() const;

    inline FVector GetTranslation() const;
    inline void SetTranslation(const FVector& Position);

    inline FVector GetAxis(int32 Axis);
    inline void GetAxis(FVector& OutXAxis, FVector& OutYAxis, FVector& OutZAxis) const;
    inline FVector GetAxisNormalized() const;
    inline void GetAxisNormalized();

public:
    inline static void MatrixMultipy(FMatrix& Result, const FMatrix& A, const FMatrix& B);
    inline static void MatrixInverse(FMatrix& Result, const FMatrix& SrcMatrix);
    inline static void MatrixTransformVector(FVector4& Result, const FVector4& V, const FMatrix& M);
};

inline FMatrix::FMatrix()
{

}

inline FMatrix::FMatrix(const FVector& XAxis, const FVector& YAxis, const FVector& ZAxis, const FVector& WAxis)
{
    M[0][0] = XAxis.X; M[0][1] = XAxis.Y; M[0][2] = XAxis.Z; M[0][3] = 0;
    M[1][0] = YAxis.X; M[1][1] = YAxis.Y; M[1][2] = YAxis.Z; M[1][3] = 0;
    M[2][0] = ZAxis.X; M[2][1] = ZAxis.Y; M[2][2] = ZAxis.Z; M[2][3] = 0;
    M[3][0] = WAxis.X; M[3][1] = WAxis.Y; M[3][2] = WAxis.Z; M[3][3] = 0;
}

inline void FMatrix::SetIndentity()
{
    M[0][0] = 1; M[0][1] = 0; M[0][2] = 0; M[0][3] = 0;
    M[1][0] = 0; M[1][1] = 1; M[1][2] = 0; M[1][3] = 0;
    M[2][0] = 0; M[2][1] = 0; M[2][2] = 1; M[2][3] = 0;
    M[3][0] = 0; M[3][1] = 0; M[3][2] = 0; M[3][3] = 1;

}


inline FMatrix FMatrix::operator*(float Scale) const
{
    FMatrix Result;

    for (int32 i=0; i<4; i++)
    {
        for (int32 j=0; j<4; j++)
        {
            Result.M[i][j] *= Scale;
        }
    }

    return Result;
}

inline void FMatrix::operator*=(float Scale)
{
    for (int32 i=0; i<4; i++)
    {
        for (int32 j=0; j<4; j++)
        {
           M[i][j] *= Scale;
        }
    }
}

inline void FMatrix::MatrixMultipy(FMatrix& Result, const FMatrix& A, const FMatrix& B)
{
    Result.M[0][0] = A.M[0][0] * B.M[0][0] + A.M[0][1] * B.M[1][0] + A.M[0][2] * B.M[2][0] + A.M[0][3] * B.M[3][0];       
    Result.M[0][1] = A.M[0][0] * B.M[0][1] + A.M[0][1] * B.M[1][1] + A.M[0][2] * B.M[2][1] + A.M[0][3] * B.M[3][1];       
    Result.M[0][2] = A.M[0][0] * B.M[0][2] + A.M[0][1] * B.M[1][2] + A.M[0][2] * B.M[2][2] + A.M[0][3] * B.M[3][2];       
    Result.M[0][3] = A.M[0][0] * B.M[0][3] + A.M[0][1] * B.M[1][3] + A.M[0][2] * B.M[2][3] + A.M[0][3] * B.M[3][3];       

    Result.M[1][0] = A.M[1][0] * B.M[0][0] + A.M[1][1] * B.M[1][0] + A.M[1][2] * B.M[2][0] + A.M[1][3] * B.M[3][0];       
    Result.M[1][1] = A.M[1][0] * B.M[0][1] + A.M[1][1] * B.M[1][1] + A.M[1][2] * B.M[2][1] + A.M[1][3] * B.M[3][1];       
    Result.M[1][2] = A.M[1][0] * B.M[0][2] + A.M[1][1] * B.M[1][2] + A.M[1][2] * B.M[2][2] + A.M[1][3] * B.M[3][2];       
    Result.M[1][3] = A.M[1][0] * B.M[0][3] + A.M[1][1] * B.M[1][3] + A.M[1][2] * B.M[2][3] + A.M[1][3] * B.M[3][3];
    
    Result.M[2][0] = A.M[2][0] * B.M[0][0] + A.M[2][1] * B.M[1][0] + A.M[2][2] * B.M[2][0] + A.M[2][3] * B.M[3][0];       
    Result.M[2][1] = A.M[2][0] * B.M[0][1] + A.M[2][1] * B.M[1][1] + A.M[2][2] * B.M[2][1] + A.M[2][3] * B.M[3][1];       
    Result.M[2][2] = A.M[2][0] * B.M[0][2] + A.M[2][1] * B.M[1][2] + A.M[2][2] * B.M[2][2] + A.M[2][3] * B.M[3][2];       
    Result.M[2][3] = A.M[2][0] * B.M[0][3] + A.M[2][1] * B.M[1][3] + A.M[2][2] * B.M[2][3] + A.M[2][3] * B.M[3][3];

    Result.M[3][0] = A.M[3][0] * B.M[0][0] + A.M[3][1] * B.M[1][0] + A.M[3][2] * B.M[2][0] + A.M[3][3] * B.M[3][0];       
    Result.M[3][1] = A.M[3][0] * B.M[0][1] + A.M[3][1] * B.M[1][1] + A.M[3][2] * B.M[2][1] + A.M[3][3] * B.M[3][1];       
    Result.M[3][2] = A.M[3][0] * B.M[0][2] + A.M[3][1] * B.M[1][2] + A.M[3][2] * B.M[2][2] + A.M[3][3] * B.M[3][2];       
    Result.M[3][3] = A.M[3][0] * B.M[0][3] + A.M[3][1] * B.M[1][3] + A.M[3][2] * B.M[2][3] + A.M[3][3] * B.M[3][3];
}


inline FMatrix FMatrix::operator*(const FMatrix& Other) const
{
    FMatrix Result;

    FMatrix::MatrixMultipy(&Result, *this, Other);

    return Result;
}

inline void FMatrix::operator*=(const FMatrix& Other)
{
    FMatrix Result;

    FMatrix::MatrixMultipy(&Result, *this, Other);

    *this = Result;
}

inline void FMatrix::MatrixInverse(FMatrix& Result, const FMatrix& SrcMatrix)
{
    FMatrix Result;

    typedef float Float4x4[4][4];
    float Det[4];

    const Float4x4& M = *((const Float4x4*)SrcMatrix);

    float m00 = M[2][2] * M[3][3] - M[2][3] * M[3][2];
    float m01 = M[1][2] * M[3][3] - M[1][3] * M[3][2];
    float m02 = M[1][2] * M[2][3] - M[1][3] * M[2][2];

    float m10 = M[2][2] * M[3][3] - M[2][3] * M[3][2];
    float m11 = M[0][2] * M[3][3] - M[0][3] * M[3][2];
    float m12 = M[0][2] * M[2][3] - M[0][3] * M[2][2];

    float m20 = M[1][2] * M[3][3] - M[1][3] * M[3][2];
    float m21 = M[0][2] * M[3][3] - M[0][3] * M[3][2];
    float m22 = M[0][2] * M[1][3] - M[0][3] * M[1][2];

    float m30 = M[1][2] * M[2][3] - M[1][3] * M[2][2];
    float m31 = M[0][2] * M[2][3] - M[0][3] * M[2][2];
    float m32 = M[0][2] * M[1][3] - M[0][3] * M[1][2];

    Det[0] = M[1][1] * m00 - M[2][1] * m01 + M[3][1] * m02;
    Det[1] = M[0][1] * m10 - M[2][1] * m11 + M[3][1] * m12;
    Det[2] = M[0][1] * m20 - M[1][1] * m21 + M[3][1] * m22;
    Det[3] = M[0][1] * m30 - M[1][1] * m31 + M[2][1] * m32;

    float Determinant = m00 * Det[0] - m10  * Det[1] + m20 * Det[2] - m30 * Det[3];
    float RDet = 1.0f / Determinant;

    Result.M[0][0] =  RDet * Det[0];
    Result.M[0][1] = -RDet * Det[1];
    Result.M[0][2] =  RDet * Det[2];
    Result.M[0][3] = -RDet * Det[3];

    Result.M[1][0] = -RDet * M[1][0] * m00 - M[2][0] * m01 + M[3][0] * m02;
    Result.M[1][1] =  RDet * M[0][0] * m10 - M[2][0] * m11 + M[3][0] * m12;
    Result.M[1][2] = -RDet * M[0][0] * m20 - M[1][0] * m21 + M[3][0] * m22;
    Result.M[1][3] =  RDet * M[0][0] * m30 - M[1][0] * m31 + M[2][0] * m32;

    Result.M[2][0] =  RDet * (M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) - M[2][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) +  M[3][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]));
    Result.M[2][1] = -RDet * (M[0][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) - M[2][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +  M[3][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]));
    Result.M[2][2] =  RDet * (M[0][0] * (M[1][1] * M[3][3] - M[2][3] * M[3][1]) - M[1][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +  M[3][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1]));
    Result.M[2][3] = -RDet * (M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]) - M[1][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]) +  M[2][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1]));

    Result.M[3][0] = -RDet * (M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) - M[2][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) +  M[3][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]));
    Result.M[3][1] =  RDet * (M[0][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) - M[2][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +  M[3][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]));
    Result.M[3][2] = -RDet * (M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) - M[1][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +  M[3][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]));
    Result.M[3][3] =  RDet * (M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) - M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +  M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]));
}

inline void FMatrix::MatrixTransformVector(FVector4& Result, const FVector4& V, const FMatrix& M)
{
    Result.X = M.M[0][0] * V.X + M.M[1][0] * V.Y + M.M[2][0] * V.Z + M.M[3][3] * V.W;
    Result.Y = M.M[0][1] * V.X + M.M[1][1] * V.Y + M.M[2][1] * V.Z + M.M[3][3] * V.W;
    Result.Z = M.M[0][2] * V.X + M.M[1][2] * V.Y + M.M[2][2] * V.Z + M.M[3][3] * V.W;
    Result.W = M.M[0][3] * V.X + M.M[1][3] * V.Y + M.M[2][3] * V.Z + M.M[3][3] * V.W;
}

inline FVector4 FMatrix::TransformVector(const FVector4& V) const
{
    FVector4 Result;

    FMatrix::MatrixTransformVector(Result, V, *this);

    return Result;
}

inline FVector4 FMatrix::TransformPosition(const FVector& V) const
{
    return TransformVector(FVector4(V, 1.0f));
}

inline FVector4 FMatrix::TransformVector(const FVector& V) const
{
    return TransformVector(FVector4(V, 0.0f));
}

inline FVector4 FMatrix::InverseTransformVector(const FVector& V) const
{
    FMatrix InverseMatrix = FMatrix::Inverse();
    return InverseMatrix.TransformVector(V);
}

inline FVector4 FMatrix::InverseTransfromPosition(const FVector& V) const
{
    FMatrix InverseMatrix = FMatrix::Inverse();
    return InverseMatrix.TransformPosition(V);
}