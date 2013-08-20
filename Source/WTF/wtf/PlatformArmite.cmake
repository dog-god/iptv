LIST(APPEND WTF_SOURCES
    armite/MainThreadArmite.cpp
    OSAllocatorPosix.cpp
    ThreadIdentifierDataPthreads.cpp
    ThreadingPthreads.cpp
    unicode/icu/CollatorICU.cpp
    url/api/ParsedURL.cpp
    url/api/URLString.cpp
    url/src/URLCanonEtc.cpp
    url/src/URLCanonFilesystemurl.cpp
    url/src/URLCanonFileurl.cpp
    url/src/URLCanonHost.cpp
    url/src/URLCanonICU.cpp
    url/src/URLCanonInternal.cpp
    url/src/URLCanonIP.cpp
    url/src/URLCanonMailto.cpp
    url/src/URLCanonPath.cpp
    url/src/URLCanonPathurl.cpp
    url/src/URLCanonQuery.cpp
    url/src/URLCanonRelative.cpp
    url/src/URLCanonStdURL.cpp
    url/src/URLCharacterTypes.cpp
    url/src/URLParse.cpp
    url/src/URLParseFile.cpp
    url/src/URLSegments.cpp
    url/src/URLUtil.cpp
)

LIST(APPEND WTF_INCLUDE_DIRECTORIES
    ${ICU_INCLUDE_DIRS}
    unicode/
    url/src/
    url/api/
)



