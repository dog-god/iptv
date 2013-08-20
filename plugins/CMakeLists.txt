################################################################################
# Copyright (c) 2012 by armite
################################################################################

set(PLUGIN_TEMPLATE_DIR ${PROJECT_SOURCE_DIR}/plugins/template)
include_directories(
    ${PROJECT_SOURCE_DIR}/Source/WebCore/plugins
    ${PLUGIN_TEMPLATE_DIR}
)

set(PLUGIN_TEMPLATE_SRC
    ${PLUGIN_TEMPLATE_DIR}/np_entry.cpp
    ${PLUGIN_TEMPLATE_DIR}/npn_gate.cpp
    ${PLUGIN_TEMPLATE_DIR}/npp_gate.cpp
    ${PLUGIN_TEMPLATE_DIR}/object.cpp
    ${PLUGIN_TEMPLATE_DIR}/pluginbase.cpp
)

add_definitions(-DXP_UNIX)
add_definitions(-DWTF_PLATFORM_ARMITE)

option(ARMITE_PLUGIN_DEMO "Need To Compile Demo Plugin" OFF)
if(ARMITE_PLUGIN_DEMO)
    add_subdirectory(demo)
endif()

option(ARMITE_PLUGIN_IPANEL "Need To Compile iPanel Plugin" ON)
if(ARMITE_PLUGIN_IPANEL)
    add_subdirectory(iPanel)
endif()

option(ARMITE_PLUGIN_Authentication "Need To Compile Authentication Plugin" ON)
if(ARMITE_PLUGIN_Authentication)
    add_subdirectory(Authentication)
endif()

option(ARMITE_PLUGIN_MediaPlayer "Need To Compile MediaPlayer Plugin" ON)
if(ARMITE_PLUGIN_MediaPlayer)
    add_subdirectory(MediaPlayer)
endif()

option(ARMITE_PLUGIN_Navigation "Need To Compile Navigation Plugin" ON)
if(ARMITE_PLUGIN_Navigation)
    add_subdirectory(Navigation)
endif()

option(ARMITE_PLUGIN_Utility "Need To Compile Utility Plugin" ON)
if(ARMITE_PLUGIN_Utility)
    add_subdirectory(Utility)
endif()

option(ARMITE_PLUGIN_J2ME "Need To Compile J2ME Plugin" ON)
if(ARMITE_PLUGIN_J2ME)
    add_subdirectory(phoneme)
endif()



