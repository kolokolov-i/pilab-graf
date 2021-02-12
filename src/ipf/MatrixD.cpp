#include "MatrixD.h"

#include "IPF.h"

namespace IPF
{
    MatrixD::MatrixD(int pw, int ph, const double *data)
        : borderResolver(BorderResolver::Replicate)
    {
        if (pw <= 0 || ph <= 0)
        {
            throw IPF::Invalid_Parameter("Matrix size must be greater than zero");
        }
        w = pw;
        h = ph;
        int n = w * h;
        this->data = new double[n];
        double *p1 = this->data;
        const double *p2 = data;
        for (int i = 0; i < n; i++, p1++, p2++)
        {
            *p1 = *p2;
        }
    }

    MatrixD::MatrixD(int pw, int ph)
        : borderResolver(BorderResolver::Replicate)
    {
        if (pw <= 0 || ph <= 0)
        {
            throw IPF::Invalid_Parameter("Matrix size must be greater than zero");
        }
        w = pw;
        h = ph;
        this->data = new double[w * h];
    }

    MatrixD::MatrixD(int pw, int ph, double value)
        : MatrixD(pw, ph)
    {
        for (int i = 0; i < pw * ph; i++)
        {
            data[i] = value;
        }
    }

    MatrixD::~MatrixD()
    {
        delete[] data;
    }

    int MatrixD::getW()
    {
        return w;
    }

    int MatrixD::getH()
    {
        return h;
    }

    double MatrixD::getValue(int x, int y)
    {
        double r;
        int aW, aH;
        aW = x;
        aH = y;
        switch (borderResolver)
        {
        case BorderResolver::Replicate:
        {
            aW = x < 0 ? 0 : (x >= w ? (w - 1) : x);
            aH = y < 0 ? 0 : (y >= h ? (h - 1) : y);
            r = data[aH * w + aW];
        }
        break;
        case BorderResolver::Reflect:
        {
            aW = x < 0 ? -(x % w) : (x >= w ? (w - 1 - ((x - w) % w)) : x);
            aH = y < 0 ? -(y % h) : (y >= h ? (h - 1 - ((y - h) % h)) : y);
            r = data[aH * w + aW];
        }
        break;
        case BorderResolver::Wrap:
        {
            aW = x < 0 ? (w + (x % w)) : (x >= w ? (x % w) : x);
            aH = y < 0 ? (h + (y % h)) : (y >= h ? (y % h) : y);
            r = data[aH * w + aW];
        }
        break;
        case BorderResolver::Zero:
        default:
            if (x < 0 || y < 0 || x >= w || y >= h)
            {
                r = 0;
            }
            else
            {
                r = data[aH * w + aW];
            }
        }
        return r;
    }
    void MatrixD::setValue(int x, int y, double v)
    {
        if (x < 0 || y < 0 || x >= w || y >= h)
        {
            throw IPF::Invalid_Parameter("Matrix index out of range");
        }
        data[y * w + x] = v;
    }
} // namespace IPF