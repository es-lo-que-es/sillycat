#include "audio_globals.hpp"

#include <cstring>
#include <stdexcept>
#include "util.hpp"


void AudioGlobals::mix_in_sounds(uint8_t * stream, int len)
{
   for ( auto sound = msounds.begin(); sound != msounds.end(); ) {
      if ( !sound->play(stream, len) ) sound = msounds.erase(sound);
      else ++sound;
   }
}


void fill_callback(void * udata, uint8_t * stream, int len)
{
   memset(stream, 0, len);

   AudioGlobals * self = (AudioGlobals*) udata;
   self->mix_in_sounds(stream, len);
}


AudioGlobals::AudioGlobals()
{
   mspecs.callback = fill_callback;
   mspecs.userdata = this;
   mspecs.samples = 4096;
   
   mspecs.format = AUDIO_S16;
   mspecs.channels = 1;
   mspecs.freq = 22050;

   msound_pack.init(mspecs);

   int res = SDL_OpenAudio(&mspecs, NULL);
   if ( res < 0 ) throw std::runtime_error(sdl_error("failed to init audio:"));

   SDL_PauseAudio(0);
}


void AudioGlobals::play_sound(SoundName name)
{
   msounds.push_back(msound_pack[name]);
}


SDL_AudioSpec AudioGlobals::specs() const 
{
   return mspecs;
}


AudioGlobals::~AudioGlobals()
{
   SDL_CloseAudio();
}
