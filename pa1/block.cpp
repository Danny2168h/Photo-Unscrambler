#include "block.h"
#include <cmath>
#include <iostream>
 
int Block::height() const {
  return data[1].size();
}
 
int Block::width() const {
  return data.size();
}
 
void Block::render(PNG &im, int x) const {
  for (int xpos = x; xpos < (x + width()); xpos++) {
    for (int ypos = 0; ypos < height(); ypos++) {
 
      HSLAPixel* pixel = im.getPixel(xpos, ypos);
      *pixel = data[xpos - x][ypos];
    }
  }
}
 
void Block::build(PNG &im, int x, int width) {
    for (int x1 = x; x1 < width + x; x1++) {
      vector<HSLAPixel> tempArray;
      for (unsigned y1 = 0; y1 < im.height(); y1++) {
        HSLAPixel *pixel = im.getPixel(x1,y1);
        tempArray.push_back(*pixel);
      }
      data.push_back(tempArray);
    }
}
