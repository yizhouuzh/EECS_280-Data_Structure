// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include <cassert>
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
using namespace std;
vector<vector<double> > summarize(vector<double> v) {
  vector<vector<double> > summ;
  vector<double> s;
  double cc = 0;
  int n = v.size();
  for (int a = 1; a < n; a++) {
    if (v[a] == v[a-1]) {
        cc++;
    } else {
        vector<double> s {v[a-1], cc};
        summ.push_back(s);
        cc = 1;
    }
  }
  if (cc != 0) {
    s.push_back(v[n-1]);
    s.push_back(cc);
    summ.push_back(s);
  }
  if (v[0]==summ[0][0]) {
    summ[0][1] += 1;
  } else {
    vector<double> s{};
    s.push_back(v[0]);
    s.push_back(1);
    summ.insert(summ.begin(), s);
  }
  return summ;
}
int count(vector<double> v) {
  return v.size();
}
double sum(vector<double> v) {
  int x = std::accumulate(v.begin(), v.end(), 0);
  return x;
}
double mean(vector<double> v) {
  float mean = 0;
  int n = count(v);
  for (int i = 0; i < n; i++) {
    mean += v[i]/n;
  }
  return mean;
}
double median(vector<double> v) {
  int n = count(v);
  
  for (int j = 0; j < n-1; j++) {
    for (int k = j+1; k < n; k++) {
      if (v[j] > v[k]) {
        int a = 0;
        a = v[j];
        v[j] = v[k];
        v[k] = a;
      }
    }
  }
  if(n%2 == 0){
    return (v[n/2-1] + v[n/2])/2;
  }
  return v[(n-1)/2];
}
double mode(vector<double> v) {
  int n = count(v);
  for (int j = 0; j < n-1; j++) {
    for (int k = j+1; k < n; k++) {
      if (v[j] > v[k]) {
        int a = 0;
        a = v[j];
        v[j] = v[k];
        v[k] = a;
      }
    }
  }
  int max_count = 1;
  int count = 1;
  int re = v[0];
  for (int i = 1; i < n;i++) {
    if (v[i] == v[i-1]) {
      count++;
    } else {
      if (count > max_count) {
        max_count = count;
        re = v[i-1];
      }
      count = 1;
    }

    if (count > max_count) {
      max_count = count;
      re = v[n-1];
    }
  }
  return re;
}
double min(vector<double> v) {
  int n = count(v);
  for (int j = 0; j < n-1; j++) {
    for (int k = j+1; k < n; k++) {
      if (v[j] > v[k]) {
        int a = 0;
        a = v[j];
        v[j] = v[k];
        v[k] = a;
      }
    }
  }
  return v[0];
}
double max(vector<double> v) {
  int n = count(v);
  for (int j = 0; j < n-1; j++) {
    for (int k = j+1; k < n; k++) {
      if (v[j] > v[k]) {
        int a = 0;
        a = v[j];
        v[j] = v[k];
        v[k] = a;
      }
    }
  }
  return v[n-1];
}
double stdev(vector<double> v) {
  double m = mean(v);
  int n = count(v);
  double sd = 0;
  for (int i = 0; i < n; i++) {
    sd += pow(v[i]-m, 2)/(n-1);
  }
  return sqrt(sd);
}
double percentile(vector<double> v, double p) {
  int n = count(v);
  for (int j = 0; j < n-1; j++) {
    for (int k = j+1; k < n; k++) {
      if (v[j] > v[k]) {
        int a = 0;
        a = v[j];
        v[j] = v[k];
        v[k] = a;
      }
    }
  }
  double r = p*(n-1)/100 + 1;
  double fractpart, intpart;
  fractpart = modf (r, &intpart);
  int i = (int) intpart;
  double a = v[i-1] + fractpart*(v[i]-v[i-1]);
  return a;
}