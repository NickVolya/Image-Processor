#pragma once

#include "bmp_image.h"
#include <array>
#include "cmath"

class Filter {
public:
    virtual void ApplyFilter(BmpIm& image) const = 0;
    virtual ~Filter() = default;
    Pixel CountAColourWithMatrix(std::vector<std::vector<Pixel>>* ptr, int x, int y,
                                 std::vector<std::vector<float>> matrix) const;
};