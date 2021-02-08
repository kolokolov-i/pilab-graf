#pragma once

#include "MatrixD.h"

namespace IPF
{
    enum class BorderResolver
    {
        Zero,
        Replicate,
        Reflect,
        Wrap
    };

    class MatrixUtil
    {
    public:
        static MatrixD *identity(int w);
        static MatrixD *filterCrossCorel(MatrixD *image, MatrixD *kernel, BorderResolver borderResolver = BorderResolver::Replicate);
        static MatrixD *filterConvolute(MatrixD *image, MatrixD *kernel, BorderResolver borderResolver = BorderResolver::Replicate);
        static MatrixD *calc(MatrixD *m1, double (*unaryFunction)(double a));
        static MatrixD *calc(MatrixD *m1, MatrixD *m2, double (*binaryFunction)(double a, double b));

        // separational filter
        static MatrixD *kernelSingle(int sizeK);
        static MatrixD *kernelGauss(double variance, int sizeK = 0);
    };
} // namespace IPF