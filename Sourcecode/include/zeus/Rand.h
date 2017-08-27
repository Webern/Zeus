// Zeus, Copyright 2017 by Matthew James Briggs

#pragma once

#include <mutex>
#include <vector>

namespace zeus
{
	/// @brief TODO
	///
	/// @detailed TODO
	///
    class Rand
    {
    public:
    	Rand();

    public:
        static std::vector<uint8_t> getRandBytes( int inNumBytes );

    private:
        static std::mutex ourMutex;
        uint64_t myEntropy;

    private:
        void seed();

    public:
        static Rand& getInstance();

    };
}
