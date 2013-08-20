LIST(APPEND WebCore_INCLUDE_DIRECTORIES
  "${JAVASCRIPTCORE_DIR}/wtf/text"
  "${WEBCORE_DIR}/platform/armite"
  "${WEBCORE_DIR}/platform/text/armite"
  "${WEBCORE_DIR}/platform/graphics/armite"
  "${WEBCORE_DIR}/page/armite"
  "${WEBCORE_DIR}/accessibility/armite"
  "${WEBKIT_DIR}/armite/WebCoreSupport"
  "${WEBKIT_DIR}/armite"
  "${DERIVED_SOURCES_DIR}"
)

LIST(APPEND WebCore_SOURCES
  page/armite/DragControllerArmite.cpp
  page/armite/EventHandlerArmite.cpp
  platform/Cursor.cpp
  platform/KURLWTFURL.cpp
  platform/armite/CursorArmite.cpp
  platform/armite/ClipboardArmite.cpp
  platform/armite/DragDataArmite.cpp
  platform/armite/DragImageArmite.cpp
  platform/armite/EventLoopArmite.cpp
  platform/armite/FileSystemArmite.cpp
  platform/armite/KURLArmite.cpp
  platform/armite/LanguageArmite.cpp
  platform/armite/LocalizedStringsArmite.cpp
  platform/armite/MIMETypeRegistryArmite.cpp
  platform/armite/PasteboardArmite.cpp
  platform/armite/PlatformKeyboardEventArmite.cpp
  platform/armite/PlatformMouseEventArmite.cpp
  platform/armite/PlatformScreenArmite.cpp
  platform/armite/RenderThemeArmite.cpp
  platform/armite/RunLoopArmite.cpp
  platform/armite/ScrollbarThemeArmite.cpp
  platform/armite/SharedBufferArmite.cpp
  platform/armite/SharedTimerArmite.cpp
  platform/armite/SoundArmite.cpp
  platform/armite/TemporaryLinkStubs.cpp
  platform/armite/WidgetArmite.cpp
  platform/graphics/ImageSource.cpp
  platform/graphics/armite/IconArmite.cpp
  platform/graphics/armite/ImageArmite.cpp
  platform/graphics/armite/ImageArmite.cpp
  platform/graphics/armite/IntRectArmite.cpp
  platform/image-decoders/ImageDecoder.cpp
  platform/image-decoders/bmp/BMPImageDecoder.cpp
  platform/image-decoders/bmp/BMPImageReader.cpp
  platform/image-decoders/gif/GIFImageDecoder.cpp
  platform/image-decoders/gif/GIFImageReader.cpp
  platform/image-decoders/ico/ICOImageDecoder.cpp
  platform/image-decoders/jpeg/JPEGImageDecoder.cpp
  platform/image-decoders/png/PNGImageDecoder.cpp
  platform/image-decoders/webp/WEBPImageDecoder.cpp
  platform/posix/FileSystemPOSIX.cpp
  platform/text/armite/TextBreakIteratorInternalICUArmite.cpp
  plugins/PluginData.cpp
  plugins/PluginPackage.cpp
  plugins/PluginView.cpp
  plugins/PluginDatabase.cpp
  platform/armite/PluginDataArmite.cpp
  platform/armite/PluginPackageArmite.cpp
  platform/armite/PluginViewArmite.cpp
)

LIST(APPEND WebCore_INCLUDE_DIRECTORIES
  "${WEBCORE_DIR}/platform/cairo"
  "${WEBCORE_DIR}/platform/graphics/cairo"
)
LIST(APPEND WebCore_SOURCES
  platform/graphics/cairo/BitmapImageCairo.cpp
  platform/graphics/cairo/CairoUtilities.cpp
  platform/graphics/cairo/FontCairo.cpp
  platform/graphics/cairo/GradientCairo.cpp
  platform/graphics/cairo/GraphicsContextCairo.cpp
  platform/graphics/cairo/ImageBufferCairo.cpp
  platform/graphics/cairo/ImageCairo.cpp
  platform/graphics/cairo/NativeImageCairo.cpp
  platform/graphics/cairo/OwnPtrCairo.cpp
  platform/graphics/cairo/PathCairo.cpp
  platform/graphics/cairo/PatternCairo.cpp
  platform/graphics/cairo/PlatformContextCairo.cpp
  platform/graphics/cairo/PlatformPathCairo.cpp
  platform/graphics/cairo/RefPtrCairo.cpp
  platform/graphics/cairo/TransformationMatrixCairo.cpp

  platform/image-decoders/cairo/ImageDecoderCairo.cpp
)

LIST(APPEND WebCore_INCLUDE_DIRECTORIES
  "${WEBCORE_DIR}/platform/graphics/freetype"
)
LIST(APPEND WebCore_SOURCES
  platform/graphics/WOFFFileFormat.cpp
  platform/graphics/armite/FontArmite.cpp
  platform/graphics/freetype/FontCacheFreeType.cpp
  platform/graphics/freetype/FontCustomPlatformDataFreeType.cpp
  platform/graphics/freetype/FontPlatformDataFreeType.cpp
  platform/graphics/freetype/GlyphPageTreeNodeFreeType.cpp
  platform/graphics/freetype/SimpleFontDataFreeType.cpp
)
LIST(APPEND WebCore_LIBRARIES
  ${ZLIB_LIBRARIES}
)

LIST(APPEND WebCore_INCLUDE_DIRECTORIES
  "${WEBCORE_DIR}/platform/network/curl"
)
LIST(APPEND WebCore_SOURCES
  platform/network/curl/CookieJarCurl.cpp
  platform/network/curl/CredentialStorageCurl.cpp
  platform/network/curl/DNSCurl.cpp
  platform/network/curl/FormDataStreamCurl.cpp
  platform/network/curl/ProxyServerCurl.cpp
  platform/network/curl/ResourceHandleCurl.cpp
  platform/network/curl/ResourceHandleManager.cpp
  platform/network/curl/SocketStreamHandleCurl.cpp
)

LIST(APPEND WebCore_SOURCES
  editing/SmartReplaceICU.cpp
  platform/text/TextEncodingDetectorICU.cpp
  platform/text/TextBreakIteratorICU.cpp
  platform/text/TextCodecICU.cpp
)

LIST(APPEND WebCore_INCLUDE_DIRECTORIES
  ${FONTCONFIG_INCLUDE_DIR}
  ${SQLITE_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${JPEG_INCLUDE_DIR}
  ${PNG_INCLUDE_DIRS}
  ${ICU_INCLUDE_DIRS}
  ${CAIRO_INCLUDE_DIRS}
  ${CURL_INCLUDE_DIRS}
  ${FREETYPE_INCLUDE_DIRS}
)

ADD_DEFINITIONS(-DWTF_USE_CROSS_PLATFORM_CONTEXT_MENUS=0)
