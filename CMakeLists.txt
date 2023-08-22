cmake_minimum_required(VERSION 3.24)
project(CreedCortex VERSION 0.1.0 LANGUAGES CXX)
option(LINK_DATASETS "Whether to link the datasets directly to the library" ON)
option(BUILD_TESTS "Whether to build test applications" ON)
find_package(xtensor REQUIRED)
find_package(xtensor-blas REQUIRED)
add_library(CreedCortex SHARED
    "src/CreedLayer.cpp"
    "src/CreedDense.cpp"
    "src/CreedActivations.cpp"
    "src/CreedSequential.cpp"
    "src/CreedMSE.cpp"
    "src/CreedSimpleDerivative.cpp"
    "src/CreedSGD.cpp"
    "src/CreedAccuracy.cpp"
    "src/CreedMNIST.cpp"
    "src/CreedStandardDistribution.cpp"
    "src/CreedGlorot.cpp"
    "src/CreedSGDMomentum.cpp"
    "src/CreedCrossEntropy.cpp"
    "src/CreedAdam.cpp"
)
target_link_libraries(CreedCortex PUBLIC xtensor xtensor-blas)
install(FILES "datasets/mnist.csv" DESTINATION share)
if(LINK_DATASETS)
    message("Linking datasets")
    function(generate_elf_from_binary INPUT_BINARY TARGET)
        execute_process(
            COMMAND dirname ${INPUT_BINARY}.o
            OUTPUT_VARIABLE DIRECTORY
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        MESSAGE("Making directory ${DIRECTORY}")
        add_custom_command(OUTPUT ${INPUT_BINARY}.o
            COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/${DIRECTORY} &&
                ld -r -b binary -o ${CMAKE_CURRENT_BINARY_DIR}/${INPUT_BINARY}.o ${INPUT_BINARY}
            COMMAND objcopy --rename-section .data=.rodata,alloc,load,readonly,data,contents
                ${CMAKE_CURRENT_BINARY_DIR}/${INPUT_BINARY}.o ${CMAKE_CURRENT_BINARY_DIR}/${INPUT_BINARY}.o)
        target_sources(${TARGET} PRIVATE ${INPUT_BINARY}.o)
    endfunction()
    generate_elf_from_binary("datasets/mnist.csv" CreedCortex)
endif()
if(BUILD_TESTS)
    message("Building tests")
    enable_testing()
    add_executable(BasicTest "test/BasicTest.cpp")
    add_test(NAME BasicTest COMMAND BasicTest)
    target_link_libraries(BasicTest PUBLIC CreedCortex)
    add_executable(MNIST "test/MNIST.cpp")
    add_test(NAME MNIST COMMAND MNIST)
    target_link_libraries(MNIST PUBLIC CreedCortex)
endif()
target_include_directories(CreedCortex PUBLIC "include")