// Zeus, Copyright 2017 by Matthew James Briggs

#pragma once

#include <string>
#include <array>
#include <mutex>

namespace zeus
{
	/// @brief Guid Generator
	///
	/// @detailed Generates a guid and holds it as two 64-bit unsigned ints
	///
    class Guid
    {
    public:
    	Guid();
        Guid( const std::array<uint8_t, 16>& inBytes );
        Guid( const std::string& inString );
        Guid( uint64_t inA, uint64_t inB );

    public:
    	bool getIsValid() const;
        void setZero();
        std::string getString() const;
        uint64_t getA() const;
        uint64_t getB() const;
        std::array<uint8_t, 16> getBytes() const;
        void setFromBytes( const std::array<uint8_t, 16>& inBytes );
        void setFromString( const std::string& inString );

    private:
        uint64_t myA;
        uint64_t myB;

    private:
        static std::recursive_mutex ourMutex;
        static bool ourIsSeeded;

    private:
        void generate();
    };

    bool operator<( const Guid& inLeft, const Guid& inRight );
    bool operator>( const Guid& inLeft, const Guid& inRight );
    bool operator==( const Guid& inLeft, const Guid& inRight );
    bool operator!=( const Guid& inLeft, const Guid& inRight );
    bool operator>=( const Guid& inLeft, const Guid& inRight );
    bool operator<=( const Guid& inLeft, const Guid& inRight );

}
