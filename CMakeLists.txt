cmake_minimum_required( VERSION 2.6 )
project( ncclock )

set( ncclock_sources
	main.c
	draw.c
	clock.c
)

set( ncclock_include_dirs
)

set( ncclock_library_dirs
)

set( ncclock_libraries
	ncurses
	m
)

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -std=gnu99 -D_GNU_SOURCE" )
link_directories( ${ncclock_library_dirs} )
include_directories( ${ncclock_include_dirs} )

add_executable( ncclock ${ncclock_sources} )
target_link_libraries( ncclock ${ncclock_libraries})
