#include "crop_filter.h"

void CropFilter::ApplyFilter(size_t width, size_t height, BmpIm& image) const {
    if (width > image.GetWidth() && height > image.GetHeight()) {
        return;
    } else if (width > image.GetWidth()) {
        auto pixies = image.GetPixiesPtr();
        std::reverse(pixies->begin(), pixies->end());
        pixies->resize(height);
        std::reverse(pixies->begin(), pixies->end());
        std::cout << "Crop filter applied" << std::endl;
    } else if (height > image.GetHeight()) {
        auto pixies = image.GetPixiesPtr();
        for (size_t y = 0; y < image.GetHeight(); ++y) {
            (*pixies)[y].resize(width);
        }
        std::cout << "Crop filter applied" << std::endl;
    } else {
        auto pixies = image.GetPixiesPtr();
        std::reverse(pixies->begin(), pixies->end());
        pixies->resize(height);
        std::reverse(pixies->begin(), pixies->end());
        for (size_t y = 0; y < height; ++y) {
            (*pixies)[y].resize(width);
        }
        std::cout << "Crop filter applied" << std::endl;
    }
}
