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

MatrixD *MatrixUtil::filterCrossCorel(MatrixD *image, MatrixD *kernel)
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
                    v += image->getValue(iW+kW, iH+kH) * kernel->getValue(jW, jH);
                }
            }
            result[iH * w + iW] = v;
        }
    }
    MatrixD *resultMatrix = new MatrixD(w, h, result);
    delete[] result;
    return resultMatrix;
}
MatrixD *MatrixUtil::filterConvolute(MatrixD *image, MatrixD *kernel)
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
                    v += image->getValue(iW-kW, iH-kH) * kernel->getValue(jW, jH);
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

MatrixD *MatrixUtil::calc(MatrixD *mP, double (*unaryFunction)(double a))
{
    int w = mP->getW();
    int h = mP->getH();
    MatrixD *mR = new MatrixD(w, h);
    for(int y = 0; y<h; y++)
    {
        for(int x = 0; x<w; x++)
        {
            mR->setValue(x, y, unaryFunction(mP->getValue(x, y)));
        }
    }
    return mR;
}

MatrixD *MatrixUtil::calc(MatrixD *m1, MatrixD *m2, double (*binaryFunction)(double a, double b))
{
    if (m1->getW() != m2->getW() || m1->getH() != m2->getH())
    {
        throw Invalid_Parameter("Matrices must be same size");
    }
    int w = m1->getW();
    int h = m1->getH();
    MatrixD *mR = new MatrixD(w, h);
    for(int y = 0; y<h; y++)
    {
        for(int x = 0; x<w; x++)
        {
            mR->setValue(x, y, binaryFunction(m1->getValue(x, y), m2->getValue(x, y)));
        }
    }
    return mR;
}

void MatrixUtil::print(std::ostream &out, MatrixD *matrix)
{
    int w = matrix->getW();
    int h = matrix->getH();
    out << "Matrix [" << w << "," << h << "]\n";
    out << std::fixed;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            out << std::setprecision(3) << std::setw(7) << std::right << matrix->getValue(x, y);
        }
        out << "\n";
    }
    out.flush();
}