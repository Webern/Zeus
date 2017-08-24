// Zeus, Copyright 2017 by Matthew James Briggs

#include "zeus/Random.h"
#include "zeus/private/Throw.h"

namespace zeus
{

////////////////////////////////////////////////////////////////////////////////
// CTOR AND COPY ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	Random::Random()
	: myValues{}
	{
        myValues = std::vector<int8_t>
        {
            #include "zeus/private/RandomNumbers.def"
        };
	}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    int
    Random::getRandBetween( int inMin, int inMax )
    {
        auto& instance = getInstance();
        std::lock_guard<std::mutex> lock{instance.myMutex};

        if ( inMin > inMax )
        {
            return 0;
        }

        const auto range = inMax - inMin;

        if ( range > 100 )
        {
            ZEUS_THROW( "only ranges of 100 or less are currently supported" );
        }

        const auto adjustment = 0 - inMin;
        inMin += adjustment;
        inMax += adjustment;


        const auto currentValue = instance.myValues.at(instance.getIndexAndAdvance());
        const auto modded = currentValue % static_cast<int8_t>( range );
        const auto result = static_cast<int>( modded ) + static_cast<int>( adjustment );
        return result;
    }


    bool
    Random::getRandomBool()
    {
        auto& instance = getInstance();
        const auto value = instance.getRandBetween( 0, 1 );
        const bool result = static_cast<bool>( value );
        return result;
    }

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    Random&
    Random::getInstance()
    {
        static Random sharedInstance{};
        return sharedInstance;
    }


    size_t
    Random::getIndexAndAdvance()
    {
        const auto result = myCurrentIndex;

        if ( static_cast<size_t>(myCurrentIndex) >= myValues.size() )
        {
            myCurrentIndex = 0;
        }
        else
        {
            ++myCurrentIndex;
        }

        return result;
    }

}
