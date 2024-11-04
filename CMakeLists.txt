add_executable(
        image_processor
        image_processor.cpp
        bmp_image.cpp
        filter_father.h crop_filter.h crop_filter.cpp grayscale_filter.h grayscale_filter.cpp negative_filter.h negative_filter.cpp sharpening_filter.h sharpening_filter.cpp edge_detection_filter.h edge_detection_filter.cpp filter_father.cpp gaussian_blur_filter.h gaussian_blur_filter.cpp parser.h parser.cpp image_processor.h first_try_my_filter_relief.h first_try_my_filter_relief.cpp my_filter_salt_and_pepper.h my_filter_salt_and_pepper.cpp)

add_catch(test_image_processor test.cpp bmp_image.cpp crop_filter.cpp grayscale_filter.cpp negative_filter.cpp sharpening_filter.cpp filter_father.cpp edge_detection_filter.cpp gaussian_blur_filter.cpp my_filter_salt_and_pepper.cpp)