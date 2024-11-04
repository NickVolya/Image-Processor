#pragma once

#include <string>
#include <vector>
#include <iostream>

struct FilterFromParse {
    std::string_view filter_name;
    std::vector<double> parameters_;
};

class Parser {
public:
    void Parse(int argc, char* argv[]);
    const char* GetOutputPath();
    std::vector<FilterFromParse> GetFiltersFromParse();
    const char* GetInputPath();

private:
    const char* input_path_;
    const char* output_path_;
    std::vector<FilterFromParse> filters_;
};
