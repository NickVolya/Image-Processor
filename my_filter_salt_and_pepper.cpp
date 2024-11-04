#include "my_filter_salt_and_pepper.h"

void SaltAndPepperFilter::ApplyFilter(BmpIm& image) const {
    if (sigma_ < 0 || sigma_ > 1) {
        std::cout << "Incorrect parameter for sap" << std::endl;
        return;
    }
    GrayscaleFilter gs;
    gs.ApplyFilter(image);
    std::vector<Pixel> n_pixies;
    int num_of_salt_and_peppers =
        static_cast<int>(sigma_ * static_cast<float>(image.GetWidth()) * static_cast<float>(image.GetHeight()));
    for (int i = 0; i < num_of_salt_and_peppers; ++i) {
        int x_pos = rand() % image.GetWidth();
        int y_pos = rand() % image.GetHeight();
        int salt_or_pepper = rand() % 2;
        if (salt_or_pepper == 1) {
            image.SetPixCol({0, 0, 0}, x_pos, y_pos);
        } else {
            image.SetPixCol({1, 1, 1}, x_pos, y_pos);
        }
    }
    GaussianBlurFilter blur(1);
    blur.ApplyFilter(image);
    std::cout << "Salt and pepper filter applied" << std::endl;
}

SaltAndPepperFilter::SaltAndPepperFilter(double sigma) : sigma_(sigma) {
}
