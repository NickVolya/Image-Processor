#include "bmp_image.h"

#include <iostream>
#include <fstream>

Pixel::Pixel() : r(0), g(0), b(0) {
}

Pixel::Pixel(float r, float g, float b) : r(r), g(g), b(b) {
}

Pixel::~Pixel() {
}

bool Pixel::operator==(const Pixel& other) const {
    return r == other.r && g == other.g && b == other.b;
}

BmpIm::BmpIm(size_t width, size_t height) {
    for (size_t i = 0; i < height; ++i) {
        pixies_.push_back(std::vector<Pixel>(width));
    }
}

BmpIm::~BmpIm() {
}

Pixel BmpIm::GetPixCol(size_t x, size_t y) const {
    return pixies_[y][x];
}

void BmpIm::SetPixCol(const Pixel& pixel, size_t x, size_t y) {
    pixies_[y][x].r = pixel.r;
    pixies_[y][x].g = pixel.g;
    pixies_[y][x].b = pixel.b;
}

void BmpIm::Read(const char* path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "File could not be open" << std::endl;
        return;
    }

    const int f_head_size = 14;
    const int inf_head_size = 40;

    unsigned char f_head[f_head_size];
    f.read(reinterpret_cast<char*>(f_head), f_head_size);

    if (f_head[0] != 'B' || f_head[1] != 'M') {
        std::cout << "Not a BMP image" << std::endl;
        f.close();
        return;
    }

    unsigned char inf_head[inf_head_size];
    f.read(reinterpret_cast<char*>(inf_head), inf_head_size);

    const int bit_8 = 8;
    const int bit_16 = 16;
    const int bit_24 = 24;
    const int ind_inf_head_5 = 5;
    const int ind_inf_head_6 = 6;
    const int ind_inf_head_7 = 7;
    const int ind_inf_head_8 = 8;
    const int ind_inf_head_9 = 9;
    const int ind_inf_head_10 = 10;
    const int ind_inf_head_11 = 11;
    int width_im = inf_head[4] + (inf_head[ind_inf_head_5] << bit_8) + (inf_head[ind_inf_head_6] << bit_16) +
                   (inf_head[ind_inf_head_7] << bit_24);
    int height_im = inf_head[ind_inf_head_8] + (inf_head[ind_inf_head_9] << bit_8) +
                    (inf_head[ind_inf_head_10] << bit_16) + (inf_head[ind_inf_head_11] << bit_24);

    pixies_.resize(height_im);
    for (std::vector<Pixel>& vector : pixies_) {
        vector.resize(width_im);
    }

    const int pad_num = ((4 - (width_im * 3) % 4) % 4);
    const double s_o_rgb = 255.0;
    for (size_t y = 0; y < height_im; ++y) {
        for (size_t x = 0; x < width_im; ++x) {
            unsigned char pixel[3];
            f.read(reinterpret_cast<char*>(pixel), 3);
            pixies_[y][x].r = static_cast<float>(pixel[2] / s_o_rgb);
            pixies_[y][x].g = static_cast<float>(pixel[1] / s_o_rgb);
            pixies_[y][x].b = static_cast<float>(pixel[0] / s_o_rgb);
        }
        f.ignore(pad_num);
    }
    f.close();
    std::cout << "File read" << std::endl;
}

void BmpIm::Export(const char* path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "File could not be open";
        return;
    }

    unsigned char bmp_pad[3] = {0, 0, 0};
    const int pad_num = ((4 - (GetWidth() * 3) % 4) % 4);
    const int f_head_size = 14;
    const int inf_head_size = 40;
    const int f_size = f_head_size + inf_head_size + GetWidth() * GetHeight() * 3 + pad_num * GetHeight();

    unsigned char f_head[f_head_size];
    const int bit_8 = 8;
    const int bit_16 = 16;
    const int bit_24 = 24;
    const int ind_inf_head_5 = 5;
    const int ind_inf_head_6 = 6;
    const int ind_inf_head_7 = 7;
    const int ind_inf_head_8 = 8;
    const int ind_inf_head_9 = 9;
    const int ind_inf_head_10 = 10;
    const int ind_inf_head_11 = 11;
    const int ind_inf_head_12 = 12;
    const int ind_inf_head_13 = 13;
    const int ind_inf_head_14 = 14;
    const int ind_inf_head_15 = 15;
    const int ind_inf_head_40 = 40;
    f_head[0] = 'B';
    f_head[1] = 'M';
    f_head[2] = f_size;
    f_head[3] = f_size >> bit_8;
    f_head[4] = f_size >> bit_16;
    f_head[ind_inf_head_5] = f_size >> bit_24;
    for (size_t i = ind_inf_head_6; i < ind_inf_head_10; ++i) {
        f_head[i] = 0;
    }
    f_head[ind_inf_head_10] = f_head_size + inf_head_size;
    for (size_t i = ind_inf_head_11; i < ind_inf_head_14; ++i) {
        f_head[i] = 0;
    }

    unsigned char inf_head[inf_head_size];
    inf_head[0] = inf_head_size;
    for (size_t i = 1; i < 4; ++i) {
        inf_head[i] = 0;
    }
    inf_head[4] = GetWidth();
    inf_head[ind_inf_head_5] = GetWidth() >> bit_8;
    inf_head[ind_inf_head_6] = GetWidth() >> bit_16;
    inf_head[ind_inf_head_7] = GetWidth() >> bit_24;
    inf_head[ind_inf_head_8] = GetHeight();
    inf_head[ind_inf_head_9] = GetHeight() >> bit_8;
    inf_head[ind_inf_head_10] = GetHeight() >> bit_16;
    inf_head[ind_inf_head_11] = GetHeight() >> bit_24;
    inf_head[ind_inf_head_12] = 1;
    inf_head[ind_inf_head_13] = 0;
    inf_head[ind_inf_head_14] = bit_24;
    for (size_t i = ind_inf_head_15; i < ind_inf_head_40; ++i) {
        inf_head[i] = 0;
    }

    f.write(reinterpret_cast<char*>(f_head), f_head_size);
    f.write(reinterpret_cast<char*>(inf_head), inf_head_size);

    const float s_o_rgb = 255.0;
    for (size_t y = 0; y < GetHeight(); ++y) {
        for (size_t x = 0; x < GetWidth(); ++x) {
            unsigned char r = static_cast<unsigned char>(GetPixCol(x, y).r * s_o_rgb);
            unsigned char g = static_cast<unsigned char>(GetPixCol(x, y).g * s_o_rgb);
            unsigned char b = static_cast<unsigned char>(GetPixCol(x, y).b * s_o_rgb);

            unsigned char pixel[] = {b, g, r};

            f.write(reinterpret_cast<char*>(pixel), 3);
        }
        f.write(reinterpret_cast<char*>(bmp_pad), pad_num);
    }
    f.close();
    std::cout << "File created";
}

int BmpIm::GetHeight() const {
    return static_cast<int>(pixies_.size());
}

int BmpIm::GetWidth() const {
    return static_cast<int>(pixies_[0].size());
}

std::vector<std::vector<Pixel>>* BmpIm::GetPixiesPtr() {
    return &pixies_;
}
