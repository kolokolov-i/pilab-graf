#include "MatrixD.h"

#include "IPF.h"

namespace IPF
{
    MatrixD::MatrixD(int pw, int ph, const double *data)
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
        for(int i = 0; i<n; i++, p1++, p2++)
        {
            *p1 = *p2;
        }
    }

    MatrixD::MatrixD(int pw, int ph)
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

    const double *MatrixD::getData()
    {
        return data;
    }
}