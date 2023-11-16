// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};
  Pixel blue = {0, 0, 255};
  Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0,0), red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,0,1), green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 0), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 1), white));
  Image_fill(img, blue);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,0,1), blue));
  ASSERT_EQUAL(Image_height(img), 2);
  ASSERT_EQUAL(Image_width(img), 2);
  delete img; // delete the Image
}

TEST(test_print_basic_3) {
  Image *img = new Image; // create an Image in dynamic memory

  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};
  Pixel blue = {0, 0, 255};
  Pixel white = {255, 255, 255};
  Pixel newc = {250, 20, 155};

  Image_init(img, 3, 3);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
  Image_set_pixel(img, 0, 2, red);
  Image_set_pixel(img, 1, 2, green);
  Image_set_pixel(img, 2, 0, blue);
  Image_set_pixel(img, 2, 1, white);
  Image_set_pixel(img, 2, 2, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0,2), red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,1,2), green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 0), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 2), white));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0,1), green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,1,1), white));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 1), white));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), red));
  Image_fill(img, blue);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0,2), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,1,2), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 0), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 2), blue));
  Image_fill(img, newc);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0,2), newc));
  ASSERT_EQUAL(Image_height(img), 3);
  ASSERT_EQUAL(Image_width(img), 3);
  delete img; // delete the Image
}

TEST(test_print_basic_4) {
  Image *img = new Image; // create an Image in dynamic memory

  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};
  Pixel blue = {0, 0, 255};
  Pixel white = {255, 255, 255};
  Pixel newc = {250, 20, 155};

  Image_init(img, 1, 4);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 1, 0, green);
  Image_set_pixel(img, 2, 0, blue);
  Image_set_pixel(img, 3, 0, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);
  ASSERT_EQUAL(Image_height(img), 4);
  ASSERT_EQUAL(Image_width(img), 1);
  // Correct output
  ostringstream correct;
  correct << "P3\n1 4\n255\n";
  correct << "255 0 0 \n";
  correct << "0 255 0 \n";
  correct << "0 0 255 \n";
  correct << "255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0,0), red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,1, 0), green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 0), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 3, 0), white));
  Image_fill(img, blue);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 0), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 0), blue));
  Image_fill(img, newc);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 0), newc));
  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
