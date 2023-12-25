#ifndef SILLYCAT_DIRECTION_HEADER
#define SILLYCAT_DIRECTION_HEADER


#define DIRECTION_COUNT 4
enum Direction { Up, Right, Down, Left };


inline Direction rev(Direction dir) 
{ 
   return Direction((dir + 2) % 4); 
}


inline Direction inc(Direction dir)
{
   return Direction((dir + 1) % 4);
}


inline bool vertical(Direction dir) 
{
   return dir == Up || dir == Down;
}


#endif
