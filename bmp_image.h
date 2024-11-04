#pragma once

#include <vector>
#include <iostream>

struct Pixel {
    float r;
    float g;
    float b;
    Pixel();
    Pixel(float r, float g, float b);
    ~Pixel();
    bool operator==(const Pixel& other) const;
};

class BmpIm {
public:
    BmpIm(size_t width, size_t height);
    ~BmpIm();
    Pixel GetPixCol(size_t x, size_t y) const;
    void SetPixCol(const Pixel& pixel, size_t x, size_t y);
    void Read(const char* path);
    void Export(const char* path) const;
    int GetHeight() const;
    int GetWidth() const;
    std::vector<std::vector<Pixel>>* GetPixiesPtr();

private:
    std::vector<std::vector<Pixel>> pixies_;
};