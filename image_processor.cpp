#include "bmp_image.h"
#include "image_processor.h"
#include "parser.h"

int main(int argc, char** argv) {
    const size_t width = 0;
    const size_t height = 0;
    BmpIm image(width, height);

    Parser par;
    par.Parse(argc, argv);

    const char* input_path = par.GetInputPath();
    image.Read(input_path);

    std::vector<FilterFromParse> filters_to_apply = par.GetFiltersFromParse();
    CollectionOfFilters collection_of_filters;
    for (const auto& filter : filters_to_apply) {
        if (filter.filter_name == "-crop") {
            if (filter.parameters_.size() != 2 || filter.parameters_[0] <= 0 || filter.parameters_[1] <= 0) {
                std::cout << "inappropriate parameters in crop" << std::endl;
                continue;
            }
            collection_of_filters.crop_.ApplyFilter(static_cast<size_t>(filter.parameters_[0]),
                                                    static_cast<size_t>(filter.parameters_[1]), image);
        } else if (filter.filter_name == "-gs") {
            collection_of_filters.gs_.ApplyFilter(image);
        } else if (filter.filter_name == "-neg") {
            collection_of_filters.neg_.ApplyFilter(image);
        } else if (filter.filter_name == "-sharp") {
            collection_of_filters.sharp_.ApplyFilter(image);
        } else if (filter.filter_name == "-edge") {
            if (filter.parameters_.size() != 1) {
                std::cout << "inappropriate parameters in edge" << std::endl;
                continue;
            }
            collection_of_filters.CreateEdge(filter.parameters_[0]).ApplyFilter(image);
        } else if (filter.filter_name == "-blur") {
            if (filter.parameters_.size() != 1) {
                std::cout << "inappropriate parameters in blur" << std::endl;
                continue;
            }
            collection_of_filters.CreateBlur(filter.parameters_[0]).ApplyFilter(image);
        } else if (filter.filter_name == "-rel") {
            collection_of_filters.rel_.ApplyFilter(image);
        } else if (filter.filter_name == "-sap") {
            if (filter.parameters_.size() != 1 || filter.parameters_[0] > 1 || filter.parameters_[0] < 0) {
                std::cout << "inappropriate parameters in sap" << std::endl;
                continue;
            }
            collection_of_filters.CreateSaltAndPepper(filter.parameters_[0]).ApplyFilter(image);
        } else {
            std::cout << "inappropriate filter name: " << filter.filter_name << std::endl;
        }
    }
    const char* output_path = par.GetOutputPath();
    image.Export(output_path);
}
