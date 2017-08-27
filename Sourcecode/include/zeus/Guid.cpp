// Zeus, Copyright 2017 by Matthew James Briggs

#include "zeus/Guid.h"
#include "zeus/Rand.h"

#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>

namespace zeus
{

////////////////////////////////////////////////////////////////////////////////
// CTOR AND COPY ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	Guid::Guid()
    : myA{ 0 }
    , myB{ 0 }
	{
        generate();
	}


    Guid::Guid( const std::array<uint8_t, 16>& inBytes )
    : myA{ 0 }
    , myB{ 0 }
    {
        setFromBytes( inBytes );
    }


    Guid::Guid( const std::string& inString )
    : myA{ 0 }
    , myB{ 0 }
    {
        setFromString( inString );
    }


    Guid::Guid( uint64_t inA, uint64_t inB )
    : myA{ inA }
    , myB{ inB }
    {

    }

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	bool
	Guid::getIsValid() const
	{
        return ( myA != 0 ) && ( myB != 0 );
	}


    void
    Guid::setZero()
    {
        myA = 0;
        myB = 0;
    }


    std::string
    Guid::getString() const
    {
        std::stringstream result;
        auto aP = reinterpret_cast<const uint8_t* const>( &myA );
        auto bP = reinterpret_cast<const uint8_t* const>( &myB );

        for( size_t i = 0; i < 16; ++i )
        {
            uint8_t theChar = 0;

            if( i < 8 )
            {
                theChar = aP[i];
            }
            else
            {
                theChar = bP[i % 8];
            }
            //         8    13   18   23
            // e90f73bc-8ae0-11e7-bb31-be2e44b06b34
            // a75846f7-6487-b100-d80c-c21c21aa8c00

            if( i == 4 || i == 6 || i == 8 || i == 10 )
            {
                result << "-";
            }
            result  << std::setfill( '0' )
                    << std::setw( 2 )
                    << std::hex
                    << static_cast<int>( theChar );
        }

        return result.str();
    }


    uint64_t
    Guid::getA() const
    {
        return myA;
    }


    uint64_t
    Guid::getB() const
    {
        return myB;
    }


    std::array<uint8_t, 16>
    Guid::getBytes() const
    {
        std::array<uint8_t, 16> bytes;

        for( int i = 0; i < 16; ++i )
        {
            bytes[i] = static_cast<uint8_t>( ( myA >> ( i * 16 ) ) & 0xFF );
        }

        for( int i = 0; i < 16; ++i )
        {
            bytes[i + 16] = static_cast<uint8_t>( ( myB >> ( i * 16 ) ) & 0xFF );
        }

        return bytes;
    }


    void
    Guid::setFromBytes( const std::array<uint8_t, 16>& inBytes )
    {
        myA = uint64_t( ( static_cast<uint64_t>( inBytes[0] ) ) << 56 |
                       ( static_cast<uint64_t>( inBytes[1] ) ) << 48 |
                       ( static_cast<uint64_t>( inBytes[2] ) ) << 40 |
                       ( static_cast<uint64_t>( inBytes[3] ) ) << 32 |
                       ( static_cast<uint64_t>( inBytes[4] ) ) << 24 |
                       ( static_cast<uint64_t>( inBytes[5] ) ) << 16 |
                       ( static_cast<uint64_t>( inBytes[6] ) ) << 8  |
                       ( static_cast<uint64_t>( inBytes[7] ) ) << 0  );

        myB = uint64_t( ( static_cast<uint64_t>( inBytes[8]  ) ) << 56 |
                       ( static_cast<uint64_t>( inBytes[9]  ) ) << 48 |
                       ( static_cast<uint64_t>( inBytes[10] ) ) << 40 |
                       ( static_cast<uint64_t>( inBytes[11] ) ) << 32 |
                       ( static_cast<uint64_t>( inBytes[12] ) ) << 24 |
                       ( static_cast<uint64_t>( inBytes[13] ) ) << 16 |
                       ( static_cast<uint64_t>( inBytes[14] ) ) << 8  |
                       ( static_cast<uint64_t>( inBytes[15] ) ) << 0  );
    }


    void
    Guid::setFromString( const std::string& inString )
    {
        // TODO - implement
    }

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    void
    Guid::generate()
    {
        const auto bytes1 = Rand::getInstance().getRandBytes( 8 );

        const auto tsnow = std::chrono::high_resolution_clock::now().time_since_epoch();
        const auto tsobj = std::chrono::duration_cast<std::chrono::nanoseconds>( tsnow );
        const auto ts = static_cast<uint64_t>( tsobj.count() );
        const uint8_t* const bytes2 = reinterpret_cast<const uint8_t* const>( &ts );

        size_t byteDestPos = 0;
        size_t byteSourcePos = 0;

        while( byteSourcePos < bytes1.size() && byteDestPos < sizeof( myA ) )
        {
            reinterpret_cast<uint8_t*>( &myA )[byteDestPos] = bytes1.at( byteSourcePos );
            ++byteSourcePos;
            reinterpret_cast<uint8_t*>( &myB )[byteDestPos] = bytes1.at( byteSourcePos );
            ++byteSourcePos;
            ++byteDestPos;
        }

        byteSourcePos = 0;

        while( byteSourcePos < sizeof( ts ) && byteDestPos < sizeof( myA ) )
        {
            reinterpret_cast<uint8_t*>( &myA )[byteDestPos] = bytes2[byteSourcePos];
            ++byteSourcePos;
            reinterpret_cast<uint8_t*>( &myB )[byteDestPos] = bytes2[byteSourcePos];
            ++byteSourcePos;
            ++byteDestPos;
        }
    }

////////////////////////////////////////////////////////////////////////////////
// NON-MEMBER FUNCTIONS ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    bool operator<( const Guid& inLeft, const Guid& inRight )
    {
        if( inLeft.getA() < inRight.getA() )
        {
            return true;
        }
        else if( inLeft.getA() > inRight.getA() )
        {
            return false;
        }

        if( inLeft.getB() < inRight.getB() )
        {
            return true;
        }

        return false;
    }


    bool operator>( const Guid& inLeft, const Guid& inRight )
    {
        return inRight < inLeft;
    }


    bool operator==( const Guid& inLeft, const Guid& inRight )
    {
        const bool isLessThan = inLeft < inRight;
        const bool isGreaterThan = inLeft > inRight;
        const bool isEqual = !isLessThan && !isGreaterThan;
        return isEqual;
    }


    bool operator!=( const Guid& inLeft, const Guid& inRight )
    {
        return !( inLeft == inRight );
    }


    bool operator<=( const Guid& inLeft, const Guid& inRight )
    {
        return ( inLeft < inRight ) || ( inLeft == inRight );
    }


    bool operator>=( const Guid& inLeft, const Guid& inRight )
    {
        return ( inLeft > inRight ) || ( inLeft == inRight );
    }
}
