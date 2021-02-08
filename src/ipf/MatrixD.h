#pragma once

namespace IPF
{
    class MatrixD
    {
    private:
        int w, h;
        double *data;

    public:
        MatrixD(int w, int h);
        MatrixD(int w, int h, double value);
        MatrixD(int w, int h, const double *data);
        ~MatrixD();

        int getW();
        int getH();
        const double *getData();
    };
} // namespace IPF