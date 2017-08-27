// Zeus, Copyright 2017 by Matthew James Briggs

#define ZEUS_ENABLE_TEST
#ifdef ZEUS_ENABLE_TEST

#include "Catch.h"
#include "zeus/Guid.h"
#include "zeus/Rand.h"

#include <iostream>

using namespace zeus;

TEST_CASE( "sdfsdf", "[Guid]" )
{
    auto& r = Rand::getInstance();
//    Guid guid{};
//    std::cout << guid.getString() << std::endl;
}

#endif
