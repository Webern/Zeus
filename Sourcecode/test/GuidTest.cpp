// Zeus, Copyright 2017 by Matthew James Briggs

#define ZEUS_ENABLE_TEST
#ifdef ZEUS_ENABLE_TEST

#include "Catch.h"
#include "zeus/Guid.h"
#include "zeus/Rand.h"

#include <iostream>

using namespace zeus;

TEST_CASE( "CollisionCheck", "[Guid]" )
{
    constexpr const size_t count = 1000000;
    std::set<Guid> guids;
    std::vector<Guid> duplicates;

    for( size_t i = 0; i < count; ++i )
    {
        const auto result = guids.emplace();

        if( !result.second )
        {
            std::cout << "duplicate " << result.first->getA() << " - " << result.first->getB() << std::endl;
            duplicates.push_back( *result.first );
        }
    }

    REQUIRE( duplicates.size() == 0 );
}


TEST_CASE( "BitManipCheck01", "[Guid]" )
{
    Guid orig{};
    REQUIRE( orig.getIsValid() );
    Guid copy{ orig.getBytes() };
    REQUIRE( orig == copy );
}

TEST_CASE( "StringParse01", "[Guid]" )
{
    Guid orig{};
    REQUIRE( orig.getIsValid() );
    Guid copy{ orig.getString() };
    REQUIRE( orig == copy );
}

#endif
