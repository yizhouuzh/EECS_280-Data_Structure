// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <vector>
using namespace std;
int main() {
    string file, col;
    cout << "enter a filename" << "\n";
    cin >> file;
    cout << "enter a column name" << "\n"; 
    cin >> col;
    cout << "reading column " << col << " from " << file  << "\n";
    vector<double> column = extract_column(file, col);
    int n = count(column);
    for (int j = 0; j < n-1; j++) {
        for (int k = j+1; k < n; k++) {
            if (column[j] > column[k]) {
                int a = 0;
                a = column[j];
                column[j] = column[k];
                column[k] = a;
            }
        }
    }
  cout << "Summary (value: frequency)" << "\n";
  vector<vector<double> > summ = summarize(column);
  int m = summ.size();
  for (int f = 0; f < m; f++) {
    cout << summ[f][0] << ": " << summ[f][1] << "\n";
  }
  cout << "\n";
  cout << "count = " << count(column) << "\n";
  cout << "sum = " << sum(column) << "\n";
  cout << "mean = " << mean(column) << "\n";
  cout << "stdev = " << stdev(column) << "\n";
  cout << "median = " << median(column) << "\n";
  cout << "mode = " << mode(column) << "\n";
  cout << "min = " << min(column) << "\n";
  cout << "max = " << max(column) << "\n";
  cout << "  0th percentile = " << min(column) << "\n";
  cout << " 25th percentile = " << percentile(column, 25) << "\n";
  cout << " 50th percentile = " << percentile(column, 50) << "\n";
  cout << " 75th percentile = " << percentile(column, 75) << "\n";
  cout << "100th percentile = " << max(column) << "\n";
}