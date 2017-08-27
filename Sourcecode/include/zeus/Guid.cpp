//// Zeus, Copyright 2017 by Matthew James Briggs
//
//#include "zeus/Guid.h"
//#include <thread>
//#include <random>
//
//namespace zeus
//{
//
//////////////////////////////////////////////////////////////////////////////////
//// CTOR AND COPY ///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	Guid::Guid()
//    : myA{ 0 }
//    , myB{ 0 }
//	{
//        xg::Guid g = xg::newGuid();
//        setFromBytes( g.getBytes() );
//	}
//
//
//    Guid::Guid( const std::array<uint8_t, 16>& inBytes )
//    : myA{ 0 }
//    , myB{ 0 }
//    {
//        setFromBytes( inBytes );
//    }
//
//
//    Guid::Guid( const std::string& inString )
//    : myA{ 0 }
//    , myB{ 0 }
//    {
//        xg::Guid g{ inString };
//
//        if( g.isValid() )
//        {
//            setFromBytes( g.getBytes() );
//        }
//    }
//
//
//    Guid::Guid( uint64_t inA, uint64_t inB )
//    : myA{ inA }
//    , myB{ inB }
//    {
//
//    }
//
//////////////////////////////////////////////////////////////////////////////////
//// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//	bool
//	Guid::getIsValid() const
//	{
//        const auto bytes = getBytes();
//        xg::Guid g{ bytes };
//        return g.isValid();
//	}
//
//
//    void
//    Guid::setZero()
//    {
//        myA = 0;
//        myB = 0;
//    }
//
//
//    std::string
//    Guid::getString() const
//    {
//        const auto bytes = getBytes();
//        xg::Guid g{ bytes };
//        return g.str();
//    }
//
//
//    uint64_t
//    Guid::getA() const
//    {
//        return myA;
//    }
//
//
//    uint64_t
//    Guid::getB() const
//    {
//        return myB;
//    }
//
//
//    std::array<uint8_t, 16>
//    Guid::getBytes() const
//    {
//        std::array<uint8_t, 16> bytes;
//
//        for( int i = 0; i < 16; ++i )
//        {
//            bytes[i] = static_cast<uint8_t>( ( myA >> ( i * 16 ) ) & 0xFF );
//        }
//
//        for( int i = 0; i < 16; ++i )
//        {
//            bytes[i + 16] = static_cast<uint8_t>( ( myB >> ( i * 16 ) ) & 0xFF );
//        }
//
//        return bytes;
//    }
//
//////////////////////////////////////////////////////////////////////////////////
//// PRIVATE FUNCTIONS ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//    void
//    Guid::setFromBytes( const std::array<uint8_t, 16>& inBytes )
//    {
//        myA = uint64_t( ( static_cast<uint64_t>( inBytes[0] ) ) << 56 |
//                        ( static_cast<uint64_t>( inBytes[1] ) ) << 48 |
//                        ( static_cast<uint64_t>( inBytes[2] ) ) << 40 |
//                        ( static_cast<uint64_t>( inBytes[3] ) ) << 32 |
//                        ( static_cast<uint64_t>( inBytes[4] ) ) << 24 |
//                        ( static_cast<uint64_t>( inBytes[5] ) ) << 16 |
//                        ( static_cast<uint64_t>( inBytes[6] ) ) << 8  |
//                        ( static_cast<uint64_t>( inBytes[7] ) ) << 0  );
//
//        myB = uint64_t( ( static_cast<uint64_t>( inBytes[8]  ) ) << 56 |
//                        ( static_cast<uint64_t>( inBytes[9]  ) ) << 48 |
//                        ( static_cast<uint64_t>( inBytes[10] ) ) << 40 |
//                        ( static_cast<uint64_t>( inBytes[11] ) ) << 32 |
//                        ( static_cast<uint64_t>( inBytes[12] ) ) << 24 |
//                        ( static_cast<uint64_t>( inBytes[13] ) ) << 16 |
//                        ( static_cast<uint64_t>( inBytes[14] ) ) << 8  |
//                        ( static_cast<uint64_t>( inBytes[15] ) ) << 0  );
//    }
//
//////////////////////////////////////////////////////////////////////////////////
//// NON-MEMBER FUNCTIONS ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//    bool operator<( const Guid& inLeft, const Guid& inRight )
//    {
//        return inLeft.getString() < inRight.getString();
//    }
//
//
//    bool operator>( const Guid& inLeft, const Guid& inRight )
//    {
//        return inRight.getString() < inLeft.getString();
//    }
//
//
//    bool operator==( const Guid& inLeft, const Guid& inRight )
//    {
//        const bool isLessThan = inLeft < inRight;
//        const bool isGreaterThan = inLeft > inRight;
//        const bool isEqual = !isLessThan && !isGreaterThan;
//        return isEqual;
//    }
//
//
//    bool operator!=( const Guid& inLeft, const Guid& inRight )
//    {
//        return !( inLeft == inRight );
//    }
//
//
//    bool operator<=( const Guid& inLeft, const Guid& inRight )
//    {
//        return ( inLeft < inRight ) || ( inLeft == inRight );
//    }
//
//
//    bool operator>=( const Guid& inLeft, const Guid& inRight )
//    {
//        return ( inLeft > inRight ) || ( inLeft == inRight );
//    }
//}
