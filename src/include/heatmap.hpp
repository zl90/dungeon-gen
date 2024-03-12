#pragma once
#include "structure.hpp"
#include <vector>

class HeatMap {
public:
  HeatMap(const unsigned int x, const unsigned int y);

  HeatMap(const unsigned int x, const unsigned int y, StructureType structure);

  HeatMap(const unsigned int x, const unsigned int y, StructureType structure,
          int hotspot_percentage);

  void print();

  std::vector<float> &operator[](int i) { return heatmap_[i]; };

private:
  /** Randomly inserts hotspots into the heatmap. A hotspot is defined as a grid
   * cell which contains a value equal to `highest_depth_` */
  void insert_hotspots_();
  /** Randomly inserts hotspots into the heatmap. A hotspot is defined as a grid
     * cell which contains a value equal to `highest_depth_`.
     @param `hotspot_percentage`, used to determine the frequency of hotspots.
   */
  void insert_hotspots_(int hotspot_percentage);

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
  const int max_hotspot_percentage_ = 4;
};
