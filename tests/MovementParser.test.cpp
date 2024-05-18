#include <gtest/gtest.h>
#include <engines/movement/MovementParser.hpp>

TEST(MovementParser, parse) {
    finder::engines::movement::MovementParser parser;
    parser.parse(finder::math::Vector2{2, 2});
    
        
}