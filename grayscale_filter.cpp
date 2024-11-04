#include "grayscale_filter.h"

void GrayscaleFilter::ApplyFilter(BmpIm& image) const {
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Pixel cur_pix = image.GetPixCol(x, y);
            Pixel n_pix;
            const float s_o_r = 0.299f;
            const float s_o_g = 0.587f;
            const float s_o_b = 0.114f;
            n_pix.r = cur_pix.r * s_o_r + cur_pix.g * s_o_g + cur_pix.b * s_o_b;
            n_pix.g = n_pix.r;
            n_pix.b = n_pix.r;
            image.SetPixCol(n_pix, x, y);
        }
    }
    std::cout << "Grayscale filter applied" << std::endl;
}
