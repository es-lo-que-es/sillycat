#ifndef SILLYCAT_WORD_HEADER
#define SILLYCAT_WORD_HEADER

#include <string>
#include <vector>

#include "direction.hpp"
#include "letter.hpp"


class Word {

 public:
   bool move();
   bool out_of_bounds() const;

   Word(const std::u32string &str, int letter_size, Effect e, const Font * f, Direction d);
   std::vector<Letter> letters;

   Direction dir() const;
   int font_size() const;
   SDL_Rect rect() const;

 private:
   SDL_Point random_pos();

   int mfont_size;
   Direction mdir;

   SDL_Rect mrect;
};


#endif
