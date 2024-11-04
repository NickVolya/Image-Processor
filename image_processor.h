#pragma once
#include "filter_father.h"
#include "grayscale_filter.h"
#include "crop_filter.h"
#include "negative_filter.h"
#include "edge_detection_filter.h"
#include "sharpening_filter.h"
#include "gaussian_blur_filter.h"
#include "first_try_my_filter_relief.h"
#include "my_filter_salt_and_pepper.h"

struct CollectionOfFilters {
    GrayscaleFilter gs_;
    CropFilter crop_;
    NegativeFilter neg_;
    SharpeningFilter sharp_;
    EdgeDetection CreateEdge(double threshold) {
        return EdgeDetection(threshold);
    }
    GaussianBlurFilter CreateBlur(double sigma) {
        return GaussianBlurFilter(sigma);
    }
    ReliefFilter rel_;
    SaltAndPepperFilter CreateSaltAndPepper(double sigma) {
        return SaltAndPepperFilter(sigma);
    }
};
