cmake_minimum_required(VERSION 3.10)

project(sillycat)


set (CMAKE_CXX_STANDARD 17)
include_directories(. web game rendering audio)


SET (
   GAME_SOURCES

   config.cpp
   globals.cpp
   game_context.cpp

   game/inversion.cpp
   game/speed_control.cpp
   game/game.cpp
   game/word.cpp
   game/letter.cpp
   game/player.cpp
)

SET (
   AUDIO_SOURCES

   audio/audio_globals.cpp
   audio/audio_buffer.cpp
   audio/sound_pack.cpp
   audio/sound.cpp
)

SET (
   RENDERING_SOURCES

   rendering/gui_globals.cpp
   rendering/indication.cpp
   rendering/text_button.cpp
   rendering/score_label.cpp
   rendering/centered_label.cpp
   rendering/game_display.cpp
   rendering/texture_pack.cpp
   rendering/texture_pack.cpp
   rendering/switch_button.cpp
   rendering/display.cpp
   rendering/sprite.cpp
   rendering/bench.cpp
   rendering/menus.cpp
   rendering/util.cpp
   rendering/font.cpp
)



file(COPY pics DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY sounds DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY config.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


if ( ${BUILD_WASM} ) 
   
   add_compile_definitions(EMSCRIPTEN_BUILD)

   SET(CMAKE_C_COMPILER "emcc")
   SET(CMAKE_CXX_COMPILER "em++")

   set(USE_FLAGS "-sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -sSDL2_IMAGE_FORMATS='[\"bmp\",\"png\"]'")

   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
   set(PRELOAD_FILES "--preload-file=pics --preload-file=fonts --preload-file=config.json --use-preload-plugins")

   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -sTOTAL_MEMORY=20MB ${USE_FLAGS} ${PRELOAD_FILES}")
   set(CMAKE_EXECUTABLE_SUFFIX .js)

   add_executable(sillycat web/main.cpp ${GAME_SOURCES} ${RENDERING_SOURCES} ${AUDIO_SOURCES})

   file(COPY web/style.css DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   file(COPY web/game.html DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

else()

   add_executable(sillycat main.cpp ${GAME_SOURCES} ${RENDERING_SOURCES} ${AUDIO_SOURCES})
   target_link_libraries(sillycat SDL2 SDL2_image SDL2_ttf)

endif()
