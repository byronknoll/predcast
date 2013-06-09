#include <iostream>
#include <stdlib.h>
#include "brain.h"
using namespace std;

int main(int argc, char* argv[]) {
  int num_predictions = 100;
  int window_size = 50;
  int memory_size = 3;
  int context_length = 100;
  int smoothing = 2;
  if (argc >= 2) num_predictions = atoi(argv[1]);
  if (argc >= 3) window_size = atoi(argv[2]);
  if (argc >= 4) memory_size = atoi(argv[3]);
  if (argc >= 5) context_length = atoi(argv[4]);
  if (argc >= 6) smoothing = atoi(argv[5]);
  Brain brain(window_size, memory_size, context_length, smoothing);
  double val;
  while(cin >> val) {
    brain.Perceive(val);
  }
  for (int i = 0; i < num_predictions; ++i) {
    cout << brain.Predict() << endl;
  }
}
