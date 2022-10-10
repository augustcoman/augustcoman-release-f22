#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

// THESE TESTS ARE NOT GRADED AND ARE FOR YOU ONLY

TEST_CASE("Hello World", "") {
    std::string hello = "Hello World!";

    REQUIRE( hello == "Hello World!" );
}

TEST_CASE("List::reverse_small", "[weight=5]") {
  
  List<int> list;
  for(int i = 1; i < 10; i++) {
    list.insertBack(i);
  }
  list.reverse();

  REQUIRE( *(list.begin()) == 9 );
  REQUIRE( *(--list.end()) == 1);
  REQUIRE(list.size() == 9);
}

TEST_CASE("List::reverse_nth_test", "[weight=5]") {
  
  List<int> list;
  for(int i = 1; i < 7; i++) {
    list.insertBack(i);
  }
  list.reverseNth(3);

  REQUIRE( *(list.begin()) == 3 );
  REQUIRE( *(--list.end()) == 4);
  REQUIRE(list.size() == 6);

  List<int> list2;
  for(int i = 1; i < 8; i++) {
    list2.insertBack(i);
  }
  list2.reverseNth(3);

  REQUIRE( *(list2.begin()) == 3 );
  REQUIRE( *(--list2.end()) == 7);
  REQUIRE(list2.size() == 7);
}

TEST_CASE("List::merge_time", "[weight=10][part=2][valgrind]") {
  PNG im1;       im1.readFromFile("../tests/merge3.png");
  PNG im2;       im2.readFromFile("../tests/merge4.png");
  PNG expected;  expected.readFromFile("../tests/expected-merge.png");

  PNG out(1074, 1212);

  vector<HSLAPixel> v1;
  for (unsigned i = 0; i < im1.width(); i++)
      for (unsigned j = 0; j < im1.height(); j++)
          v1.push_back(im1.getPixel(i, j));
  vector<HSLAPixel> v2;
  for (unsigned i = 0; i < im2.width(); i++)
      for (unsigned j = 0; j < im2.height(); j++)
          v2.push_back(im2.getPixel(i, j));
  List<HSLAPixel> l1(v1.begin(), v1.end());
  List<HSLAPixel> l2(v2.begin(), v2.end());
  l1.mergeWith(l2);
  REQUIRE(l1.size() == 1074*1212);
  vector<HSLAPixel> merged(l1.begin(), l1.end());
  unsigned x = 0;
  for (unsigned i = 0; i < merged.size(); i++) {
      int y = i % 1212;
      out.getPixel(x, y) = merged[i];
      if (y == 1211)
          x++;
  }

  out.writeToFile("actual-merge-time.png");
  INFO("Output image `out` saved as actual-merge.png");

  //REQUIRE( out == expected );
}