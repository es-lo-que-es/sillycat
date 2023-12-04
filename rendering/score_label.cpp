#include "score_label.hpp"
#include <stdio.h>


ScoreLabel::ScoreLabel() { }


ScoreLabel::ScoreLabel(const std::string &text, SDL_Rect rect, int font_size)
{ 
   init(text, rect, font_size);
}


void ScoreLabel::init(const std::string &text, SDL_Rect rect, int font_size)
{
   mname_len = text.length();
   mlabel.init(text, rect, font_size, true);
   children.push_back(&mlabel);

   update(mscore);
}


void ScoreLabel::update(int new_score)
{
   snprintf(mscore_str, sizeof(mscore_str)-1, "%d", new_score);
   mlabel.replace_tail(mscore_str);
   mscore = new_score;
}


int ScoreLabel::score() const 
{
   return mscore;
}
