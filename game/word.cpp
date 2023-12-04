#include "word.hpp"
#include "direction.hpp"
#include "globals.hpp"
#include "util.hpp"


SDL_Point Word::random_pos()
{
   SDL_Point result;

   int len = letters.size() * mfont_size;

   int rw = rand() % (globals.rect().w - mfont_size);
   int rh = rand() % (globals.rect().h - mfont_size);

   switch ( mdir ) {
      case Up: result = { rw, globals.rect().h }; break;
      case Right: result = { -len, rh }; break;
      case Down: result = { rw, -len }; break;
      case Left: result = { globals.rect().w, rh }; break;
   }

   return result;
}


Word::Word(const std::u32string &s, int font_size, Effect e, const Font * f, Direction d)
   : mfont_size(font_size), mdir(d)
{
   for ( uint32_t ch : s ) letters.push_back(Letter(ch, e, f));
   SDL_Point pos = random_pos();

   mrect = { pos.x, pos.y, mfont_size, mfont_size };

   int len = letters.size() * mfont_size;

   if ( vertical(mdir) ) mrect.h = len;
   else mrect.w = len;
}


bool Word::out_of_bounds() const
{
   bool result = false;
   SDL_Rect border = globals.rect();

   switch ( mdir ) {
      case Right: result = mrect.x >= border.w; break;
      case Down: result = mrect.y >= border.h; break;
      case Left: result = (mrect.x + mrect.w) < 0; break;
      case Up: result = (mrect.y + mrect.h) < 0; break;
   }

   return result;
}


bool Word::move()
{
   if ( out_of_bounds() ) return false;
   move_rect(mrect, globals.speed(), mdir);
   
   return true;
}


int Word::font_size() const { return mfont_size; }


SDL_Rect Word::rect() const { return mrect; }


Direction Word::dir() const { return mdir; }
