#ifndef SILLYCAT_SPEED_CONTROL
#define SILLYCAT_SPEED_CONTROL


class SpeedControl {

 public: 
   void init(int speed);
   void mod(int val);
   int get() const;
   void reset();

 private:
   int mdefault_speed;
   int mmax_speed;
   int mmin_speed;
   int mspeed;
};


#endif
