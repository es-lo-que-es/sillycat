#include "texture_pack.hpp"
#include "util.hpp"
#include <cstdio>
#include <exception>


const int TextureCount = 1;
const char * TextureNameStrings[] = { "pics/cat.png" };


TexturePack::~TexturePack()
{
   for ( SDL_Texture * t : textures ) if ( t ) SDL_DestroyTexture(t);
}


void TexturePack::init()
{
   for ( int i = 0; i < TextureCount; ++i ) textures.push_back(load_png_texture(TextureNameStrings[i]));
}


SDL_Texture * TexturePack::operator [] (TextureName name)
{
   return textures[name];
}
