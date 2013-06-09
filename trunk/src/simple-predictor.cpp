#include <iostream>
#include <stdlib.h>
#include "memory.h"
using namespace std;

int main(int argc, char* argv[]) {
  int num_predictions = 100;
  int context_length = 100;
  int smoothing = 2;
  if (argc >= 2) num_predictions = atoi(argv[1]);
  if (argc >= 3) context_length = atoi(argv[2]);
  if (argc >= 4) smoothing = atoi(argv[3]);
  Memory mem(context_length, smoothing);
  double val;
  while(cin >> val) {
    mem.Perceive(val);
  }
  for (int i = 0; i < num_predictions; ++i) {
    cout << mem.Predict() << endl;
  }
}
