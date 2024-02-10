#ifndef SILLYCAT_INVERSION_HEADER
#define SILLYCAT_INVERSION_HEADER

#include <chrono>


class Inversion {
 
 public: 
   Inversion();

   void reset();
   void trigger();

   bool active() const;

 private:
   std::chrono::time_point<std::chrono::high_resolution_clock> mlasat_invert;
   const unsigned int minterval = 2000;
   bool mactive = false;

   void apply_invert();
};


#endif

