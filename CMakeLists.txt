# Copyright 2026, Cinar, A. L.
# SPDX-License-Identifier: GPL-3.0-only

cmake_minimum_required(VERSION 3.21)

if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.27")
	cmake_policy(SET CMP0135 NEW)
endif()

project(
	template_cpp_project
	VERSION 1.0.0 
	LANGUAGES CXX
)

# dependencies
Include(FetchContent)

set(matrix_rw_VERSION 1.2.1) # matrix_rw, used for testing

if(PROJECT_IS_TOP_LEVEL)
	FetchContent_Declare(
		matrix_rw 
		URL https://github.com/cinaral/matrix_rw/releases/download/v${matrix_rw_VERSION}/src.zip
	)
	FetchContent_MakeAvailable(matrix_rw)
endif()

find_package(Eigen3 3.3 REQUIRED)



if(PROJECT_IS_TOP_LEVEL)
	option(DEBUG_BUILD "Build everything in debug mode" ON)
	option(BUILD_TESTS "Build tests" ON)
	option(BUILD_EXAMPLES "Build examples" ON)
	option(BUILD_BENCHMARKS "Build benchmarks" ON)
	option(USE_SINGLE_PRECISION "Use single precision floats" OFF)

	# where to look for the project header and source files
	set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
	set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
	set(TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)
	set(EXAMPLE_DIR ${CMAKE_CURRENT_LIST_DIR}/examples)
	set(BENCHMARK_DIR ${CMAKE_CURRENT_LIST_DIR}/benchmarks)

	# tests, examples, benchmarks to compile
	set(TEST_NAMES
		example_test
	)
	set(EXAMPLE_NAMES
		example
	)
	set(BENCHMARK_NAMES
	)

	# source files
	file (GLOB_RECURSE CPP_PROJECT_TEMPLATE_SRC CONFIGURE_DEPENDS "${SRC_DIR}/cpp_project_template/*.cpp")

	# files to package
	set(PACKAGE_FILES 
		include/${PROJECT_NAME}/
		include/${PROJECT_NAME}.hpp 
		CMakeLists.txt 
		LICENSE
	)

	# set up output directories
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
	file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)

	# project compile options
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF)

	add_compile_options(
		-fdiagnostics-color=always # colored debug output
		-fmessage-length=0 # disable line wrapping (default=72 char) 
		-pipe # avoid temporary files
	)

	# warnings:
	# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
	# https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html
	add_compile_options(
		-Wall # all warnings
		-Wextra # more warnings
		-Wpedantic # MORE warnings
		-Wconversion # warn for implicit conversions 
		-Wsign-conversion # warn for implicity conversion of signed/unsigned ints
		-Wcast-qual # "Warn whenever a pointer is cast so as to remove a type qualifier from the target type"
		-Wformat=2 # check calls to printf and scanf etc make sense (equivalent to -Wformat -Wformat-nonliteral -Wformat-security -Wformat-y2k)
		-Wundef # warn for undefined identifiers in #if directives
		-Werror=float-equal # turn float equality comparisons to errors
		-Wshadow # warn for all instances of shadowing of another variable, parameter, type, class member
		-Wcast-align # warn for pointer cast alignment mismatch
		-Wunused # warn for unused (-Wall implies this already)
		-Wnull-dereference # warn for undefined dereferencing a null pointer
		-Wdouble-promotion # warn if float is implicitly promoted to double
		-Wimplicit-fallthrough # warn for switch case fallthrough
		-Wextra-semi # warn about redundant semicolons
		-Woverloaded-virtual # warn when a function declaration hides virtual functions from a base class
		-Wnon-virtual-dtor # warn when a class is possible to but unsafe to delete and instance of derived class
		-Wold-style-cast # warn if C-style cast to non-void type is used in C++
	)

	if(DEBUG_BUILD)
		add_compile_options(
			-O0 # no optimization, -Og may work better with some debuggers
			-g # debug symbols
			-grecord-gcc-switches # store compiler flags in debugging information
		)
	else()
		add_compile_options(
			-O3 # release optimization
			-fhardened # equivalent to: (-D_FORTIFY_SOURCE=3	-D_GLIBCXX_ASSERTIONS -ftrivial-auto-var-init=zero -fPIE  -pie  -Wl,-z,relro,-z,now				-fstack-protector-strong -fstack-clash-protection -fcf-protection=full (x86 GNU/Linux only)) https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html 	
			)
	endif()

	if(USE_SINGLE_PRECISION)
		add_compile_options(-DUSE_SINGLE_PRECISION) # use single precision floats
	endif()

	#***************#
	#* Executables *#
	#***************#
	add_executable(
		main
		${CPP_PROJECT_TEMPLATE_SRC}					
	)
	target_include_directories(
		main PRIVATE 
		${INCLUDE_DIR}
	)
	target_compile_options(
		main PRIVATE
	)
	target_link_libraries(main PRIVATE 
		Eigen3::Eigen
	)
	
	#***********#
	#* Testing *#
	#***********#
	if(BUILD_TESTS)
		enable_testing()

		foreach(ELEMENT ${TEST_NAMES})
			add_executable(
				${ELEMENT}
				${TEST_DIR}/${ELEMENT}.cpp						
			)
			target_include_directories(
				${ELEMENT} PRIVATE 
				${INCLUDE_DIR}
				${matrix_rw_SOURCE_DIR}/include
			)
			target_compile_options(
				${ELEMENT} PRIVATE
			)
			add_test(
				NAME ${ELEMENT} 
				COMMAND ${ELEMENT}
				WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
			)
		endforeach(ELEMENT ${TEST_NAMES})
	endif()

	#************#
	#* Examples *#
	#************#
	if(BUILD_EXAMPLES)
		foreach(ELEMENT ${EXAMPLE_NAMES})
			add_executable(
				${ELEMENT}
				${EXAMPLE_DIR}/${ELEMENT}.cpp						
			)
			target_include_directories(
				${ELEMENT} PRIVATE 
				${INCLUDE_DIR}
				${matrix_rw_SOURCE_DIR}/include
			)
			target_compile_options(
				${ELEMENT} PRIVATE
			)
		endforeach(ELEMENT ${EXAMPLE_NAMES})
	endif()

	#*************#
	#* Benchmark *#
	#*************#
	if(BUILD_BENCHMARKS)
		foreach(ELEMENT ${BENCHMARK_NAMES})
			add_executable(
				${ELEMENT}
				${BENCHMARK_DIR}/${ELEMENT}.cpp
			)
			target_include_directories(
				${ELEMENT} PRIVATE 
				${INCLUDE_DIR}	
			)
			target_compile_options(
				${ELEMENT} PRIVATE
				-O3 # optimization level, alternative: -Ofast (turns on ffast-math etc.)
				-m64 # x64
				-mavx2 # enable avx2
			)
		endforeach(ELEMENT ${BENCHMARK_NAMES})
	endif()

	#************************#
	#* Packaged source code *#
	#************************#
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/src.zip
		COMMAND ${CMAKE_COMMAND} -E tar c ${CMAKE_CURRENT_BINARY_DIR}/src.zip --format=zip -- ${PACKAGE_FILES}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		DEPENDS ${PACKAGE_FILES}
	)
	add_custom_target(
		src_package 
		DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/src.zip
	)
endif()
