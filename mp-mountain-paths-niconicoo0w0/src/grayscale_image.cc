#include "grayscale_image.hpp"
#include "color.hpp"
#include <fstream>
#include <string>
#include <cmath>
#include "color.hpp"
#include <iostream>

//shade_of_gray = std::round((elevation_point - min_ele) / (max_ele - min_ele) * 255)

const int kMultiply = 255;

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
    std::vector<Color> image;
    int shade_of_gray = 0;
    for (size_t row = 0; row < dataset.Height(); row++) {
        for (size_t col = 0; col < dataset.Width(); col++) {
            if (dataset.MaxEle() == dataset.MinEle()) {
                image.push_back(Color(0, 0, 0));
            } else {
                shade_of_gray = std::round(((double)dataset.DatumAt(row, col) - (double)dataset.MinEle()) /
                ((double)dataset.MaxEle() - (double)dataset.MinEle()) * kMultiply);
                image.push_back(Color((int)shade_of_gray, (int)shade_of_gray, (int)shade_of_gray));
            }
        }
        image_.push_back(image);
        image.clear();
    }
    height_ = dataset.Height();
    width_ = dataset.Width();
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) {
    ElevationDataset dataset = ElevationDataset(filename, width, height);
    std::vector<Color> image;
    int shade_of_gray = 0;
    for (size_t row = 0; row < dataset.Height(); row++) {
        for (size_t col = 0; col < dataset.Width(); col++) {
            if (dataset.MaxEle() == dataset.MinEle()) {
                image.push_back(Color(0, 0, 0));
            } else {
                shade_of_gray = std::round(((double)dataset.DatumAt(row, col) - (double)dataset.MinEle()) /
                ((double)dataset.MaxEle() - (double)dataset.MinEle()) * kMultiply);
                image.push_back(Color((int)shade_of_gray, (int)shade_of_gray, (int)shade_of_gray));
            }
        }
        image_.push_back(image);
        image.clear();
    }
    height_ = dataset.Height();
    width_ = dataset.Width();
}

size_t GrayscaleImage::Width() const {
    return width_;
}
size_t GrayscaleImage::Height() const {
    return height_;
}
unsigned int GrayscaleImage::MaxColorValue() const {
    return kMaxColorValue;
}
const Color& GrayscaleImage::ColorAt(int row, int col) const {
    return image_[row][col];
}
const std::vector<std::vector<Color> >& GrayscaleImage::GetImage() const {
    return image_;
}
void GrayscaleImage::ToPpm(const std::string& name) const {
    std::ofstream o;
    o.open(name, std::ios::out);
    o << "P3" << std::endl;
    o << width_ << ' ' << height_ << std::endl;
    o << GrayscaleImage::kMaxColorValue << std::endl;
    for (size_t row = 0; row < height_; row++) {
        for (size_t col = 0; col < width_; col++) {
            o << image_[row][col].Red() << ' ' << image_[row][col].Green() << ' ' << image_[row][col].Blue() << ' ';
            if (col != width_ - 1) {
                o << ' ';
            }
        }
        o << std::endl;
    }
    o.close();
}