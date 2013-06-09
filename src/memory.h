#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

class Memory {
 public:
  Memory(int context_length, int smoothing);
  ~Memory();
  void Perceive(double val);
  double Predict();

 private:
  std::vector<double> history_;
  std::vector<double> smoothed_;
  unsigned int smoothing_;
  unsigned int context_length_;
  double partial_;
  double last_prediction_;
  unsigned long long prediction_pos_;
  unsigned long long best_match_;
  bool prediction_made_;
};

#endif
