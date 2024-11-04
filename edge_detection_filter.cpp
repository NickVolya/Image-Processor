#include "edge_detection_filter.h"
#include "grayscale_filter.h"

void EdgeDetection::ApplyFilter(BmpIm& image) const {
    GrayscaleFilter gs;
    gs.ApplyFilter(image);
    auto pixies = image.GetPixiesPtr();
    std::vector<Pixel> n_pixies;
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            Pixel n_pix;
            n_pix = CountAColourWithMatrix(pixies, x, y, {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}});
            if (n_pix.r > threshold_ || n_pix.g > threshold_ || n_pix.b > threshold_) {
                n_pix.r = 1;
                n_pix.g = 1;
                n_pix.b = 1;
            } else {
                n_pix.r = 0;
                n_pix.g = 0;
                n_pix.b = 0;
            }
            n_pixies.push_back(n_pix);
        }
    }
    size_t i = 0;
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            image.SetPixCol(n_pixies[i], x, y);
            ++i;
        }
    }
    std::cout << "Edge detection filter applied" << std::endl;
}

EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {
}
