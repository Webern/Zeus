// Zeus, Copyright 2017 by Matthew James Briggs

#include "zeus/Rand.h"

#include <iostream>
#include <thread>
#include <memory>
#include <array>

namespace
{
    constexpr const uint64_t PRIME_NUMBER_64BIT = 10003181;
    constexpr const unsigned int PRIME_NUMBER_UINT = static_cast<unsigned int>( PRIME_NUMBER_64BIT );
}

namespace zeus
{

////////////////////////////////////////////////////////////////////////////////
// CTOR AND COPY ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    std::mutex Rand::ourMutex{};

	Rand::Rand()
    : myEntropy{ std::numeric_limits<decltype(myEntropy)>::max() }
	{
        std::lock_guard<std::mutex> lock{ Rand::ourMutex };
        seed();
	}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    std::vector<uint8_t>
	Rand::getRandBytes( int inNumBytes )
	{
        std::lock_guard<std::mutex> lock{ ourMutex };
        std::vector<uint8_t> bytes;

        int totalBytes = 0;

        while( totalBytes < inNumBytes )
        {
            const auto randomNumber = std::rand();
            const size_t randSize = sizeof( randomNumber );
            const uint8_t* const randomBytes = reinterpret_cast<const uint8_t* const>( &randomNumber );

            for( size_t i = 0; i < randSize; ++i, ++totalBytes )
            {
                if( totalBytes >= inNumBytes )
                {
                    break;
                }

                bytes.push_back( randomBytes[i] );
            }
        }

        return bytes;
	}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    void
    Rand::seed()
    {
        std::hash<std::thread::id> hasher;
        const auto threadIdObject = std::this_thread::get_id();
        const auto threadIdHash = hasher( threadIdObject );
        const auto threadId = static_cast<uint64_t>( threadIdHash );
        const auto intP = std::make_unique<int>( 0 );
        const auto address = reinterpret_cast<uint64_t>( intP.get() );
        const auto tsnow = std::chrono::high_resolution_clock::now().time_since_epoch();
        const auto tsobj = std::chrono::duration_cast<std::chrono::nanoseconds>( tsnow );
        const auto ts = static_cast<uint64_t>( tsobj.count() );

        uint64_t hash = threadId;
        hash *= PRIME_NUMBER_64BIT;
        hash += address;
        hash *= PRIME_NUMBER_64BIT;
        hash += ts;

        const int targetByteCount = sizeof(unsigned int);
        unsigned int srandSeed = 0;

        if( targetByteCount == 8 )
        {
            srandSeed = static_cast<unsigned int>( hash );
        }
        else
        {
            std::array<uint8_t, 8> entropyBytes;
            uint8_t* hashBytesP = reinterpret_cast<uint8_t*>( &hash );

            for( size_t i = 0; i < 8; ++i )
            {
                entropyBytes[i] = hashBytesP[i];
            }

            unsigned int uintHash = 0;
            unsigned int part0 = *reinterpret_cast<unsigned int*>(hashBytesP);
            unsigned int part4 = *reinterpret_cast<unsigned int*>(hashBytesP + 4);

            uintHash = part0;
            uintHash *= PRIME_NUMBER_UINT;
            uintHash += part4;
            srandSeed = uintHash;
        }

        std::srand( srandSeed );
        myEntropy = hash;
    }

////////////////////////////////////////////////////////////////////////////////
// PRIVATE STATIC FUNCTIONS ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    Rand&
    Rand::getInstance()
    {
        static Rand instance;
        return instance;
    }

}
