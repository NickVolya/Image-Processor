#pragma once

#include "filter_father.h"

// Это первая попытка создания своего фильтра. Решил не удалять

class ReliefFilter : public Filter {
public:
    ~ReliefFilter() override = default;
    void ApplyFilter(BmpIm& image) const override;
};
