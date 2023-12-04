#ifndef SILLYCAT_EFFECTS_HEADER
#define SILLYCAT_EFFECTS_HEADER


#define EFFECT_TYPE_COUNT 5
enum EffectType { Health, Death, Points, Speed, Random };


struct Effect{
   EffectType type;
   int value;
};


#endif
