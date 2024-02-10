#ifndef SILLYCAT_DIRECTION_HEADER
#define SILLYCAT_DIRECTION_HEADER


#define DIRECTION_COUNT 4
enum class Direction { Up, Right, Down, Left };


inline Direction rev(Direction dir) 
{ 
   return Direction(((int)dir + 2) % 4); 
}


inline Direction inc(Direction dir)
{
   return Direction(((int)dir + 1) % 4);
}


inline bool vertical(Direction dir) 
{
   return dir == Direction::Up || dir == Direction::Down;
}


inline bool uleft_direction(Direction dir) 
{
   return dir == Direction::Up || dir == Direction::Left;
}


#endif
