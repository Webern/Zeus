// Zeus, Copyright 2017 by Matthew James Briggs

#include "zeus/Guid.h"

// define the appropriate platform-specific macro for crossguid before including it
#if defined (__WIN32__)
#define GUID_WINDOWS
#endif

#if defined (__CYGWIN32__)
#define GUID_WINDOWS
#endif

#if defined (_MSC_VER)
#define GUID_WINDOWS
#endif

#if __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE
        #define GUID_CFUUID
    #elif TARGET_OS_MAC
        #define GUID_CFUUID
    #endif
#endif

#if __linux__
    #define GUID_LIBUUID
#elif __unix__
    #define GUID_LIBUUID
#elif defined(_POSIX_VERSION)
    #define GUID_LIBUUID
#endif

#include "crossguid/Guid.hpp"

namespace zeus
{

////////////////////////////////////////////////////////////////////////////////
// CTOR AND COPY ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	Guid::Guid()
    : mValue{}
	{
        xg::Guid g = xg::newGuid();
        mValue = g.str();
	}


    Guid::Guid( const std::array<unsigned char, 16>& inBytes )
    : mValue{}
    {
        xg::Guid g{ inBytes };
        mValue = g.str();
    }


    Guid::Guid( const unsigned char* inBytes )
    : mValue{}
    {
        xg::Guid g{ inBytes };
        mValue = g.str();
    }


    Guid::Guid( const std::string& inString )
    : mValue{}
    {
        xg::Guid g{ inString };

        if( g.isValid() )
        {
            mValue = g.str();
        }
    }

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	bool
	Guid::getIsValid() const
	{
        xg::Guid g{ mValue };
        return g.isValid();
	}


    void
    Guid::setZero()
    {
        xg::Guid g{};
        mValue = g.str();
    }


    std::string
    Guid::getString() const
    {
        return mValue;
    }

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    void
    Guid::privateFunc()
    {

    }

////////////////////////////////////////////////////////////////////////////////
// NON-MEMBER FUNCTIONS ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    bool operator<( const Guid& inLeft, const Guid& inRight )
    {
        return inLeft.getString() < inRight.getString();
    }


    bool operator>( const Guid& inLeft, const Guid& inRight )
    {
        return inRight.getString() < inLeft.getString();
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
