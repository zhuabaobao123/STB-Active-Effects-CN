cmake_minimum_required(VERSION 3.21)

# ---- Cache build vars ----
option(COPY_BUILD "Copy the build output to the Skyrim directory." TRUE)
macro(set_from_environment VARIABLE)
	if (NOT DEFINED ${VARIABLE} AND DEFINED ENV{${VARIABLE}})
		set(${VARIABLE} $ENV{${VARIABLE}})
	endif ()
endmacro()

# ---- Vcpkg check ----
set_from_environment(VCPKG_ROOT)
if (NOT DEFINED VCPKG_ROOT)
	message(
		FATAL_ERROR
		"Variable VCPKG_ROOT is not set."
	)
endif ()

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(
		FATAL_ERROR
			"In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
	)
endif()

# CommonLibSSE-NG (alandtse, ng) requires the dynamic CRT (static-md triplet).
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL" CACHE STRING "")

# ---- Project ----

project(
	STB_ActiveEffects
	VERSION 1.0.0
	LANGUAGES CXX
)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.h.in
	${CMAKE_CURRENT_BINARY_DIR}/include/Version.h
	@ONLY
)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.rc.in
	${CMAKE_CURRENT_BINARY_DIR}/version.rc
	@ONLY
)

# ---- Globals ----

if (MSVC)
	add_compile_definitions(
		_UNICODE
	)

	if (NOT ${CMAKE_GENERATOR} STREQUAL "Ninja")
		add_compile_options(
			/MP	# Build with Multiple Processes
		)
	endif ()
endif ()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF)

# ---- Dependencies ----

# CommonLibSSE-NG (alandtse fork, ng branch) - supports Skyrim 1.7.104 / Address Library v13.
set(COMMONLIBSSE_PATH "E:/CommonLibSSE-NG-alandtse" CACHE PATH "Path to CommonLibSSE-NG source tree")
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory("${COMMONLIBSSE_PATH}" CommonLibSSE EXCLUDE_FROM_ALL)

# add_commonlibsse_plugin() is defined in CommonLibSSE's cmake helper. function() definitions
# do not cross the subdirectory scope, so include it into this scope to call it here.
set(CommonLibSSE_INCLUDE_DIRS
	"${COMMONLIBSSE_PATH}/include"
	"${COMMONLIBSSE_PATH}/extern/openvr/headers"
)
include("${COMMONLIBSSE_PATH}/cmake/CommonLibSSE.cmake")

find_package(spdlog REQUIRED CONFIG)
find_package(nlohmann_json REQUIRED CONFIG)
find_path(SIMPLEINI_INCLUDE_DIRS "SimpleIni.h" REQUIRED)

# ---- Add source files ----

set(SOURCES
	src/main.cpp
        src/WidgetActiveEffects.cpp
        src/WidgetActiveEffects.h
        src/MenuHandler.cpp
        src/MenuHandler.h
        src/Localization.cpp
        src/Localization.h
        src/SKSEMenuFramework.h
	src/PCH.h
)

source_group(
	TREE
		${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		${SOURCES}
)

source_group(
	TREE
		${CMAKE_CURRENT_BINARY_DIR}
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/include/Version.h
)

# ---- Create DLL ----

# add_commonlibsse_plugin auto-generates SKSEPlugin_Version/Query (cross-runtime safe).
add_commonlibsse_plugin(
	${PROJECT_NAME}
	NAME "STB_ActiveEffects"
	AUTHOR "STB"
	VERSION 1.0.0
	USE_ADDRESS_LIBRARY
	SOURCES
		${SOURCES}
		${CMAKE_CURRENT_BINARY_DIR}/include/Version.h
		${CMAKE_CURRENT_BINARY_DIR}/version.rc
)

target_compile_features(
	${PROJECT_NAME}
	PRIVATE
		cxx_std_23
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${SIMPLEINI_INCLUDE_DIRS}
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		spdlog::spdlog
		nlohmann_json::nlohmann_json
)

if (MSVC)
	target_compile_options(
		${PROJECT_NAME}
		PRIVATE
			/utf-8	# Set Source and Executable character sets to UTF-8
			/Zi	# Debug Information Format

			/permissive-	# Standards conformance

			/Zc:alignedNew	# C++17 over-aligned allocation
			/Zc:auto	# Deduce Variable Type
			/Zc:char8_t
			/Zc:__cplusplus	# Enable updated __cplusplus macro
			/Zc:externC
			/Zc:externConstexpr	# Enable extern constexpr variables
			/Zc:forScope	# Force Conformance in for Loop Scope
			/Zc:hiddenFriend
			/Zc:implicitNoexcept	# Implicit Exception Specifiers
			/Zc:lambda
			/Zc:noexceptTypes	# C++17 noexcept rules
			/Zc:preprocessor	# Enable preprocessor conformance mode
			/Zc:referenceBinding	# Enforce reference binding rules
			/Zc:rvalueCast	# Enforce type conversion rules
			/Zc:sizedDealloc	# Enable Global Sized Deallocation Functions
			/Zc:strictStrings	# Disable string literal type conversion
			/Zc:ternary	# Enforce conditional operator rules
			/Zc:threadSafeInit	# Thread-safe Local Static Initialization
			/Zc:tlsGuards
			/Zc:trigraphs	# Trigraphs Substitution
			/Zc:wchar_t	# wchar_t Is Native Type

			/external:anglebrackets
			/external:W0

			/W4	# Warning level
			/WX	# Warning level (warnings are errors)

			"$<$<CONFIG:RELEASE>:/Zc:inline;/JMC-;/Ob3>"
	)

	target_link_options(
		${PROJECT_NAME}
		PRIVATE
			/WX	# Treat Linker Warnings as Errors

			"$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
			"$<$<CONFIG:RELEASE>:/INCREMENTAL:NO;/OPT:REF;/OPT:ICF;/DEBUG:FULL>"
	)
endif ()

target_precompile_headers(
	${PROJECT_NAME}
	PRIVATE
		src/PCH.h
)
