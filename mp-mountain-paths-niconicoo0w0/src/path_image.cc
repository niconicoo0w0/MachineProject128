#include "path_image.hpp"
#include "grayscale_image.hpp"
#include "elevation_dataset.hpp"
#include "path.hpp"
#include <vector>
#include <string>
#include "color.hpp"
#include <iostream>
#include <fstream>



int up_ele = 0;
int down_ele = 0;
int forward_ele = 0;

const int kMax = 2147483647;
const int kOner= 252;
const int kTwor= 25;
const int kThreer= 63;
const int kOneg= 31;
const int kTwog= 253;
const int kThreeg= 13;

Color red = Color(kOner, kTwor, kThreer);
// Color green = Color(kOneg, kTwog, kThreeg);

int PathImage::Compare(unsigned int forward_ele, unsigned int up_ele, unsigned int down_ele, Path &path) {
    int returnit = 0;
    unsigned int temp = forward_ele;
    if (down_ele < temp) { 
        returnit = 1;
        temp = down_ele;
    }
    if (up_ele < temp) { 
       returnit = -1;
       temp = up_ele;
    }
    path.IncEleChange(temp);
    return returnit;
}

unsigned int min = kMax;
unsigned int min_index = 0;

PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset): width_(image.Width()), height_(image.Height()) {
    path_image_ = image.GetImage();
    data_ = dataset.GetData();
    for (size_t i = 0; i < height_; i++) {
        size_t next_step = i;
        Path p(width_, i);
        p.SetLoc(0, next_step);
        path_image_[next_step][0] = red;
        for (size_t col = 0; col < width_ - 1; col++) {
            if (next_step == 0) {
                forward_ele = abs(data_[next_step][col + 1] - data_[next_step][col]);
                down_ele = abs(data_[next_step + 1][col + 1] - data_[next_step][col]);
                next_step += Compare(forward_ele, kMax, down_ele, p);
                p.SetLoc(col + 1, next_step);
                path_image_[next_step][col + 1] = red;
            } else if (next_step == height_ - 1) {
                forward_ele = abs(data_[next_step][col + 1] - data_[next_step][col]);
                up_ele = abs(data_[next_step - 1][col + 1] - data_[next_step][col]);
                next_step += Compare(forward_ele, up_ele, kMax, p);
                p.SetLoc(col + 1, next_step);
                path_image_[next_step][col + 1] = red;
            } else {
                forward_ele = abs(data_[next_step][col + 1] - data_[next_step][col]);
                up_ele = abs(data_[next_step - 1][col + 1] - data_[next_step][col]);
                down_ele = abs(data_[next_step + 1][col + 1] - data_[next_step][col]);
                next_step += Compare(forward_ele, up_ele, down_ele, p);
                p.SetLoc(col + 1, next_step);
                path_image_[next_step][col + 1] = red;
            }
        }
        paths_.push_back(p);
        if (p.EleChange() < min) {
            min = p.EleChange();
            min_index = i;
        }
    }
    std::vector<size_t> green = paths_[min_index].GetPath();
    for (size_t col = 0; col < green.size(); col++) { 
        path_image_[green[col]][col] = Color(kOneg, kTwog, kThreeg);
    }
}



size_t PathImage::Width() const {
    return width_;
}

size_t PathImage::Height() const {
    return height_;
}

unsigned int PathImage::MaxColorValue() const {
    return PathImage::kMaxColorValue;
}

const std::vector<Path>& PathImage::Paths() const {
    return paths_;
}

const std::vector<std::vector<Color> >& PathImage::GetPathImage() const {
    return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
    std::ofstream o;
    o.open(name);
    o << "P3" << std::endl;
    o << width_ << " " << height_ << std::endl;
    o << "255" << std::endl;
    for (size_t row = 0; row < height_; row++) {
        for (size_t col = 0; col < width_; col++) {
            o << path_image_[row][col].Red() << ' ' << path_image_[row][col].Green() << ' ' << path_image_[row][col].Blue();
            if (col != width_ - 1) {
                o << ' ';
            }
        }
        o << std::endl;
    }
    o.close();
}	

// #include "path_image.hpp"
// #include "grayscale_image.hpp"
// #include "elevation_dataset.hpp"
// #include "path.hpp"
// #include <vector>
// #include <string>
// #include "color.hpp"
// #include <iostream>
// #include <fstream>

// size_t up_ele = 0;
// size_t down_ele = 0;
// size_t forward_ele = 0;
// const int kOner= 252;
// const int kTwor= 25;
// const int kThreer= 63;
// const int kOneg= 31;
// const int kTwog= 253;
// const int kThreeg= 13;


// int PathImage::Compare(size_t forward_ele, size_t up_ele, size_t down_ele) {
//     if (forward_ele == down_ele && forward_ele == up_ele && up_ele == down_ele) { //三个都相等
//         return 0;
//     }
//     if (up_ele == down_ele) { //上下相等
//         return -1;
//     }
//     if (forward_ele == up_ele || forward_ele == down_ele) { //上中或者上下相等
//         return 0;
//     }
//     if (forward_ele < down_ele && forward_ele < up_ele) { 
//         return 0;
//     }
//     if (down_ele < forward_ele && down_ele < up_ele) {
//         return -1;
//     } 
//     if (up_ele < forward_ele && up_ele < down_ele) {
//         return 1;
//     }
//     return 0;
// }

// // std::vector<size_t


// size_t PathImage::GetGreenRow(const ElevationDataset &data, std::vector<std::vector<size_t>> movements) {
//     std::vector<size_t> sum;
//     size_t min = SIZE_MAX;
//     size_t min_row_num = 0;
//     for (size_t i = 0; i < movements.size(); i++) {
//         size_t temp = 0;
//         for (size_t move = 0; move < movements[0].size(); move++) {
//             temp += data.DatumAt(movements[i][move], move);
//         }
//         sum.push_back(temp);
//     }
//     for (size_t j = 0; j < sum.size(); j++) {  //sum.size()相当于path的数量，存的是每个path的总长度
//         if (sum[j] < min) {
//             min = sum[j];
//             min_row_num = j;
//         }
//     }
//     return min_row_num;
// }


// PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset) {
//     ElevationDataset data = ElevationDataset(dataset);
//     GrayscaleImage path = GrayscaleImage(image); PathImage::path_image_ = image.GetImage();
//     std::vector<size_t> start; std::vector<size_t> movement; std::vector<std::vector<size_t>> movements;
//     for (size_t i = 0; i < paths_.size(); i++) {
//         start.push_back(paths_[i].StartingRow());
//     }
//     for (size_t s = 0; s < start.size(); s++) {
//         movement.push_back(start[s]);
//         for (size_t col = 0; col < data.Width() - 1; col++) {
//             size_t next_step = start[s];
//             if (next_step == 0) {
//                 forward_ele = abs(data.DatumAt(next_step, col + 1) - data.DatumAt(next_step, col));
//                 down_ele = abs(data.DatumAt(next_step + 1, col + 1) - data.DatumAt(next_step, col));
//                 next_step += Compare(forward_ele, SIZE_MAX, down_ele);
//                 movement.push_back(next_step);
//             } else if (next_step == data.Height() - 1) {
//                 forward_ele = abs(data.DatumAt(next_step, col + 1) - data.DatumAt(next_step, col));
//                 up_ele = abs(data.DatumAt(next_step - 1, col + 1) - data.DatumAt(next_step, col));
//                 next_step += Compare(forward_ele, up_ele, SIZE_MAX);
//                 movement.push_back(next_step);
//             } else {
//                 forward_ele = abs(data.DatumAt(next_step, col + 1) - data.DatumAt(next_step, col));
//                 up_ele = abs(data.DatumAt(next_step - 1, col + 1) - data.DatumAt(next_step, col));
//                 down_ele = abs(data.DatumAt(next_step + 1, col + 1) - data.DatumAt(next_step, col));
//                 next_step += Compare(forward_ele, up_ele, down_ele);
//                 movement.push_back(next_step);
//             }
//         }
//         movements.push_back(movement); movement.clear();
//         size_t min_row_num = GetGreenRow(data, movements);
//         for (size_t row = 0; row < movements.size(); row++) {
//             for (size_t col = 0; col < movements[0].size(); col++) {
//                 path_image_[row][col] = Color(kOner, kTwor, kThreer);
//             }
//         }
//         for (size_t col = 0; col < movements[0].size(); col++) {
//             path_image_[min_row_num][col] = Color(kOneg, kTwog, kThreeg);
//         }
//     }
// }

// size_t PathImage::Width() const {
//     return width_;
// }

// size_t PathImage::Height() const {
//     return height_;
// }

// unsigned int PathImage::MaxColorValue() const {
//     return PathImage::kMaxColorValue;
// }

// const std::vector<Path>& PathImage::Paths() const {
//     return paths_;
// }

// const std::vector<std::vector<Color> >& PathImage::GetPathImage() const {
//     return path_image_;
// }

// void PathImage::ToPpm(const std::string& name) const {
//     std::ofstream o;
//     o.open(name);
//     o << "P3" << std::endl;
//     o << width_ << " " << height_ << std::endl;
//     o << "255" << std::endl;
//     for (size_t row = 0; row < height_; row++) {
//         for (size_t col = 0; col < width_; col++) {
//             o << path_image_[row][col].Red() << ' ' << path_image_[row][col].Green() << ' ' << path_image_[row][col].Blue();
//             if (height_ - 1 != 1) {
//                 o << '\n';
//             }
//         }
//         o << std::endl;
//     }
//     o.close();
// }	