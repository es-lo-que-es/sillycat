#ifndef SILLYCAT_EFFECTS_HEADER
#define SILLYCAT_EFFECTS_HEADER


#define EFFECT_TYPE_COUNT 6
enum class EffectType { Health, Death, Points, Speed, Invert, Random };


struct Effect{
   EffectType type;
   int value;
};


#endif
