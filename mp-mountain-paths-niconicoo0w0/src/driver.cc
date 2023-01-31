#include "elevation_dataset.hpp"
#include "color.hpp"
#include "path.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
    ElevationDataset data = ElevationDataset("/home/vagrant/src/mp-mountain-paths-niconicoo0w0/example-data/ex_input_data/map-input-w51-h55.dat", 51,55);

    // for (const auto& row: data.GetData()) {
    //     for (const auto& i: row) {
    //         std::cout << i << ' ';
    //     }
    //     std::cout << "\n";
    // }
    GrayscaleImage gray(data);
    PathImage path(gray, data);
    path.ToPpm("/home/vagrant/src/mp-mountain-paths-niconicoo0w0/example-data/ex_input_data/data_output.ppm");
}