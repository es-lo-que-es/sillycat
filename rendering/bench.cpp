#include "bench.hpp"

#include <stdio.h>
#include <chrono>


std::chrono::time_point<std::chrono::high_resolution_clock> start;


void start_timer()
{
   start = std::chrono::high_resolution_clock::now();
}


void end_timer(const char * str)
{
   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> duration = end - start;

   printf("%s: %lfms\n", str, duration.count());
}
