LIST(APPEND WebKit_INCLUDE_DIRECTORIES
    "${JAVASCRIPTCORE_DIR}/wtf/text"
    "${WEBKIT_DIR}/armite"
    "${WEBKIT_DIR}/armite/Platform"
    "${WEBKIT_DIR}/armite/WebCoreSupport"
    "${WEBCORE_DIR}/platform/armite"
    "${WEBCORE_DIR}/platform/graphics/cairo"
    "${WEBCORE_DIR}/platform/graphics/freetype"
    ${CAIRO_INCLUDE_DIRS}
    ${LIBXML2_INCLUDE_DIR}
    ${SQLITE_INCLUDE_DIR}
    ${CURL_INCLUDE_DIRS}
    ${ICU_INCLUDE_DIRS}
)

LIST(APPEND WebKit_SOURCES
    armite/WebCoreSupport/ChromeClientArmite.cpp
    armite/WebCoreSupport/EditorClientArmite.cpp
    armite/WebCoreSupport/FrameLoaderClientArmite.cpp
    armite/WebView.cpp
    armite/WebViewPrivate.cpp
    armite/WebFrame.cpp
    armite/WebUtils.cpp
)

#LIST(APPEND WebKit_LIBRARIES "-llog -lz -lm -ldl -lstdc++ -L${THIRDPARTY_DIR}/libs -Wl,-whole-archive -lcairo -lcurl -ljpeg -lpng15 -lxml2 -lsqlite3 -lfreetype -lcares -lfontconfig -lpixman-1 -licuuc -licudata -licui18n -lsupc++ -Wl,-no-whole-archive")

LIST(APPEND WebKit_LIBRARIES "-lz -lm -ldl -lcairo -lcurl -ljpeg -lpng12 -lxml2 -lsqlite3 -lfreetype -lfontconfig -licuuc -licudata -licui18n -lxslt")




