#include "sharpening_filter.h"

void SharpeningFilter::ApplyFilter(BmpIm& image) const {
    auto pixies = image.GetPixiesPtr();
    std::vector<Pixel> n_pixies;
    const int s_o_central = 5;
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            n_pixies.push_back(CountAColourWithMatrix(pixies, x, y, {{0, -1, 0}, {-1, s_o_central, -1}, {0, -1, 0}}));
        }
    }
    size_t i = 0;
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            image.SetPixCol(n_pixies[i], x, y);
            ++i;
        }
    }
    std::cout << "Sharpening filter applied" << std::endl;
}
