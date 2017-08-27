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


TEST_CASE( "StringParse02", "[Guid]" )
{
    const std::string str1 = "8ee18c15-5daf-6c00-db24-5a6888fe9dce";
    const std::string str2 = "8eE18C15-5dAF-6c00-DB24-5a6888fe9DCE";

    Guid orig{ str1 };
    REQUIRE( orig.getIsValid() );
    Guid copy{ str2 };
    REQUIRE( orig == copy );
}




TEST_CASE( "StringParse03", "[Guid]" )
{
    const std::string str1 = "8ee18c15-5daf-6cFf-db24-5a6888fe9dce";
    const std::string str2 = "8eE18C15xxxx5dAF6cFfxDB24_____5a6888fe9DCE";

    Guid orig{ str1 };
    REQUIRE( orig.getIsValid() );
    Guid copy{ str2 };
    REQUIRE( orig == copy );
}

//inString	const string &		0x00007fff5fbfe110

#endif
