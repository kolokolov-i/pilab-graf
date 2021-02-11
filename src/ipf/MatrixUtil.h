#pragma once

#include "MatrixD.h"

#include <iostream>

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

        static MatrixD *kernelSingle(int sizeK);
        static MatrixD *kernelGaussQ(double variance, int sizeK = 0);
        static MatrixD *kernelGaussV(double variance, int sizeW = 0, int sizeH = 0);

        static void print(std::ostream &out, MatrixD* matrix);
    };
} // namespace IPF