# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\serialLog_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\serialLog_autogen.dir\\ParseCache.txt"
  "serialLog_autogen"
  )
endif()
