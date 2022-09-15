#include "Image.h"
#include "StickerSheet.h"
#include "../lib/cs225/HSLAPixel.h"

void remove_alpha_gradient(Image& target) {
  for(unsigned y = 0; y < target.height(); y++) {
    for(unsigned x = 0; x < target.width(); x++) {
      if(target.getPixel(x, y).a <= 0.9) {
        target.getPixel(x, y).a = 0.0;
      }
    }
  }
}

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image engineering_quad;
  engineering_quad.readFromFile("../engineering_quad.png");

  Image obamium;
  Image soyjack_l;
  Image soyjack_r;
  Image boss_health;
  Image hud_bar;
  obamium.readFromFile("../obamium_smaller.png");
  soyjack_l.readFromFile("../soyjack_l.png");
  soyjack_r.readFromFile("../soyjack_r.png");
  boss_health.readFromFile("../boss_health_clear_resized.png");
  hud_bar.readFromFile("../hud_display_smaller.png");

  obamium.darken(0.1);
  remove_alpha_gradient(obamium);
  remove_alpha_gradient(soyjack_l);
  remove_alpha_gradient(soyjack_r);
  remove_alpha_gradient(boss_health);

  soyjack_l.scale(0.8);
  soyjack_r.scale(0.8);

  StickerSheet meme(engineering_quad, 5);
  meme.addSticker(obamium, 265, 110);
  meme.addSticker(soyjack_l, 0, 146);
  meme.addSticker(soyjack_r, 727, 146);
  meme.addSticker(boss_health, 166, 0);
  meme.addSticker(hud_bar, 238, 545);

  meme.render().writeToFile("../myImage.png");
  //


  return 0;
}

/* Old code used to clear boss_health:

Image boss_health;
  boss_health.readFromFile("../boss_health_a.png");
  cs225::HSLAPixel color = boss_health.getPixel(0, 0);
  for(unsigned y = 0; y < boss_health.height(); y++) {
    for(unsigned x = 0; x < boss_health.width(); x++) {
      if(boss_health.getPixel(x, y) == color) {
        boss_health.getPixel(x, y).a = 0.0;
      }
    }
  }
  boss_health.writeToFile("../boss_health_clear.png");

*/

/*
old locations:
  meme.addSticker(soyjack_l, 0, 11);
  meme.addSticker(soyjack_r, 652, 11);
*/