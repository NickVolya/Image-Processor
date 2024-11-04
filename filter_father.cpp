#include "filter_father.h"

Pixel Filter::CountAColourWithMatrix(std::vector<std::vector<Pixel>> *ptr, int x, int y,
                                     std::vector<std::vector<float>> matrix) const {
    Pixel n_pix;
    int s_o_matrix_line = static_cast<int>(matrix.size());
    int aver = (s_o_matrix_line - 1) / 2;
    float sum_r = 0;
    float sum_g = 0;
    float sum_b = 0;
    for (int i = -aver; i < s_o_matrix_line - aver; ++i) {
        for (int j = -aver; j < s_o_matrix_line - aver; ++j) {
            sum_r += matrix[i + aver][j + aver] *
                     (*ptr)[std::max(std::min(y + i, static_cast<int>((*ptr).size() - 1)), 0)]
                           [std::max(std::min(x + j, static_cast<int>((*ptr)[y].size() - 1)), 0)]
                               .r;
            sum_g += matrix[i + aver][j + aver] *
                     (*ptr)[std::max(std::min(y + i, static_cast<int>((*ptr).size() - 1)), 0)]
                           [std::max(std::min(x + j, static_cast<int>((*ptr)[y].size() - 1)), 0)]
                               .g;
            sum_b += matrix[i + aver][j + aver] *
                     (*ptr)[std::max(std::min(y + i, static_cast<int>((*ptr).size() - 1)), 0)]
                           [std::max(std::min(x + j, static_cast<int>((*ptr)[y].size() - 1)), 0)]
                               .b;
        }
    }
    n_pix.r = std::min(1.0f, std::max(0.0f, sum_r));
    n_pix.g = std::min(1.0f, std::max(0.0f, sum_g));
    n_pix.b = std::min(1.0f, std::max(0.0f, sum_b));
    return n_pix;
}