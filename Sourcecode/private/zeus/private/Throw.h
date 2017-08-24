// MusicXML Class Library
// Copyright (c) by Matthew James Briggs
// Distributed under the MIT License

#pragma once

#include <string>

#ifndef __FILENAME__

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

        #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

    #else

        #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

    #endif

#endif

#ifndef ZEUS_THROW
#define ZEUS_THROW(throw_error_message)                 \
throw std::runtime_error (                              \
  std::string( "error in " )                            \
+ std::string( __FILENAME__ )                           \
+ std::string(" (line ")                                \
+ std::string( std::to_string(__LINE__ ) )              \
+ std::string(") ")                                     \
+ std::string( __FUNCTION__ )                           \
+ std::string(": '")                                    \
+ std::string( throw_error_message ) );                    
#endif

#ifndef ZEUS_THROW_NULL
#define THROW_NULL THROW("null pointer encountered")
#endif

#ifndef ZEUS_THROW_IF_NULL
#define THROW_IF_NULL(pointerVariable)               \
if ( pointerVariable == nullptr ) { THROW_NULL }
#endif

#ifndef ZEUS_THROW_IF_BAD_VALUE
#define THROW_IF_BAD_VALUE( VALUE, MIN_VAL, MAX_VAL )                          \
if( VALUE < MIN_VAL || VALUE > MAX_VAL ) {                                     \
std::stringstream BADVALUEMESSAGE;                                             \
BADVALUEMESSAGE << "value out of range. " <<                                   \
#VALUE << " = " << VALUE << ", min = " << MIN_VAL << ", max = " << MAX_VAL;    \
THROW( BADVALUEMESSAGE.str() ) }
#endif

#ifndef ZEUS_BUG
#define ZEUS_BUG ZEUS_THROW( "this exception is due to a coding error" );
#endif

#ifndef ZEUS_ASSERT
#define ZEUS_ASSERT(expectedTrueStatement)               \
if ( ! (expectedTrueStatement) ) { ZEUS_THROW("assertion failed '" #expectedTrueStatement "'"); }
#endif
