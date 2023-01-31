#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>
#include <string>
#include <iostream>
#include "color.hpp"
#include "path.hpp"
#include "grayscale_image.hpp" 
#include "elevation_dataset.hpp"

class PathImage {
public:
  int Compare(unsigned int forward_ele, unsigned int up_ele, unsigned int down_ele, Path &path); //helper function
  // size_t GetGreenRow(const ElevationDataset &data, std::vector<std::vector<size_t>> movements);
  
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color> >& GetPathImage() const;
  void ToPpm(const std::string& name) const;

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  std::vector<std::vector<int>> data_;
};

#endif

// #ifndef PATH_IMAGE_H
// #define PATH_IMAGE_H

// #include <cstdlib>  // for size_t
// #include <vector>
// #include <string>
// #include <iostream>
// #include "color.hpp"
// #include "path.hpp"
// #include "grayscale_image.hpp" 
// #include "elevation_dataset.hpp"

// class PathImage {
// public:
//   int Compare(size_t forward_ele, size_t up_ele, size_t down_ele); //helper function
//   size_t GetGreenRow(const ElevationDataset &data, std::vector<std::vector<size_t>> movements);
//   PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
//   size_t Width() const;
//   size_t Height() const;
//   unsigned int MaxColorValue() const;
//   const std::vector<Path>& Paths() const;
//   const std::vector<std::vector<Color> >& GetPathImage() const;
//   void ToPpm(const std::string& name) const;

// private:
//   std::vector<Path> paths_;
//   size_t width_ = 0;
//   size_t height_ = 0;
//   std::vector<std::vector<Color>> path_image_;
//   static const int kMaxColorValue = 255;
// };

// #endif