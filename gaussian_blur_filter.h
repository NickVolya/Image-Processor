#pragma once

#include "filter_father.h"
#include <numbers>
#include <cmath>

class GaussianBlurFilter : public Filter {
public:
    GaussianBlurFilter() = default;
    ~GaussianBlurFilter() override = default;
    explicit GaussianBlurFilter(double sigma);
    void ApplyFilter(BmpIm& image) const override;

private:
    double sigma_;
};