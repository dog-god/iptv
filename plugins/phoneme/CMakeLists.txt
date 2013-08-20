##################################################
# Add sources for phoneme plugin.
##################################################

set(PLUGIN_PHONEME_DIR ${PROJECT_SOURCE_DIR}/plugins/phoneme)
set(PHONEME_ADVANCED_DIR ${PROJECT_SOURCE_DIR}/advanced)

include_directories(${PLUGIN_PHONEME_DIR}/include
    ${PHONEME_ADVANCED_DIR}/cdc/src
    ${PHONEME_ADVANCED_DIR}/cdc/src/share
    ${PHONEME_ADVANCED_DIR}/cdc/src/linux
    ${PHONEME_ADVANCED_DIR}/cdc/src/linux-arm
    ${PHONEME_ADVANCED_DIR}/cdc/src/arm
    ${PHONEME_ADVANCED_DIR}/cdc/build/linux-arm-generic
)

list(APPEND PLUGIN_PHONEME_SRC
    ${PLUGIN_TEMPLATE_SRC}
    ${PLUGIN_PHONEME_DIR}/plugin.cpp
    ${PLUGIN_PHONEME_DIR}/advanced.cpp
)

link_directories(${PHONEME_ADVANCED_DIR}/cdc/build/linux-arm-generic/bin)
add_library(Phoneme SHARED ${PLUGIN_PHONEME_SRC})
target_link_libraries(Phoneme -ljnigraphics -llog -lm -pthread -lcvm)





