############################################################################
# CMakeLists.txt
# Copyright (C) 2015  Belledonne Communications, Grenoble France
#
############################################################################
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#
############################################################################

if(ENABLE_SHARED)
	set(BELR_LIBRARIES_FOR_TESTER belr)
else()
	set(BELR_LIBRARIES_FOR_TESTER belr-static)
endif()

set(GRAMMAR_FILES
	grammars/basicgrammar.txt
	grammars/vcardgrammar.txt
	grammars/sipgrammar.txt
)

set(HEADER_FILES_CXX belr-tester.hpp)
set(SOURCE_FILES_CXX
	belr-tester.cpp
	belr-charrecognizer-tester.cpp
	belr-selector-tester.cpp
	belr-exclusiveselector-tester.cpp
	belr-sequence-tester.cpp
	belr-loop-tester.cpp
	belr-charrange-tester.cpp
	belr-literal-tester.cpp
	belr-recognizerpointer-tester.cpp
	belr-basicgrammar-tester.cpp
	belr-vcardgrammar-tester.cpp
	belr-sipgrammar-tester.cpp
)

bc_apply_compile_flags(SOURCE_FILES_CXX STRICT_OPTIONS_CPP STRICT_OPTIONS_CXX)

add_executable(belr_tester ${SOURCE_FILES_CXX} ${HEADER_FILES_CXX})
set_target_properties(belr_tester PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(belr_tester PUBLIC ${BCTOOLBOX_TESTER_INCLUDE_DIRS})
target_link_libraries(belr_tester ${BELR_LIBRARIES_FOR_TESTER} ${BCTOOLBOX_TESTER_LIBRARIES})

if(APPLE)
	set_target_properties(belr_tester PROPERTIES LINK_FLAGS "-stdlib=libc++")
endif()
if(NOT IOS)
	install(TARGETS belr_tester
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
	)
endif()
install(FILES ${GRAMMAR_FILES} DESTINATION "${CMAKE_INSTALL_DATADIR}/belr_tester/grammars")