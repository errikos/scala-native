cmake_minimum_required(VERSION 3.19)

add_library(immix-isolates
        datastructures/BlockList.c
        datastructures/BlockList.h
        datastructures/Bytemap.c
        datastructures/Bytemap.h
        datastructures/Stack.c
        datastructures/Stack.h
        metadata/BlockMeta.h
        metadata/LineMeta.h
        metadata/ObjectMeta.h
        Allocator.c
        Allocator.h
        Block.c
        Block.h
        BlockAllocator.c
        BlockAllocator.h
        Constants.h
        Heap.c
        Heap.h
        ImmixGC.c
        LargeAllocator.c
        LargeAllocator.h
        Marker.c
        Marker.h
        Object.c
        Object.h
        Settings.c
        Settings.h
        State.c
        State.h
        Stats.c
        Stats.h)

target_include_directories(immix-isolates
        PRIVATE ../immix_commix)

add_executable(immix-isolates-test
        munit/munit.c
        munit/munit.h
        munit/main.c
        munit/tests/test-settings.c
        munit/tests/test-sample.c)

target_link_libraries(immix-isolates-test
        immix-isolates)

target_include_directories(immix-isolates-test
        PRIVATE munit
        PRIVATE .
        PRIVATE ../immix_commix)

