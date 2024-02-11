#ifndef SILLYCAT_SOUND_PACK_HEADER
#define SILLYCAT_SOUND_PACK_HEADER

#include "sound.hpp"


enum class SoundName { Gain, Death, Count };


class SoundPack {

 public:
   void init(SDL_AudioSpec specs);
   Sound operator [] (SoundName name) const;

 private:
   std::vector<AudioBuffer> msounds;

};


#endif
