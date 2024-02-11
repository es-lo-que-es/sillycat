#ifndef SILLYCAT_TEXTURE_PACK_HEADER
#define SILLYCAT_TEXTURE_PACK_HEADER

#include <vector>
#include <SDL2/SDL.h>


enum class TextureName { Cat, Sound, RedX, Count };


class TexturePack {

 public:
   SDL_Texture * operator [] (TextureName name);
   ~TexturePack();
   void init();

 private:
   std::vector<SDL_Texture*> textures;
   void release_textures();

};


#endif
