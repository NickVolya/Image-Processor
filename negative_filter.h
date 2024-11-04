#pragma once

#include "filter_father.h"

class NegativeFilter : public Filter {
public:
    ~NegativeFilter() override = default;
    void ApplyFilter(BmpIm &image) const override;
};
