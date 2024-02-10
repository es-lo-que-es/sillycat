#include "word.hpp"
#include "direction.hpp"
#include "globals.hpp"
#include "util.hpp"


SDL_Point Word::random_pos()
{
   SDL_Point result;

   SDL_Rect rect = globals.gui.rect();
   int len = letters.size() * mfont_size;

   int rw = rand() % (rect.w - mfont_size);
   int rh = rand() % (rect.h - mfont_size);

   switch ( mdir ) {
      case Direction::Up: result = { rw, rect.h }; break;
      case Direction::Right: result = { -len, rh }; break;
      case Direction::Down: result = { rw, -len }; break;
      case Direction::Left: result = { rect.w, rh }; break;
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
   SDL_Rect border = globals.gui.rect();

   switch ( mdir ) {
      case Direction::Right: result = mrect.x >= border.w; break;
      case Direction::Down: result = mrect.y >= border.h; break;
      case Direction::Left: result = (mrect.x + mrect.w) < 0; break;
      case Direction::Up: result = (mrect.y + mrect.h) < 0; break;
   }

   return result;
}


bool Word::move()
{
   if ( out_of_bounds() ) return false;
   move_rect(mrect, globals.speed.get(), mdir);
   
   return true;
}


int Word::font_size() const { return mfont_size; }


SDL_Rect Word::rect() const { return mrect; }


Direction Word::dir() const { return mdir; }
