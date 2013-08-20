##################################################
# Add sources for demo plugin.
##################################################

set(PLUGIN_IPANEL_DIR ${PROJECT_SOURCE_DIR}/plugins/iPanel)

include_directories(${PLUGIN_DEMO_DIR}/include)

list(APPEND PLUGIN_IPANEL_SRC
    ${PLUGIN_TEMPLATE_SRC}
    ${PLUGIN_IPANEL_DIR}/plugin.cpp
)

add_library(iPanel SHARED ${PLUGIN_IPANEL_SRC})
target_link_libraries(iPanel -llog)





