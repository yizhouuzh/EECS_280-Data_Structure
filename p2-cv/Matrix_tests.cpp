// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

TEST(test_basic) {
  Matrix *mat = new Matrix;
  const int width = 3;
  const int height = 5;
  Matrix_init(mat, 3, 5);
  ASSERT_EQUAL(width, Matrix_width(mat));
  ASSERT_EQUAL(height, Matrix_height(mat));
  Matrix_fill(mat, 0);

  int *ptr = Matrix_at(mat, 2, 1);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 1);
  ASSERT_EQUAL(*ptr, 0);
  *ptr = 42;

  const int *cptr = Matrix_at(mat, 2, 1);
  ASSERT_EQUAL(*cptr, 42);

  Matrix_fill_border(mat, 9);
  ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 9);

  ASSERT_EQUAL(Matrix_max(mat), 42);
  int *ptr1 = Matrix_at(mat, 2, 2);
  *ptr1 = 59;
  ASSERT_EQUAL(Matrix_max(mat), 59);
  const int *ccptr = Matrix_at(mat, 1, 1);
  ASSERT_EQUAL(*ccptr, 0);
  Matrix_fill_border(mat, -1);
  const int *cccptr = Matrix_at(mat, 0, 1);
  ASSERT_EQUAL(*cccptr, -1);
  const int *ccccptr = Matrix_at(mat, 4, 2);
  ASSERT_EQUAL(*ccccptr, -1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 2), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 3, 0, 2), -1);
  delete mat;

}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 1);

  *Matrix_at(mat, 0, 0) = 42;
  *Matrix_at(mat, 0, 1) = 20;
  ostringstream expected;
  expected << "2 1\n"
           << "42 20 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
