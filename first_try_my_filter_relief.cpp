#include "first_try_my_filter_relief.h"
#include "grayscale_filter.h"

void ReliefFilter::ApplyFilter(BmpIm& image) const {
    GrayscaleFilter gs;
    gs.ApplyFilter(image);
    auto pixies = image.GetPixiesPtr();
    std::vector<Pixel> n_pixies;
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            n_pixies.push_back(CountAColourWithMatrix(
                pixies, x, y,
                {{-1, -1, -1, -1, 0}, {-1, -1, -1, 0, 1}, {-1, -1, 0, 1, 1}, {-1, 0, 1, 1, 1}, {0, 1, 1, 1, 1}}));
        }
    }
    size_t i = 0;
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            image.SetPixCol(n_pixies[i], x, y);
            ++i;
        }
    }
}