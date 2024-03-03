#pragma once
#include <vector>

class HeatMap {
public:
  HeatMap(unsigned int x, unsigned int y);

  void print();

private:
  /** Performs a convolution on the heatmap, smoothing out hotspots. */
  void smoothen_();

  /** The heatmap grid containing values from 0.0 (lowest terrain) to 1.0
   * (highest terrain)*/
  std::vector<std::vector<float>> heatmap_;
  unsigned int width_;
  unsigned int height_;
};
