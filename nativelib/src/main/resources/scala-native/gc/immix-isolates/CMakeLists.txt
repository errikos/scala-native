cmake_minimum_required(VERSION 3.19)

add_compile_options(-DREACTIVE_ISOLATES)

add_library(immix-isolates
        datastructures/BinaryTree.c
        datastructures/BinaryTree.h
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
        Stats.h ImmixGC.h)

target_include_directories(immix-isolates
        PRIVATE ../immix_commix)

add_executable(immix-isolates-test
        test/munit/munit.c
        test/munit/munit.h
        test/main.c
        test/tests/test-sample.c
        test/tests/test-settings.c
        test/tests/test-btree.c
        test/tests/test-gc)

target_link_libraries(immix-isolates-test
        immix-isolates)

target_include_directories(immix-isolates-test
        PRIVATE test/munit
        PRIVATE .
        PRIVATE ../immix_commix)

