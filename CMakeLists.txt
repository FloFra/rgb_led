cmake_minimum_required ( VERSION 2.6 )
project ( RGBLEDControl )

FIND_PACKAGE( Boost 1.40 COMPONENTS system thread REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(rgbledctl RGBLEDControl.cpp)

TARGET_LINK_LIBRARIES( rgbledctl ${Boost_LIBRARIES} )

install (TARGETS rgbledctl DESTINATION bin)
