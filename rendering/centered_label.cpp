#include "centered_label.hpp"
#include "globals.hpp"
#include "util.hpp"


CenteredLabel::CenteredLabel() { } 


CenteredLabel::CenteredLabel(const std::string &str, SDL_Rect rect, int font_size, bool bg)
{
   init(str, rect, font_size, bg);
}


void CenteredLabel::init(const std::string &str, SDL_Rect rect, int font_size, bool bg)
{
   mtext = str;
   mtarget = rect;
   minit_len = str.length();

   mfont_size = font_size;
   mbackground = bg;

   mrect.y = mtarget.y + ( mtarget.h - mfont_size ) / 2;
   mrect.h = mfont_size;

   adjust_alignment();
}


void CenteredLabel::adjust_alignment()
{
   int text_width = mfont_size * mtext.length();
   mrect.x = mtarget.x + ( mtarget.w - text_width ) / 2;
   mrect.w = text_width;
}


void CenteredLabel::render()
{
   if ( mbackground ) render_fill_rect(&mrect, globals.config.background_color);
   globals.gui.fonts()[0].render_string(mtext, {mrect.x, mrect.y}, mfont_size);
}


void CenteredLabel::replace_tail(const char * str)
{
   int len = strlen(str);
   mtext.replace(minit_len, len, str);
   mtext.resize(minit_len + len);

   adjust_alignment();
}
