#include "sound_pack.hpp"
#include <stdexcept>


const char * SOUND_NAMES[] = { "sounds/gain.wav", "sounds/loss.wav", "sounds/death.wav" };


void SoundPack::init(SDL_AudioSpec specs)
{
   for ( int i = 0; i < (int)SoundName::Count; ++i ) 
      msounds.emplace_back(AudioBuffer(SOUND_NAMES[i], specs));
}


Sound SoundPack::operator [] (SoundName name) const
{
   int index = (int) name;
   if ( index < 0 || index >= (int)SoundName::Count ) throw std::runtime_error("sound_pack: out of bounds access");
   return Sound(&msounds[index]);
}
