#ifndef SEAM_CARVER_HPP
#define SEAM_CARVER_HPP

#include "image_ppm.hpp"

class SeamCarver {
public:
//=============================================================================================
//Helper functions => Calculating Energy
  Pixel GetLeft(int row, int col) const;
  Pixel GetRight(int row, int col) const;
  Pixel GetUp(int row, int col) const;
  Pixel GetDown(int row, int col) const;
  int Square(int num) const;
  int** EnergyChart() const; //return a chart with energy vals.

//=============================================================================================
//Helper functions => For Vertical
  int** AllVertical() const;

//=============================================================================================
//Helper functions => For Horizontal
  int** AllHorizontal() const;

//=============================================================================================
  // default constructor
  //
  // Not tested, but you are welcome to intialize (or not) member variables
  // however you like in this function
  SeamCarver() = default;

//=============================================================================================
  // overloaded constructor
  //
  // sets the instances' image_ as a DEEP COPY of the image parameter. Note
  // that if ImagePPM's copy constructor is implemented correctly, you
  // shouldn't have to worry about the details of a deep copy here
  SeamCarver(const ImagePPM& image);

//=============================================================================================
  // sets the instances' image_ as a DEEP COPY of the image parameter. Same
  // note as above regarding ImagePPM
  void SetImage(const ImagePPM& image);

//=============================================================================================
  // returns the instance's image_
  const ImagePPM& GetImage() const;

//=============================================================================================
  // returns the image's height
  int GetHeight() const;
  // returns the image's width
  int GetWidth() const;
  // returns the energy of the pixel at row col in image_
  int GetEnergy(int row, int col) const;

//=============================================================================================
  // returns the horizontal seam of image_ with the least amount of
  // energy
  //
  // the ith int in the returned array corresponds to which row at
  // col i is in the seam. example:
  //
  //    | x |   |
  // ---+---+---+---
  //  x |   | x |
  // ---+---+---+---
  //    |   |   | x
  // returns {1, 0, 1, 2}
  int* GetHorizontalSeam() const;

  // returns the vertical seam of image_ with the least amount of
  // energy
  //
  // the ith int in the returned array corresponds to which col at
  // row i is in the seam. example:
  //
  //    | x |   |
  // ---+---+---+---
  //    |   | x |
  // ---+---+---+---
  //    |   | x |
  // returns {1, 2, 2}
  int* GetVerticalSeam() const;

  // removes one horizontal seam in image_. example:
  //
  // image_ before:
  //  0 | 1 | 2 | 3
  // ---+---+---+---
  //  4 | 5 | 6 | 7
  // ---+---+---+---
  //  8 | 9 | 10| 11
  //
  // seam to remove:
  //    | x |   |
  // ---+---+---+---
  //  x |   | x |
  // ---+---+---+---
  //    |   |   | x
  //
  // image_ after:
  //  0 | 5 | 2 | 3
  // ---+---+---+---
  //  8 | 9 | 10| 7

  //=============================================================================================
  void RemoveHorizontalSeam();

  void RemoveVerticalSeam();

  /**
   * Add any helper methods you may need
   */

private:
  ImagePPM image_;
  int height_ = 0;
  int width_ = 0;


  /**
   * Add any helper methods you may need
   */
};
//=============================================================================================

#endif