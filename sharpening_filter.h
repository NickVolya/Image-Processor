#pragma once

#include "filter_father.h"
#include <algorithm>

class SharpeningFilter : public Filter {
public:
    ~SharpeningFilter() override = default;
    void ApplyFilter(BmpIm& image) const override;
};