#pragma once
#include <vector>

class HeatMap {
public:
  HeatMap(unsigned int x, unsigned int y);

  void print();

private:
  /** Randomly inserts hotspots into the heatmap. A hotspot is defined as a grid
   * cell which contains a value equal to `highest_depth_` */
  void insert_hotspots_();

  /** Performs a discrete 2D convolution on the heatmap, smoothing out hotspots.
   */
  void smoothen_();

  /** The heatmap grid containing values from `lowest_depth_` to
   * `highest_depth_` */
  std::vector<std::vector<float>> heatmap_;
  unsigned int width_;
  unsigned int height_;
  const float highest_depth_ = 1.0f;
  const float lowest_depth_ = 0.0f;
  const float hotspot_percentage_ = 3.0f;
};
