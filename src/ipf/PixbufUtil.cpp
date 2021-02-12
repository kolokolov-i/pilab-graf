#include "PixbufUtil.h"

using namespace IPF;

MatrixD *PixbufUtil::grayMatrix(Glib::RefPtr<Gdk::Pixbuf> px)
{
    guint8 *pixels = px->get_pixels();
    int w = px->get_width();
    int h = px->get_height();
    int n = w * h;
    gdouble *result = new gdouble[n];
    guint8 *p1 = pixels;
    gdouble *p2 = result;
    for (int i = 0; i < n; i++)
    {
        guint8 r, g, b;
        double m;
        r = *p1++;
        g = *p1++;
        b = *p1++;
        m = r * 0.213 + g * 0.715 + b * 0.072;
        *p2++ = m / 255.; // normalization from 0..255 to 0.0..1.0
    }
    return new MatrixD(w, h, result);
}

Glib::RefPtr<Gdk::Pixbuf> PixbufUtil::grayPixbuf(MatrixD *matrix, double min, double max)
{
    int w = matrix->getW();
    int h = matrix->getH();
    Glib::RefPtr<Gdk::Pixbuf> result = Gdk::Pixbuf::create(Gdk::Colorspace::COLORSPACE_RGB, false, 8, w, h);
    guint8 *p2 = result->get_pixels();
    double factor = 255 / (max - min); // normalization
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            double m = matrix->getValue(x, y);
            m = (m - min) * factor;
            guint8 t;
            if (m >= 0 && m <= 255)
            {
                t = (guint8)m;
            }
            else
            {
                if (m < 0)
                    t = 0;
                if (m > 255)
                    t = 255;
            }
            *p2++ = t;
            *p2++ = t;
            *p2++ = t;
        }
    }
    return result;
}