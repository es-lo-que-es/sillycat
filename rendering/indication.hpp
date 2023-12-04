#ifndef sILLYCAT_INDICATION
#define sILLYCAT_INDICATION

#include "display.hpp"
#include <array>

#define INDICATION_COUNT 4
enum Indication { PointGain, PointLoss, HpGain, HpLoss };


class Indicator : public Display {

 public:
   Indicator(SDL_Rect rect);
   void indicate(Indication indication);
   void render();
   void reset();
 
 private:
   std::array<int, INDICATION_COUNT> count;

};


#endif
