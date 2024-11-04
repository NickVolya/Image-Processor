#include "parser.h"

const char* Parser::GetOutputPath() {
    return output_path_;
}

std::vector<FilterFromParse> Parser::GetFiltersFromParse() {
    return filters_;
}

void Parser::Parse(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Not enough information" << std::endl;
        return;
    }
    input_path_ = argv[1];
    output_path_ = argv[2];
    for (size_t i = 3; i < argc; ++i) {
        if (argv[i][0] == '-') {
            FilterFromParse filter;
            filter.filter_name = argv[i];
            filters_.push_back(filter);
        } else {
            if (filters_.empty()) {
                if (isalpha(argv[i][0])) {
                    std::cout << "No '-' before the filter" << std::endl;
                } else {
                    std::cout << "No filter to apply these parameters" << std::endl;
                }
                return;
            } else {
                if (isalpha(argv[i][0])) {
                    std::cout << "No '-' before the filter" << std::endl;
                    return;
                }
                filters_[filters_.size() - 1].parameters_.push_back(std::stod(argv[i]));
            }
        }
    }
}

const char* Parser::GetInputPath() {
    return input_path_;
}
