# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("OOP1" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
file(GLOB C_FILES "src/*.cc")

if (WIN32)
	add_definitions("/W4 /WX") #Wall выводит ошибку "Record: 4 bytes padding addede after data member"
	add_compile_options(-D _CRT_SECURE_NO_WARNINGS) #fopen и scanf
else()
	add_definitions("-Wall -Wextra -Werror -Wconversion -Wsign-conversion")
endif(WIN32)

add_executable (${PROJECT_NAME} ${C_FILES}) 
