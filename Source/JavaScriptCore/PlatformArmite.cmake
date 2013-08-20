LIST(APPEND JavaScriptCore_SOURCES
    jit/ExecutableAllocatorFixedVMPool.cpp
    jit/ExecutableAllocator.cpp
)

LIST(APPEND JavaScriptCore_INCLUDE_DIRECTORIES
    ${ICU_INCLUDE_DIRS}
)

