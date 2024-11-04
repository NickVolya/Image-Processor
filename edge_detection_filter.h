#pragma once

#include "filter_father.h"
#include <algorithm>

class EdgeDetection : public Filter {
public:
    EdgeDetection() = default;
    explicit EdgeDetection(double threshold);
    ~EdgeDetection() override = default;
    void ApplyFilter(BmpIm& image) const override;

private:
    double threshold_;
};