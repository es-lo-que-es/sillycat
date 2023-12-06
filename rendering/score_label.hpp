#ifndef SILLYCAT_SCORE_LABEL
#define SILLYCAT_SCORE_LABEL

#include "centered_label.hpp"
#include "display.hpp"


class ScoreLabel : public Display {

 public: 

   ScoreLabel();
   int score() const;

   void init(const std::string &text, SDL_Rect rect, int font_size);
   ScoreLabel(const std::string &text, SDL_Rect rect, int font_size);
   void update(int score);

 private:

   char mscore_str[32] = { 0 };
   CenteredLabel mlabel;

   int mname_len = 0;
   int mscore = 0;

};


#endif
