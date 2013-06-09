#ifndef BRAIN_H
#define BRAIN_H

#include "memory.h"

class Brain {
 public:
  Brain(int window_size, int memory_size, int context_length, int smoothing);
  ~Brain();
  void Perceive(double val);
  double Predict();
 private:
  unsigned int window_size_;
  unsigned int memory_size_;
  std::vector<double> history_;
  std::vector<double> predictions_;
  Memory** memory_;
  bool prediction_made_;
};

#endif
