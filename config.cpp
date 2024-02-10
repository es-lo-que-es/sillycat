#include "config.hpp"

#include <fstream>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <string>

#include "nlohmann/json.hpp"

using json = nlohmann::json;


SDL_Color vec_to_color(const std::vector<int> &vec)
{
   SDL_Color col;
   if ( vec.size() != 4 ) throw std::runtime_error("invalid color config");

   col.r = vec[0]; col.g = vec[1];
   col.b = vec[2]; col.a = vec[3];

   return col;
}


std::u32string parse_utf8_string(const std::string &str)
{
   std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
   std::u32string result = converter.from_bytes(str);

   return result;
}


Config::Config()
{
   json data = json::parse(std::fstream("config.json"));
   
   background_color = vec_to_color(data["background-color"]);
   font_color = vec_to_color(data["font-color"]);

   for ( auto &word : data["words"] ) {
      if ( word["type"] < 0 || word["type"] >= EFFECT_TYPE_COUNT ) throw std::runtime_error("unknown effect type in the config");
      word_combos.push_back({ parse_utf8_string(word["str"]), { word["type"], word["value"]}});
   }
   
   alphabet = parse_utf8_string(data["alphabet"]);
   font_size = data["font-size"];
}


const std::pair<std::u32string, Effect>& Config::random_word_combo() const
{
   int index = rand() % word_combos.size();
   return word_combos[index];
}
