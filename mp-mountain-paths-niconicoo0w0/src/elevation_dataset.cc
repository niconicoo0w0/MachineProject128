#include "elevation_dataset.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// void printVector(std::vector<std::vector<int> > &v)
// {
//     std::vector<std::vector<int> >::iterator iter;
//     for (iter = v.begin(); iter != v.end() ; ++iter) {
//         for (size_t i = 0; i < (*iter).size(); ++i) {
//             std::cout << (*iter)[i] << " ";
//         }
//         std::cout << std::endl;
//     }
// }

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height): width_(width), height_(height) {
  std::ifstream file{filename};
  if (!file.is_open()) { throw std::runtime_error("What are u doing, howdy?🤠"); }
  std::vector<int> temp;
  size_t count = 0;
  for (std::string line; std::getline(file, line); line = "") {
    line += " ";std::string word;
    for (size_t col = 0; col < line.length(); col++) {
      if (line[col] != ' ' && line[col] != '\n' && line[col] != '\r' && line[col] != '\t') {
        word += line[col];
      } else if (word.length() != 0) {
        if (std::stoi(word) > max_ele_ || count == 0) { max_ele_ = std::stoi(word);}
        if (std::stoi(word) < min_ele_ || count == 0) { min_ele_ = std::stoi(word);}
        temp.push_back(std::stoi(word));
        count++;
        word.clear();
        if (count % width_ == 0) {
          data_.push_back(temp);
          temp.clear();
        }
      } else {
        word.clear();
        continue;
      }
    }
  }
  if (count != width_ * height_ || data_.size() != height_ || data_[0].size() != width_) {
    throw std::runtime_error(std::to_string(width_));
  }
}

size_t ElevationDataset::Width() const {
    return width_;
}
size_t ElevationDataset::Height() const {
    return height_;
}
int ElevationDataset::MaxEle() const {
    return max_ele_;
}
int ElevationDataset::MinEle() const {
    return min_ele_;
}
int ElevationDataset::DatumAt(size_t row, size_t col) const {
    return data_[row][col];
}
const std::vector<std::vector<int> >& ElevationDataset::GetData() const {
    return data_;
}