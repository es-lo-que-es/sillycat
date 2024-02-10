#include "sound.hpp"



Sound::Sound(const AudioBuffer * buff, bool loop)
   : mbuffer(buff), mlooped(loop)
{ }


bool Sound::play(uint8_t * stream, int len)
{
   if ( mstate == Ready ) mstate = Playing;
   int left = mbuffer->len() - mpos;

   if ( left <= 0 ) {

      if ( !mlooped ) return false;

      left = mbuffer->len();
      mpos = 0;
   }

   len = ( len > left ? left : len );

   SDL_MixAudio(stream, mbuffer->data() + mpos, len, SDL_MIX_MAXVOLUME);
   mpos += len;

   return true;
}
