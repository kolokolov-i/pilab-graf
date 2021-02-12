#pragma once

namespace IPF
{
    class MatrixD
    {
    protected:
        int w, h;
        double *data;

    public:

        enum BorderResolver
        {
            Zero,
            Replicate,
            Reflect,
            Wrap
        };

        MatrixD(int w, int h);
        MatrixD(int w, int h, double value);
        MatrixD(int w, int h, const double *data);
        ~MatrixD();

        int getW();
        int getH();
        double getValue(int x, int y);
        void setValue(int x, int y, double v);
        BorderResolver borderResolver;

    };
} // namespace IPF