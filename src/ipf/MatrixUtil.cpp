#include "MatrixUtil.h"

#include "IPF.h"

#include <iomanip>
#include <cmath>

using namespace IPF;

MatrixD *MatrixUtil::identity(int w)
{
    double *data = new double[w * w];
    for (int i = 0; i < w; i++)
    {
        data[i * w + i] = 1;
    }
    MatrixD *resultMatrix = new MatrixD(w, w, data);
    delete[] data;
    return resultMatrix;
}

MatrixD *MatrixUtil::filterCrossCorel(MatrixD *image, MatrixD *kernel, BorderResolver borderResolver)
{
    int krnW = kernel->getW();
    int krnH = kernel->getH();
    if (!(krnW % 2) || !(krnH % 2))
    {
        throw Invalid_Parameter("Kernel size must be odd");
    }
    int krnKW = krnW / 2;
    int krnKH = krnH / 2;
    int w = image->getW();
    int h = image->getH();
    const double *src = image->getData();
    const double *krn = kernel->getData();
    double *result = new double[w * h];
    for (int iH = 0; iH < h; iH++)
    {
        for (int iW = 0; iW < w; iW++)
        {
            double v = 0;
            for (int jH = 0, kH = -krnKH; jH < krnH; jH++, kH++)
            {
                for (int jW = 0, kW = -krnKW; jW < krnW; jW++, kW++)
                {
                    double t;
                    int aW, aH;
                    aW = iW + kW;
                    aH = iH + kH;
                    if (aW < 0 || aH < 0 || aW >= w || aH >= h)
                    {
                        switch (borderResolver)
                        {
                        case BorderResolver::Replicate:
                        {
                            if (aW < 0 || aW >= w)
                            {
                                aW = iW;
                            }
                            if (aH < 0 || aH >= h)
                            {
                                aH = iH;
                            }
                            t = src[aH * w + aW];
                        }
                        break;
                        case BorderResolver::Reflect:
                        {
                            if (aW >= w)
                            {
                                aW = w - 1 - (aW % w);
                            }
                            else if (aW < 0)
                            {
                                aW = -1 - (aW % w);
                            }
                            if (aH >= h)
                            {
                                aH = h - 1 - (aH % h);
                            }
                            else if (aH < 0)
                            {
                                aH = -1 - (aH % h);
                            }
                            t = src[aH * w + aW];
                        }
                        break;
                        case BorderResolver::Wrap:
                        {
                            if (aW >= w)
                            {
                                aW = aW % w;
                            }
                            else if (aW < 0)
                            {
                                aW = w + (aW % w);
                            }
                            if (aH >= h)
                            {
                                aH = aH % h;
                            }
                            else if (aH < 0)
                            {
                                aH = h + (aH % h);
                            }
                            t = src[aH * w + aW];
                        }
                        break;
                        case BorderResolver::Zero:
                        default:
                            t = 0;
                        }
                    }
                    else
                    {
                        t = src[aH * w + aW];
                    }
                    v += t * krn[jH * krnW + jW];
                }
            }
            result[iH * w + iW] = v;
        }
    }
    MatrixD *resultMatrix = new MatrixD(w, h, result);
    delete[] result;
    return resultMatrix;
}
MatrixD *MatrixUtil::filterConvolute(MatrixD *image, MatrixD *kernel, BorderResolver borderResolver)
{
    int krnW = kernel->getW();
    int krnH = kernel->getH();
    if (!(krnW % 2) || !(krnH % 2))
    {
        throw Invalid_Parameter("Kernel size must be odd");
    }
    int krnKW = krnW / 2;
    int krnKH = krnH / 2;
    int w = image->getW();
    int h = image->getH();
    const double *src = image->getData();
    const double *krn = kernel->getData();
    double *result = new double[w * h];
    for (int iH = 0; iH < h; iH++)
    {
        for (int iW = 0; iW < w; iW++)
        {
            double v = 0;
            for (int jH = 0, kH = -krnKH; jH < krnH; jH++, kH++)
            {
                for (int jW = 0, kW = -krnKW; jW < krnW; jW++, kW++)
                {
                    double t;
                    int aW, aH;
                    aW = iW + kW;
                    aH = iH + kH;
                    if (aW < 0 || aH < 0 || aW >= w || aH >= h)
                    {
                        switch (borderResolver)
                        {
                        case BorderResolver::Replicate:
                        {
                            if (aW < 0 || aW >= w)
                            {
                                aW = iW;
                            }
                            if (aH < 0 || aH >= h)
                            {
                                aH = iH;
                            }
                            t = src[aH * w + aW];
                        }
                        break;
                        case BorderResolver::Reflect:
                        {
                            if (aW >= w)
                            {
                                aW = w - 1 - (aW % w);
                            }
                            else if (aW < 0)
                            {
                                aW = -1 - (aW % w);
                            }
                            if (aH >= h)
                            {
                                aH = h - 1 - (aH % h);
                            }
                            else if (aH < 0)
                            {
                                aH = -1 - (aH % h);
                            }
                            t = src[aH * w + aW];
                        }
                        break;
                        case BorderResolver::Wrap:
                        {
                            if (aW >= w)
                            {
                                aW = aW % w;
                            }
                            else if (aW < 0)
                            {
                                aW = w + (aW % w);
                            }
                            if (aH >= h)
                            {
                                aH = aH % h;
                            }
                            else if (aH < 0)
                            {
                                aH = h + (aH % h);
                            }
                            t = src[aH * w + aW];
                        }
                        break;
                        case BorderResolver::Zero:
                        default:
                            t = 0;
                        }
                    }
                    else
                    {
                        t = src[aH * w + aW];
                    }
                    v += t * krn[jH * krnW + jW];
                }
            }
            result[iH * w + iW] = v;
        }
    }
    MatrixD *resultMatrix = new MatrixD(w, h, result);
    delete[] result;
    return resultMatrix;
}

MatrixD *MatrixUtil::kernelSingle(int sizeK)
{
    int w, h;
    w = h = sizeK * 2 + 1;
    double *result = new double[w * h];
    result[w * sizeK + sizeK] = 1;
    MatrixD *resultMatrix = new MatrixD(w, h, result);
    delete[] result;
    return resultMatrix;
}

// Square matrix for Gaussian filter
MatrixD *MatrixUtil::kernelGaussQ(double vrc, int sizeH)
{
    if (sizeH == 0)
    {
        sizeH = 3 * vrc;
    }
    int mW, mH;
    mW = mH = sizeH * 2 + 1;
    double *result = new double[mW * mH];
    double pi = acos(-1.0);
    double t1 = 2 * vrc * vrc;
    double t2 = 1. / (t1 * pi);
    for (int iH = 0, kH = -sizeH; iH < mH; iH++, kH++)
    {
        for (int iW = 0, kW = -sizeH; iW < mW; iW++, kW++)
        {
            double v = t2 * exp(-(kW * kW + kH * kH) / t1);
            result[iH * mW + iW] = v;
        }
    }
    MatrixD *resultMatrix = new MatrixD(mW, mH, result);
    delete[] result;
    return resultMatrix;
}

// Vector matrix for Gaussian filter
MatrixD *MatrixUtil::kernelGaussV(double vrc, int sizeW, int sizeH)
{
    int mW, mH, mL;
    if (sizeW == 0 && sizeH > 0)
    {
        mW = 1;
        mH = sizeH * 2 + 1;
        mL = sizeH;
    }
    else if (sizeH == 0 && sizeW > 0)
    {
        mW = sizeW * 2 + 1;
        mH = 1;
        mL = sizeW;
    }
    else
    {
        throw Invalid_Parameter("One of sizes must be zero");
    }
    int n = mW * mH;
    double *result = new double[n];
    double pi = acos(-1.0);
    double t1 = 2 * vrc * vrc;
    double t2 = 1. / (sqrt(2 * pi) * vrc);
    for (int i = 0, k = -mL; i < n; i++, k++)
    {
        double v = t2 * exp(-(k * k) / t1);
        result[i] = v;
    }
    MatrixD *resultMatrix = new MatrixD(mW, mH, result);
    delete[] result;
    return resultMatrix;
}

MatrixD *MatrixUtil::calc(MatrixD *matrix, double (*unaryFunction)(double a))
{
    int w = matrix->getW();
    int h = matrix->getH();
    int n = w * h;
    double *result = new double[n];
    const double *src = matrix->getData();
    const double *p1 = src;
    double *r = result;
    for (int i = 0; i < n; i++, p1++, r++)
    {
        *r = unaryFunction(*p1);
    }
    MatrixD *resultMatrix = new MatrixD(w, h, result);
    delete[] result;
    return resultMatrix;
}

MatrixD *MatrixUtil::calc(MatrixD *m1, MatrixD *m2, double (*binaryFunction)(double a, double b))
{
    if (m1->getW() != m2->getW() || m1->getH() != m2->getH())
    {
        throw Invalid_Parameter("Matrices must be same size");
    }
    int w = m1->getW();
    int h = m1->getH();
    int n = w * h;
    double *result = new double[n];
    const double *src1 = m1->getData();
    const double *p1 = src1;
    const double *src2 = m2->getData();
    const double *p2 = src2;
    double *r = result;
    for (int i = 0; i < n; i++, p1++, p2++, r++)
    {
        *r = binaryFunction(*p1, *p2);
    }
    MatrixD *resultMatrix = new MatrixD(w, h, result);
    delete[] result;
    return resultMatrix;
}

void MatrixUtil::print(std::ostream &out, MatrixD *matrix)
{
    int w = matrix->getW();
    int h = matrix->getH();
    const double *table = matrix->getData();
    out << "Matrix [" << w << "," << h << "]\n";
    out << std::fixed;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            out << std::setprecision(3) << std::setw(7) << std::right << table[i * w + j];
        }
        out << "\n";
    }
    out.flush();
}