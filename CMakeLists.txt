cmake_minimum_required(VERSION 3.11.0)
project(bomberman VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()

# sources et include
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "include/*.hpp")

# Set 
if(MSVC)
	# Force to always compile with W4
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	# Update if necessary
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall")
endif()

# set the cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# set the boost options
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

# Trouver un package avec find_package
find_package("Irrlicht")
find_package(Boost 1.66.0) 

if (Irrlicht_FOUND AND Boost_FOUND)

	# executable
	include_directories(${Boost_INCLUDE_DIRS}) 
	include_directories(${Irrlicht_INCLUDE_DIRS})
	include_directories(include)

	add_executable(bomberman ${SOURCE_FILES})
	target_link_libraries(bomberman ${Irrlicht_LIBRARIES})
	target_link_libraries(bomberman ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Librairy not found")
endif()