cmake_minimum_required(VERSION 3.19)

include_directories(
        ../gc/shared
        ../gc/immix-isolates
        ../gc/immix_commix)

add_library(isolates
        IsolateLayer.c
        IsolateLayer.h
        )

add_executable(isolates-test
        test/munit/munit.c
        test/munit/munit.h
        test/tests/test-sample.c
        test/main.c)

target_include_directories(isolates-test
        PRIVATE test/munit
        PRIVATE .)
