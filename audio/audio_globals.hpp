#ifndef SILLYCAT_AUDIO_GLOBALS_HEADER
#define SILLYCAT_AUDIO_GLOBALS_HEADER

#include "audio/sound.hpp"
#include "audio/sound_pack.hpp"
#include <SDL2/SDL.h>
#include <list>
#include <vector>


class AudioGlobals {

 public:
   void mix_in_sounds(uint8_t * stream, int len);  

   void play_sound(SoundName name);
   SDL_AudioSpec specs() const;

   void switch_mute();

   ~AudioGlobals();
   AudioGlobals();

 private:
   std::vector<Sound> themes;
   std::list<Sound> msounds;

   SoundPack msound_pack;
   SDL_AudioSpec mspecs;

   bool mmuted = false;

};


#endif
