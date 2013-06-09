#include <stdio.h>
#include <math.h>

#include "memory.h"

double Mean(const std::vector<double>& x, long long start, long long end) {
  double val = 0;
  for (unsigned int i = start; i < end; ++i) {
    val += x[i];
  }
  return val / (end - start);
}

double Var(const std::vector<double>& x, double x_m, long long start, long long end) {
  double val = 0;
  for (unsigned int i = start; i < end; ++i) {
    val += (x[i] - x_m) * (x[i] - x_m);
  }
  return val / (end - start);
}

double StdDev(const std::vector<double>& x, double x_m, long long start, long long end) {
  return sqrt(Var(x, x_m, start, end));
}

double CC(const std::vector<double>& data, double x_m, double y_m, int lag, long long start, long long end) {
  double val = 0;
  for (unsigned int index1 = start; index1 < end; ++index1) {
    int index2 = index1 + lag - start;
    val += (data[index1] - y_m) * (data[index2] - x_m);
  }
  return val / (end - start);
}

double NCC(const std::vector<double>& data, double x_m, double x_std, double y_m, double y_std, int lag, long long start, long long end) {
  return CC(data, x_m, y_m, lag, start, end) / (x_std * y_std);
}

std::vector<double> LeastSquares(const std::vector<double>& data, long long start, long long end) {
  double y_m = Mean(data, start, end);
  double x_m = (start+end-1) / 2.0;
  double var_x = 0;
  for (unsigned int i = start; i < end; ++i) {
    var_x += (i - x_m) * (i - x_m);
  }
  var_x /= (end - start);
  double cov = 0;
  for (unsigned int i = start; i < end; ++i) {
    cov += (i - x_m) * (data[i] - y_m);
  }
  cov /= (end - start);
  std::vector<double> vars;
  vars.push_back(cov / var_x);
  vars.push_back(y_m - (vars[0] * x_m));
  return vars;
}

Memory::Memory(int context_length, int smoothing) : smoothing_(smoothing), context_length_(context_length), partial_(0), last_prediction_(0), prediction_pos_(0), best_match_(0), prediction_made_(false) {}

Memory::~Memory() {}

void Memory::Perceive(double val) {
  history_.push_back(val);
  prediction_made_ = false;
  partial_ += val;
  if (history_.size() % smoothing_ == 0) {
    partial_ /= smoothing_;
    smoothed_.push_back(partial_);
    partial_ = 0;
  }
}

double Memory::Predict() {
  if (history_.size() == 0) return 0;
  else if (history_.size() == 1) return history_[0];

  double offset = 0;
  if (!prediction_made_) {
    prediction_made_ = true;
    unsigned int context = context_length_;
    std::vector<double>& data = smoothed_;
    int smoothing = smoothing_;
    if (context > smoothed_.size() / 2) {
      data = history_;
      context = history_.size() / 2;
      if (context > context_length_) context = context_length_;
      smoothing = 1;
    }
    if (context > 2) {
      long long end = data.size();
      long long context_start = end - context;

      double y_m = Mean(data, context_start, end);
      double y_std = StdDev(data, y_m, context_start, end);

      double best_ncc = -1;
      long long best_time = -1;
      for (long long i = 0; i < end - 2 * context; ++i) {
        double x_m = Mean(data, i, i + context);
        double x_std = StdDev(data, x_m, i, i + context);
        double ncc = NCC(data, x_m, x_std, y_m, y_std, i, context_start, end);
        if (ncc > best_ncc) {
          best_ncc = ncc;
          best_time = i;
        }
      }
      best_match_ = smoothing * (best_time + context) + (history_.size() % smoothing);
      prediction_pos_ = best_match_;
      std::vector<double> vars = LeastSquares(history_, 0, history_.size());
      double p1 = vars[1] + vars[0] * prediction_pos_;
      double p2 = vars[1] + vars[0] * history_.size();
      offset = p2 - p1;
    } else {
      best_match_ = 1;
      prediction_pos_ = 1;
      offset = history_[history_.size() - 1] - history_[0];
    }
  } else {
    ++prediction_pos_;
    if (prediction_pos_ == history_.size()) {
      prediction_pos_ = best_match_;
    }
    offset = last_prediction_ - history_[prediction_pos_ - 1];
  }
  last_prediction_ = history_[prediction_pos_] + offset;
  return last_prediction_;
}
