#ifndef SILLYCAT_INDICATION_HEADER
#define SILLYCAT_INDICATION_HEADER

#include "display.hpp"
#include <array>
#include <chrono>


enum class Indication { PointGain, PointLoss, HpGain, HpLoss, Count };


class Indicator : public Display {

 public:
   Indicator(SDL_Rect rect);
   void indicate(Indication indication);
   void render();
   void reset();
 
 private:
   std::array<std::chrono::time_point<std::chrono::high_resolution_clock>, (int)Indication::Count> mtpoints;
   static const unsigned int mperiod = 700;

};


#endif
