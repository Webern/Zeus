// Zeus, Copyright 2017 by Matthew James Briggs

#pragma once

#include <string>
#include <array>

namespace zeus
{
	/// @brief Guid Generator
	///
	/// @detailed Generates a guid and holds it as a string
	///
    class Guid
    {
    public:
    	Guid();
        Guid( const std::array<unsigned char, 16>& inBytes );
        Guid( const unsigned char* inBytes );
        Guid( const std::string& inString );

    public:
    	bool getIsValid() const;
        void setZero();
        std::string getString() const;

    private:
        std::string mValue;

    private:
        void privateFunc();     
    };

    bool operator<( const Guid& inLeft, const Guid& inRight );
    bool operator>( const Guid& inLeft, const Guid& inRight );
    bool operator==( const Guid& inLeft, const Guid& inRight );
    bool operator!=( const Guid& inLeft, const Guid& inRight );
    bool operator>=( const Guid& inLeft, const Guid& inRight );
    bool operator<=( const Guid& inLeft, const Guid& inRight );

}
