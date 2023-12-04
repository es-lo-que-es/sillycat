#ifndef SILLYCAT_GAME_HEADER
#define SILLYCAT_GAME_HEADER

#include <vector>
#include "word.hpp"
#include "player.hpp"


class Game {

 public:
   void reset();
   Player player;
   Game(int font_size, int hp);

   const std::vector<Word>& words() const;
   bool over() const;

   bool move_player(Direction dir);
   bool do_tick();
   void end();

 private:
   void move_words();
   void spawn_word();

   std::vector<Word> mwords;

   bool mover = false;
   int mfont_size;
   int mtick = 0;
};



#endif
