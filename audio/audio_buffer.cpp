#include "audio_buffer.hpp"

#include <SDL2/SDL_timer.h>
#include <stdexcept>
#include <memory>

#include <SDL2/SDL.h>
#include "util.hpp"


void free_wav(uint8_t * ptr) { SDL_FreeWAV(ptr); };


AudioBuffer :: AudioBuffer(const char * filename, SDL_AudioSpec specs)
{
   Uint8 * data;
   SDL_AudioCVT cvt;
   SDL_AudioSpec wave;

   auto pspec = SDL_LoadWAV(filename, &wave, &data, &mlen);
   if ( pspec == NULL ) throw std::runtime_error(sdl_error("failed to load wav:"));
   std::unique_ptr<uint8_t, decltype(&free_wav)> wav_guard(data, free_wav);

   int res = SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq, specs.format, specs.channels, specs.freq);
   if ( res < 0 ) throw std::runtime_error(sdl_error("failed build wav converter:"));

   mbuffer.resize(mlen * cvt.len_mult);
   cvt.buf = (uint8_t*)mbuffer.data();
   memcpy(cvt.buf, data, mlen);
   cvt.len = mlen;

   res = SDL_ConvertAudio(&cvt);
   if ( res < 0 ) throw std::runtime_error(sdl_error("failed to convert wav:"));

   mlen = cvt.len_cvt;
}


const uint8_t * AudioBuffer::data() const
{  
   return mbuffer.data();
}


uint32_t AudioBuffer::len() const
{
   return mlen;
}
