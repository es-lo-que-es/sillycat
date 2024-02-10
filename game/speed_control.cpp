#include "speed_control.hpp"
#include <algorithm>


void SpeedControl::init(int speed)
{
   mdefault_speed = mspeed = speed;

   mmin_speed = std::max(1.0, speed / 1.2);
   mmax_speed = std::max(1.0, speed * 1.4);
}


int SpeedControl::get() const 
{ 
   return mspeed;
} 


void SpeedControl::mod(int val)
{
   mspeed += val;
   if ( mspeed > mmax_speed ) mspeed = mmax_speed;
   else if ( mspeed < mmin_speed ) mspeed = mmin_speed;
}


void SpeedControl::reset() 
{
   mspeed = mdefault_speed;
}
