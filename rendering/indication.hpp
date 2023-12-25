#ifndef SILLYCAT_INDICATION_HEADER
#define SILLYCAT_INDICATION_HEADER

#include "display.hpp"
#include <array>
#include <chrono>


#define INDICATION_COUNT 4
enum Indication { PointGain, PointLoss, HpGain, HpLoss };


class Indicator : public Display {

 public:
   Indicator(SDL_Rect rect);
   void indicate(Indication indication);
   void render();
   void reset();
 
 private:
   std::array<std::chrono::time_point<std::chrono::high_resolution_clock>, INDICATION_COUNT> mtpoints;
   static const unsigned int mperiod = 700;

};


#endif
