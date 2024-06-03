#include <gtest/gtest.h>
#include <engines/movement/MovementParser.hpp>

TEST(MovementParser, parse) {
    finder::engines::movement::MovementParser parser{"./test"};
    parser.parse(finder::math::Vector2{2, 2});
    
        
}