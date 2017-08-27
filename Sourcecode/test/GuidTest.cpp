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
    std::set<Guid> guids;
    int dupCount = 0;

    for( int i = 0; i < 1000000000; ++i )
    {
        const auto result = guids.emplace();

        if( !result.second )
        {
            std::cout << dupCount << " duplicate " << result.first->getA() << " - " << result.first->getB() << std::endl;
            ++dupCount;
        }
    }
}

#endif
