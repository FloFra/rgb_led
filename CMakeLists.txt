cmake_minimum_required ( VERSION 2.6 )
project ( rgbledctl )

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/)

link_directories(${EXECUTABLE_OUTPUT_PATH})

ADD_LIBRARY(rgbled SHARED src/rgbled.c)

ADD_EXECUTABLE(rgbledctl src/rgbledctl.cpp)

TARGET_LINK_LIBRARIES(rgbledctl rgbled)



INSTALL(TARGETS  rgbledctl  rgbled
			RUNTIME DESTINATION bin
			LIBRARY DESTINATION lib)

INSTALL(FILES src/rgbledctl.h DESTINATION include)