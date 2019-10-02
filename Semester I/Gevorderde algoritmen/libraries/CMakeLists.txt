
set(SOURCE_FILES
    )

set(ADDITIONAL_INPUT_FILES
    )

set(TEST_SOURCE_FILES
    binaire-boom/binaireboom-test.cpp
    binaire-boom/binaireboom.h
    binaire-boom/richting.h
    btree/btree-test.cpp
    btree/btree.h
    chrono/chrono-simple-test.cpp
    chrono/chrono-simple.cpp
    chrono/chrono-simple.h
    csv/csv-test.cpp
    csv/csv.cpp
    csv/csv.h
    graaf/graaf-test.cpp
    graaf/graaf.h
    intstring/intstring.h
    kdtree/kdtree-test.cpp
    kdtree/kdtree.h
    kdtree/punt2d.h
    knuth-morris-pratt/kmp-test.cpp
    knuth-morris-pratt/kmp.h
    lgfloor/lgfloor-test.cpp
    lgfloor/lgfloor.h
    lijst/lijst-test.cpp
    lijst/lijst.h
    rood-zwarte-boom/rzboom-bu.h
    rood-zwarte-boom/rzboom-td.h
    rood-zwarte-boom/rzboom-test.cpp
    rood-zwarte-boom/rzboom.h
    schijf/schijf-test.cpp
    schijf/schijf.h
    sorteren/insertionsort.h
    sorteren/inversieteller-test.cpp
    sorteren/inversieteller.h
    sorteren/mergesort.h
    sorteren/optimized-mergesort.h
    sorteren/quicksort-test.cpp
    sorteren/quicksort.h
    sorteren/shellsort-test.cpp
    sorteren/shellsort.h
    sorteren/sorteermethode-test.cpp
    sorteren/sorteermethode.h
    sorteren/sortvector-test.cpp
    sorteren/sortvector.h
    sorteren/stlsort.h
    splayboom/splayboombottomup-test.cpp
    splayboom/splayboombottomup.h
    splayboom/splayboomtopdown-test.cpp
    splayboom/splayboomtopdown.h
    stringmetbits/stringmetbits-test.cpp
    stringmetbits/stringmetbits.h
    stroomnetwerken/stroomnetwerk.h
    stroomnetwerken/stroomnetwerk_test.cpp
    stroomnetwerken/stroomnetwerkgenerator.h
    stroomnetwerken/vergrotendpad.h
    stroomnetwerken/volgendpadzoeker.h
    stroomnetwerken/zoekers/grootstecapaciteitenpadzoeker.h
    stroomnetwerken/zoekers/kortstepadzoeker.h
    stroomnetwerken/zoekers/langpadzoeker.h
    woordstroom/woordstroom-test.cpp
    woordstroom/woordstroom.h
    )

set(ADDITIONAL_TEST_FILES
    woordstroom/test.txt
    )

set(GOOGLE_TEST_DIR
    external/googletest
    )

cmake_minimum_required(VERSION 3.14)
include(../tools/cmake/compile.cmake)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(external/json build_json)
target_link_libraries(${TEST_EXECUTABLE_NAME} nlohmann_json::nlohmann_json)
