#pragma once

#include "filter_father.h"

class GrayscaleFilter : public Filter {
public:
    ~GrayscaleFilter() override = default;
    void ApplyFilter(BmpIm &image) const override;
};
