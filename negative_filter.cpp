#include "negative_filter.h"

void NegativeFilter::ApplyFilter(BmpIm& image) const {
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Pixel cur_pix = image.GetPixCol(x, y);
            Pixel n_pix;
            n_pix.r = 1 - cur_pix.r;
            n_pix.g = 1 - cur_pix.g;
            n_pix.b = 1 - cur_pix.b;
            image.SetPixCol(n_pix, x, y);
        }
    }
    std::cout << "Negative filter applied" << std::endl;
}
