#pragma once

#include "filter_father.h"

class CropFilter {
public:
    ~CropFilter() = default;
    void ApplyFilter(size_t width, size_t height, BmpIm& image) const;
};
