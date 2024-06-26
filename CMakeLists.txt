# debug vs release
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_COMPILER "clang++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -fsanitize=address -pedantic")

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

endif()

# set cmake standards
cmake_minimum_required(VERSION 3.10)
project(cli_blackjack)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# fetch google test
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
)

FetchContent_MakeAvailable(googletest)

# include dir
include_directories("include/cli_blackjack" "include/gtest")

# add executables
add_executable(main "./src/main.cpp")
add_executable(card_test "./test/card_test.cpp")
add_executable(deck_test "./test/deck_test.cpp")
add_executable(player_test "./test/player_test.cpp")
add_executable(dealer_test "./test/dealer_test.cpp")

# make libraries with source files
add_library(card_library STATIC 
"./src/card.cpp" 
"./src/deck.cpp"
"./src/player.cpp"
"./src/dealer.cpp"
)

# link libraries to executables
target_link_libraries(main card_library)
target_link_libraries(card_test gtest_main card_library)
target_link_libraries(deck_test gtest_main card_library)
target_link_libraries(player_test gtest_main card_library)
target_link_libraries(dealer_test gtest_main card_library)


# add test
add_test(card_test card_test)
add_test(deck_test deck_test)
add_test(player_test player_test)
add_test(dealer_test dealer_test)
