
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG base;      base.readFromFile("../maze_base_2.png");
  PNG layer_1;   layer_1.readFromFile("../maze_layer_1.png");
  PNG layer_2;   layer_2.readFromFile("../maze_layer_2.png");
  PNG evil_woody; evil_woody.readFromFile("../evil_woody.png");
  
  FloodFilledImage image(base);
  BFS maze_solver(layer_1, Point(404, 94), 0.05);
  RainbowColorPicker rainbow(0.05);
  image.addFloodFill( maze_solver, rainbow );

  DFS laughing(layer_2, Point(0, 0), 0.05);
  MyColorPicker woody(evil_woody);
  image.addFloodFill(laughing, woody);

  Animation animation = image.animate(15000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill2.gif");

  return 0;
}
