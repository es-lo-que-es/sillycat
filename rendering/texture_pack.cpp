#include "texture_pack.hpp"
#include "util.hpp"
#include <cstdio>
#include <stdexcept>


const char * TextureNameStrings[] = { "pics/cat.png", "pics/sound.png", "pics/redx.png" };


TexturePack::~TexturePack()
{
   for ( SDL_Texture * t : textures ) if ( t ) SDL_DestroyTexture(t);
}


void TexturePack::init()
{
   for ( int i = 0; i < (int)TextureName::Count; ++i ) textures.push_back(load_png_texture(TextureNameStrings[i]));
}


SDL_Texture * TexturePack::operator [] (TextureName name)
{
   int index = (int)name;
   if ( index < 0 || index >= (int)TextureName::Count ) throw std::runtime_error("out of bounds texture-pack access");
   return textures[index];
}
