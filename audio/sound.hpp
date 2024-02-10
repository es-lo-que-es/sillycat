#ifndef SILLYCAT_SOUND_HEADER
#define SILLYCAT_SOUND_HEADER

#include "audio_buffer.hpp"


class Sound {
 
 public:
   Sound(const AudioBuffer * buff, bool loop = false);
   bool play(uint8_t * stream, int len);

 private:
   enum SoundState { Ready, Playing };
   SoundState mstate = Ready;

   const AudioBuffer * mbuffer = nullptr;
   bool mlooped = false;
   int mpos = 0;

};


#endif
