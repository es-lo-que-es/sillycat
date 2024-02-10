#ifndef SILLYCAT_SPRITE
#define SILLYCAT_SPRITE

#include <SDL2/SDL.h>


class Sprite {
   
 public:
   void render(SDL_Rect * dest);
   Sprite(SDL_Texture * texture, int period, int frame_width);

 private:
   void reset();
   void next_frame();

   SDL_Texture * mtexture;
   SDL_Rect mrect;

   int mframes;
   int mframe = 0;

   int mperiod;
   int mtick;
};


#endif
