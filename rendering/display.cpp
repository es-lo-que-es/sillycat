#include "display.hpp"
#include "globals.hpp"


Display::Display() { }


Display::~Display() { }


Display::Display(SDL_Rect rect) : mrect(rect) { } 


bool Display::in_rect(SDL_Point point) const 
{ 
   return SDL_PointInRect(&point, &mrect);
}


void Display::set_rect(SDL_Rect rect) 
{ 
   mrect = rect;
}


SDL_Rect Display::rect() const 
{ 
   return mrect;
}


void Display::render() 
{ 
   for ( auto d : children ) d->render();
}


void Display::handle_event(SDL_Event * e) 
{ 
   if ( e->type == SDL_QUIT ) globals.run = false;
   for ( auto d : children ) d->handle_event(e);
}
