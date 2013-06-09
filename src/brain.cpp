#include <vector>
#include <math.h>
#include <cmath>

#include "brain.h"

#define PI 3.14159265

std::vector<double> DCT(const std::vector<double>& v, int size) {
  int N = v.size();
  std::vector<double> S(size, 0);
  for (int k = 0; k < size; ++k) {
    double f = 1;
    if (k == 0) f = 1 / sqrt(2);
    double val = 0;
    for (int n = 0; n < N; ++n) {
      val += v[n] * cos(((2*n + 1) * k * PI) / (2*N));
    }
    S[k] = (2.0 / N) * f * val;
  }
  return S;
}

std::vector<double> IDCT(const std::vector<double>& v, int start, int end, int size) {
  int N = v.size();
  std::vector<double> s(end-start, 0);
  for (int n = start; n < end; ++n) {
    double val = 0;
    for (int k = 0; k < size; ++k) {
      double f = 1;
      if (k == 0) f = 1 / sqrt(2);
      double u = 1;
      if ((n / v.size()) % 2 == 1) u = -1;
      if (k % 2 == 0) u = 1;
      val += f * u * v[k] * cos(((2*n + 1) * k * PI) / (2*N));
    }
    s[n-start] = val;
  }
  return s;
}

std::vector<double> Hann(const std::vector<double>& input, int start, int end) {
  std::vector<double> v(end-start, 0);
  for (int i = 0; i < end-start; ++i) {
    v[i] = 0.5 * (1 - cos((2 * PI * i) / (end-start-1))) * input[start+i];
  }
  return v;
}

Brain::Brain(int window_size, int memory_size, int context_length, int smoothing) : window_size_(window_size), memory_size_(memory_size), predictions_(window_size_, 0), prediction_made_(false) {
  memory_ = new Memory*[memory_size_];
  for (unsigned int i = 0; i < memory_size_; ++i) {
    memory_[i] = new Memory(context_length, smoothing);
  }
}

Brain::~Brain() {
  for (unsigned int i = 0; i < memory_size_; ++i) {
    delete memory_[i];
  }
  delete[] memory_;
}

void Brain::Perceive(double val) {
  prediction_made_ = false;
  history_.push_back(val);
  if (history_.size() <= window_size_) return;
  std::vector<double> dct = DCT(Hann(history_, history_.size() - window_size_, history_.size()), memory_size_);
  for (unsigned int i = 0; i < memory_size_; ++i) {
    memory_[i]->Perceive(dct[i]);
  }
}

double Brain::Predict() {
  if (!prediction_made_) {
    prediction_made_ = true;
    for (unsigned int i = 0; i < window_size_/2 - 1; ++i) {
      for (unsigned int j = 0; j < memory_size_; ++j) {
        memory_[j]->Predict();
      }
    }
  }
  for (unsigned int i = 0; i < memory_size_; ++i) {
    predictions_[i] = memory_[i]->Predict();
  }
  std::vector<double> v = IDCT(predictions_, window_size_/2, (window_size_/2) + 1, memory_size_);
  return v[0];
}
