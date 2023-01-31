#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here

// given functions below, DO NOT MODIFY

const int kMax = 2147483647;

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
  // returns the instance's image_
const ImagePPM& SeamCarver::GetImage() const {
  return image_;
}
  // returns the image's height
int SeamCarver::GetHeight() const {
  return height_;
}
  // returns the image's width
int SeamCarver::GetWidth() const {
  return width_;
}

Pixel SeamCarver::GetLeft(int row, int col) const {
  if (col == 0) {
    return image_.GetPixel(row, width_ - 1);
  }
  return image_.GetPixel(row, col - 1);
}

Pixel SeamCarver::GetRight(int row, int col) const {
  if (col == width_ - 1) { //the last column of the row
    return image_.GetPixel(row, 0);
  }
  return image_.GetPixel(row, col + 1); 
}

Pixel SeamCarver::GetUp(int row, int col) const {
  if (row == 0) {
    return image_.GetPixel(height_ - 1, col);
  }
  return image_.GetPixel(row - 1, col);
}

Pixel SeamCarver::GetDown(int row, int col) const {
  if (row == height_ - 1) {
    return image_.GetPixel(0, col);
  }
  return image_.GetPixel(row + 1, col);
}

int SeamCarver::Square(int num) const {
  int num_square = num * num;
  return num_square;
}

int SeamCarver::GetEnergy(int row, int col) const {
  int horizontal_red = GetRight(row, col).GetRed() - GetLeft(row, col).GetRed();
  int horizontal_blue = GetRight(row, col).GetBlue() - GetLeft(row, col).GetBlue();
  int horizontal_green = GetRight(row, col).GetGreen() - GetLeft(row, col).GetGreen();
  int vertical_red = GetUp(row, col).GetRed() - GetDown(row, col).GetRed();
  int vertical_blue = GetUp(row, col).GetBlue() - GetDown(row, col).GetBlue();
  int vertical_green = GetUp(row, col).GetGreen() - GetDown(row, col).GetGreen();
  int returnit = Square(horizontal_red) + Square(horizontal_blue) + Square(horizontal_green) + Square(vertical_red) + Square(vertical_blue) + Square(vertical_green);
  return returnit;
}

int** SeamCarver::EnergyChart() const {
  int** arr = new int*[height_];
  for (int i = 0; i < height_; i++) {
    arr[i] = new int[width_];
  }
  for (int row = 0; row < height_; row++) {
    for (int col = 0; col < width_; col++) {
      arr[row][col] = GetEnergy(row, col);
    }
  }
  return arr;
}

int** SeamCarver::AllHorizontal() const {
  int** arr = EnergyChart();
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < height_; row++) { 
      if (row == 0) {                                 // => 🤠 when the row == 0 => only compare with down & middle
        int down = arr[1][col + 1];
        int middle = arr[0][col + 1];
        if (down < middle) {
          arr[0][col] += down;
        } else {
          arr[0][col] += middle;
        }
      } else if (row != 0 && row != height_ - 1) {     // => 🤠 middle :) 正常情况
        int up = arr[row - 1][col + 1];
        int middle = arr[row][col + 1];
        int down = arr[row + 1][col + 1];
        if (up <= middle && up <= down) {
          arr[row][col] += up;
        } else if (middle < up && middle <= down) {
          arr[row][col] += middle;
        } else {
          arr[row][col] += down;
        }
      } else {                                       // => 🤠 when the row == height_ - 1 => only compare with up & middle
        int up = arr[height_ - 2][col + 1];
        int middle = arr[height_ - 1][col + 1];
        if (up <= middle) {
          arr[row][col] += up;
        } else {
          arr[row][col] += middle;
        }
      }
    }
  }
  return arr;
}

int** SeamCarver::AllVertical() const {
  int** arr = EnergyChart();
  for (int row = height_ - 2; row >= 0; row--) {
    for (int col = 0; col < width_; col++) { 
      if (col == 0) {                                 // => 🤠 when the column == 0 => only compare with middle & right
        int right = arr[row + 1][1];
        int middle = arr[row + 1][0];
        if (right < middle) {
          arr[row][0] += right;
        } else {
          arr[row][0] += middle;
        }
      } else if (col != 0 && col != width_ - 1) {     // => 🤠 middle :) 正常情况
        int left = arr[row + 1][col - 1];
        int right = arr[row + 1][col + 1];
        int middle = arr[row + 1][col];
        if (left <= right && left < middle) {
          arr[row][col] += left;
        } else if (right < left && right < middle) {
          arr[row][col] += right;
        } else {
          arr[row][col] += middle;
        }
      } else {                                       // => 🤠 when the column == width_ - 1 => only compare with left & middle
        int left = arr[row + 1][width_ - 2];
        int middle = arr[row + 1][width_ - 1];
        if (left < middle) {
          arr[row][col] += left;
        } else {
          arr[row][col] += middle;
        }
      }
    }
  }
  return arr;
}

int* SeamCarver::GetHorizontalSeam() const {
  int** arr = AllHorizontal(); int* returnit = new int[width_]; int min = kMax;
  for (int row = 0; row < height_; row++) {
    if (arr[row][0] < min) {  min = arr[row][0];  returnit[0] = row; }
  }
  for (int index = 0; index < width_ - 1; index++) {
    if (returnit[index] == 0) {
      int middle = arr[0][index + 1];
      int down = arr[1][index + 1];
      if (down < middle) {
        returnit[index + 1] = 1;
      } else {
        returnit[index + 1] = 0;
      }
    } else if (returnit[index] == height_ - 1) {
      int up = arr[returnit[index] - 1][index + 1];            //(0,1,1,1,1)
      int middle = arr[returnit[index]][index + 1];
      if (up < middle) {
        returnit[index + 1] = returnit[index] - 1;
      } else {
        returnit[index + 1] = returnit[index];
      }
    } else {
      int up = arr[returnit[index] - 1][index + 1];
      int middle = arr[returnit[index]][index + 1];
      int down = arr[returnit[index] + 1][index + 1];   //middle => up => down
      if (down < middle && down < up) {           
        returnit[index + 1] = returnit[index] + 1;
      } else if (up < middle) {
        returnit[index + 1] = returnit[index] - 1;
      } else {
        returnit[index + 1] = returnit[index];
      }
    }
  }
  for (int i = 0; i < height_; i++) {
    delete[] arr[i];
  }
  delete[] arr;
  return returnit;
}

int* SeamCarver::GetVerticalSeam() const {
  int** arr = AllVertical(); int* returnit = new int[height_];  int min = kMax;
  for (int col = 0; col < width_; col++) {
    if (arr[0][col] < min) { min = arr[0][col]; returnit[0] = col; }
  }
  for (int index = 0; index < height_ - 1; index++) {                //中 => 左 => 右
    if (returnit[index] == 0) {
      int right = arr[index + 1][1]; 
      int middle = arr[index + 1][0];
      if (right < middle) {
        returnit[index + 1] = 1;
      } else {
        returnit[index + 1] = 0;
      }
    } else if (returnit[index] == width_ - 1) {
      int left = arr[index + 1][width_ - 2]; 
      int middle = arr[index + 1][width_ - 1];
      if (left < middle) {
        returnit[index + 1] = width_ - 2;
      } else {
        returnit[index + 1] = width_ - 1;
      }
    } else {
      int left = arr[index + 1][returnit[index] - 1]; 
      int middle = arr[index + 1][returnit[index]];
      int right = arr[index + 1][returnit[index] + 1];
      if (right < middle && right < left) {
        returnit[index + 1] = returnit[index] + 1;
      } else if (left < middle) {
        returnit[index + 1] = returnit[index] - 1;
      } else {
        returnit[index + 1] = returnit[index];
      }
    }
  }
  for (int i = 0; i < height_; i++) {
    delete[] arr[i];
  }
  delete[] arr;
  return returnit;
}

void SeamCarver::RemoveHorizontalSeam() {
  auto** newpixel = new Pixel*[height_ - 1];
  for (int row = 0; row < height_ - 1; row++) {
    newpixel[row] = new Pixel[width_];
  }
  int* seam = GetHorizontalSeam(); 
  ImagePPM newimage = ImagePPM();
  newimage.SetMaxColorValue(image_.GetMaxColorValue()); 
  newimage.SetHeight(height_ - 1); 
  newimage.SetWidth(width_);
  for (int col = 0; col < width_; col++) {
    int skip = 0;
    for (int row = 0; row < height_; row++) {
      if (seam[col] == row) {
        skip += 0;
      } else {
        newpixel[skip][col] = image_.GetPixel(row, col);
        skip++;
      }
    }
  }
  delete[] seam;
  image_.~ImagePPM();
  newimage.SetPixel(newpixel);
  SetImage(newimage);
}

void SeamCarver::RemoveVerticalSeam() {
  auto** newpixel = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    newpixel[row] = new Pixel[width_ - 1];
  }
  int* seam = GetVerticalSeam(); 
  ImagePPM newimage = ImagePPM();
  newimage.SetMaxColorValue(image_.GetMaxColorValue());
  newimage.SetHeight(height_); 
  newimage.SetWidth(width_ - 1);
  for (int row = 0; row < height_; row++) {
    int skip = 0;
    for (int col = 0; col < width_; col++) {
      if (seam[row] == col) {
        skip += 0;
      } else {
        newpixel[row][skip] = image_.GetPixel(row, col);
        skip++;
      }
    }
  }
  delete[] seam;
  image_.~ImagePPM();
  newimage.SetPixel(newpixel);
  SetImage(newimage);
}