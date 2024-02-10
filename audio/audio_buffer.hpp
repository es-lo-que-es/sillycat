#ifndef SILLYCAT_AUDIO_BUFFER_HEADER
#define SILLYCAT_AUDIO_BUFFER_HEADER

#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>


class AudioBuffer {

 public:
   AudioBuffer(const char * filename, SDL_AudioSpec specs);
   const uint8_t * data() const;
   uint32_t len() const;

 private:
   std::vector<uint8_t> mbuffer;
   uint32_t mlen = 0;

};


#endif
