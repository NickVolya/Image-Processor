#include <catch.hpp>

#include "bmp_image.h"
#include "crop_filter.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "sharpening_filter.h"
#include "edge_detection_filter.h"
#include "gaussian_blur_filter.h"
#include "my_filter_salt_and_pepper.h"
#include <iostream>

TEST_CASE("Reading BMP file") {
    std::cout << "Reading BMP file test:" << std::endl;
    const size_t width = 0;
    const size_t height = 0;
    BmpIm* image = new BmpIm(width, height);
    const char* input_path_exist =
        "../tasks/image_processor/test_script/"
        "data/lenna.bmp";           // существующий путь
    image->Read(input_path_exist);  // напишет, что файл прочитан
    delete image;

    BmpIm* new_image = new BmpIm(width, height);
    const char* input_path_notexist =
        "../tasks/image_processor/test_script/"
        "data/notexist.bmp";  // несуществующий путь
    new_image->Read(input_path_notexist);  // должно появиться сообщение о том, что файл нельзя прочитать
    delete new_image;

    BmpIm* new2_image = new BmpIm(width, height);
    const char* input_path_jpg =
        "../tasks/image_processor/"
        "test_pictures/kit.jpg";       // считывает не BMP файл
    new2_image->Read(input_path_jpg);  // должно написать, что не BMP файл
    delete new2_image;
    std::cout << "***********" << std::endl;
}

TEST_CASE("Crop filter") {
    std::cout << "Crop filter test:" << std::endl;
    const size_t width = 0;
    const size_t height = 0;
    BmpIm* image = new BmpIm(width, height);
    const char* input_path =
        "../tasks/image_processor/test_script/"
        "data/lenna.bmp";
    image->Read(input_path);
    CropFilter crop;
    const int wdth = 500;
    const int ht = 3000;
    crop.ApplyFilter(wdth, ht, *image); // обрежет только по ширине
    delete image;

    BmpIm* image2 = new BmpIm(width, height);
    image2->Read(input_path);
    const int wdth2 = -500;
    const int ht2 = 1000;
    crop.ApplyFilter(wdth2, ht2, *image2);
    delete image2;
    std::cout << "***********" << std::endl;
}

TEST_CASE("Grayscale filter") {
    std::cout << "Grayscale filter test:" << std::endl;
    const size_t width = 0;
    const size_t height = 0;
    BmpIm* image = new BmpIm(width, height);
    const char* input_path =
        "../tasks/image_processor/test_script/"
        "data/lenna.bmp";
    image->Read(input_path);
    GrayscaleFilter gs;
    gs.ApplyFilter(*image);
    delete image;
    std::cout << "***********" << std::endl;
}

TEST_CASE("Negative filter") {
    std::cout << "Negative filter test:" << std::endl;
    const size_t width = 0;
    const size_t height = 0;
    BmpIm* image = new BmpIm(width, height);
    const char* input_path =
        "../tasks/image_processor/test_script/"
        "data/lenna.bmp";
    image->Read(input_path);
    NegativeFilter neg;
    neg.ApplyFilter(*image);
    neg.ApplyFilter(*image); // возвращается к исходному состоянию
    delete image;
    std::cout << "***********" << std::endl;
}

TEST_CASE("Sharpening filter") {
    std::cout << "Sharpening filter test:" << std::endl;
    const size_t width = 0;
    const size_t height = 0;
    BmpIm* image = new BmpIm(width, height);
    const char* input_path =
        "../tasks/image_processor/test_script/"
        "data/lenna.bmp";
    image->Read(input_path);
    SharpeningFilter sharp;
    sharp.ApplyFilter(*image);
    delete image;
    std::cout << "***********" << std::endl;
}

TEST_CASE("Edge detection filter") {
    std::cout << "Edge detection filter test:" << std::endl;
    const size_t width = 0;
    const size_t height = 0;
    BmpIm* image = new BmpIm(width, height);
    const char* input_path =
        "../tasks/image_processor/test_script/"
        "data/lenna.bmp";
    image->Read(input_path);
    const int threshold = 100000;
    EdgeDetection edge(threshold);
    edge.ApplyFilter(*image);
    delete image;

    BmpIm* image2 = new BmpIm(width, height);
    image2->Read(input_path);
    const int threshold2 = -20;
    EdgeDetection edge2(threshold2);
    edge2.ApplyFilter(*image2);
    delete image2;
    std::cout << "***********" << std::endl;
}

TEST_CASE("Gaussian blur filter") {
    std::cout << "Gaussian blur filter test:" << std::endl;
    const size_t width = 0;
    const size_t height = 0;
    BmpIm* image = new BmpIm(width, height);
    const char* input_path =
        "../tasks/image_processor/test_script/"
        "data/lenna.bmp";
    image->Read(input_path);
    const float sigma = 3;
    GaussianBlurFilter blur(sigma);
    blur.ApplyFilter(*image);
    delete image;
    std::cout << "***********" << std::endl;
}

TEST_CASE("Salt and pepper filter") {
    std::cout << "Salt and pepper filter test:" << std::endl;
    const size_t width = 0;
    const size_t height = 0;
    BmpIm* image = new BmpIm(width, height);
    const char* input_path =
        "../tasks/image_processor/test_script/"
        "data/lenna.bmp";
    image->Read(input_path);
    const float sigma = 0.4;
    SaltAndPepperFilter sap(sigma);
    sap.ApplyFilter(*image);
    delete image;

    BmpIm* image2 = new BmpIm(width, height);
    image2->Read(input_path);
    const float sigma2 = 10;
    SaltAndPepperFilter sap2(sigma2);
    sap2.ApplyFilter(*image2);
    delete image2;

    BmpIm* image3 = new BmpIm(width, height);
    image3->Read(input_path);
    const float sigma3 = -50;
    SaltAndPepperFilter sap3(sigma3);
    sap2.ApplyFilter(*image3);
    delete image3;
    std::cout << "***********" << std::endl;
}