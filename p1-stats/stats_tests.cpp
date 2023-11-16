/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <numeric>
#include <cmath>
using namespace std;

void test_sum_small_data_set();
void test_mean_median_min_max_data_set();
void test_small_data_set();
// Add prototypes for you test functions here.

int main() {
  test_sum_small_data_set();
  // Call your test functions here
  test_mean_median_min_max_data_set();
  test_small_data_set();
  return 0;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

void test_mean_median_min_max_data_set() {
  cout << "test_mean_median_min_max_data_set" << endl;

  vector<double>  data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(5);
  data.push_back(9);
  data.push_back(1);
  data.push_back(1);
  data.push_back(2);
  data.push_back(6);
  cout << median(data);
  cout << max(data);
  cout << percentile(data, 75);
  assert(mean(data) == 3.375);
  assert(median(data) == 2);
  assert(min(data) == 1);
  assert(max(data) == 9);
  assert(percentile(data, 25) == 1);
  assert(percentile(data, 75) == 5.25);
  assert(sum(data) == 27);
  cout << "PASS!" << endl;
}

void test_small_data_set() {
  cout << "test_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);

  assert(median(data) == 1);
  assert(min(data) == 1);
  assert(max(data) == 1);
  assert(percentile(data, 40) == 1);

  cout << "PASS!" << endl;
}
// Add the test function implementations here.