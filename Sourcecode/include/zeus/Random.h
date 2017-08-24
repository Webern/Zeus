// Zeus, Copyright 2017 by Matthew James Briggs

#pragma once

#include <vector>
#include <mutex>

namespace zeus
{
	/// @brief Provides Pseudo Random Numbers
	///
	/// @detailed Really it Does
	///
    class Random
    {
    public:


    public:
        /// currently only supports a range of 100, throws if range is too big
        static int getRandBetween( int inMin, int inMax );
        static bool getRandomBool();

    private:
        std::vector<int8_t> myValues;
        int myCurrentIndex;
        mutable std::mutex myMutex;

    private:
        Random();
        static Random& getInstance();
        size_t getIndexAndAdvance();
    };
}
