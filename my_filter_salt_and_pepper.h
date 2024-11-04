#pragma once

#include "filter_father.h"
#include "grayscale_filter.h"
#include "gaussian_blur_filter.h"
#include <random>

// Фильтр делает изображение черно-белым и добавляет белый шум на изображение. Принимает в качестве параметра величину
// sigma от 0 до 1, которая влияет на степень шума

class SaltAndPepperFilter : public Filter {
public:
    SaltAndPepperFilter() = default;
    explicit SaltAndPepperFilter(double sigma);
    ~SaltAndPepperFilter() override = default;
    void ApplyFilter(BmpIm& image) const override;

private:
    double sigma_;
};
