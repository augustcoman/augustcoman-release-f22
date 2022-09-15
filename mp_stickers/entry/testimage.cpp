#include "Image.h"

#include <iostream>

int main() {
  Image alma;

  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.lighten(0.2);
  alma.writeToFile("../lighten.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.saturate(0.2);
  alma.writeToFile("../saturate.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.scale(0.5);
  alma.writeToFile("../scale2x.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.scale(1800, 1800);
  alma.writeToFile("../scale2x_again.png");

  std::cout << "Using Image::rotateColor to create `rotated.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.rotateColor(630);
  alma.writeToFile("../rotated2.png");

  std::cout << "Using Image::illinify to create `illinify.png`..." << std::endl;
  alma.readFromFile("../alma.png");
  alma.illinify();
  alma.writeToFile("../illinified.png");

  Image tester;

  std::cout << "experimenting my photos..." << std::endl;
  tester.readFromFile("../photo_me_test.png");
  tester.rotateColor(180);
  tester.writeToFile("../me_tinted.png");
  tester.readFromFile("../photo_me_test.png");
  tester.illinify();
  tester.writeToFile("../me_infected.png");

  std::cout << std::abs(-34.4) << std::endl;

  return 0;
}
