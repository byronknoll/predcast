#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cout << "Wrong number of arguments." << endl;
    return -1;
  }
  ifstream f1(argv[1]);
  vector<double> data1;
  double val;
  while (f1 >> val) {
    data1.push_back(val);
  }
  f1.close();
  ifstream f2(argv[2]);
  vector<double> data2;
  while (f2 >> val) {
    data2.push_back(val);
  }
  f2.close();
  if (data1.size() != data2.size()) {
    cout << "Input sizes do not match: " << data1.size() << " vs " << data2.size() << endl;
    return -1;
  }
  double rmse = 0;
  for (unsigned int i = 0; i < data1.size(); ++i) {
    rmse += (data1[i] - data2[i]) * (data1[i] - data2[i]);
  }
  rmse /= data1.size();
  rmse = sqrt(rmse);
  cout << rmse << endl;
}
