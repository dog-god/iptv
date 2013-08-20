##################################################
# Add sources for demo plugin.
##################################################

set(PLUGIN_DEMO_DIR ${PROJECT_SOURCE_DIR}/plugins/Navigation)

include_directories(${PLUGIN_DEMO_DIR}/include)

list(APPEND PLUGIN_DEMO_SRC
    ${PLUGIN_TEMPLATE_SRC}
    ${PLUGIN_DEMO_DIR}/plugin.cpp
)

add_library(Navigation SHARED ${PLUGIN_DEMO_SRC})
target_link_libraries(Navigation -llog)





