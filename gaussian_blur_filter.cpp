#include "gaussian_blur_filter.h"

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {
}

void GaussianBlurFilter::ApplyFilter(BmpIm& image) const {
    auto pixies = image.GetPixiesPtr();
    std::vector<Pixel> n_pixies;
    std::vector<float> kernel_line;
    float kernel_sum = 0;
    const int border = static_cast<int>(3 * sigma_);
    const float sig_2 = static_cast<float>(2 * sigma_ * sigma_);
    const float sqrt_pi_sig_2 = static_cast<float>(sqrt(sig_2 * std::numbers::pi));
    const int height = static_cast<int>(image.GetHeight() - 1);
    const int width = static_cast<int>(image.GetWidth() - 1);
    for (int y = -border; y < border; ++y) {
        float value_for_kernel_line =
            static_cast<float>(std::pow(std::numbers::e, static_cast<float>(-y * y) / sig_2) / sqrt_pi_sig_2);
        kernel_sum += value_for_kernel_line;
        kernel_line.push_back(value_for_kernel_line);
    }
    for (size_t y = 0; y < kernel_line.size(); ++y) {
        kernel_line[y] /= kernel_sum;
    }
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            Pixel n_pix;
            n_pix.r = 0;
            n_pix.g = 0;
            n_pix.b = 0;
            for (int m = -border; m < border; ++m) {
                n_pix.r += (*pixies)[y][std::max(std::min(x + m, width), 0)].r * kernel_line[m + border];
                n_pix.g += (*pixies)[y][std::max(std::min(x + m, width), 0)].g * kernel_line[m + border];
                n_pix.b += (*pixies)[y][std::max(std::min(x + m, width), 0)].b * kernel_line[m + border];
            }
            n_pixies.push_back(n_pix);
        }
    }
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            Pixel n_pix;
            n_pix.r = 0;
            n_pix.g = 0;
            n_pix.b = 0;
            for (int m = -border; m < border; ++m) {
                n_pix.r +=
                    n_pixies[(std::max(std::min(y + m, height), 0)) * image.GetWidth() + x].r * kernel_line[m + border];
                n_pix.g +=
                    n_pixies[(std::max(std::min(y + m, height), 0)) * image.GetWidth() + x].g * kernel_line[m + border];
                n_pix.b +=
                    n_pixies[(std::max(std::min(y + m, height), 0)) * image.GetWidth() + x].b * kernel_line[m + border];
            }
            image.SetPixCol(n_pix, x, y);
        }
    }
    std::cout << "Gaussian blur filter applied" << std::endl;
}
