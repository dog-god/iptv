/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#include "config.h"
#include "RenderTheme.h"

#include "CSSValueKeywords.h"
#include "FileSystem.h"
#include "Frame.h"
#include "FrameView.h"
#include "GraphicsContext.h"
#include "NotImplemented.h"
#include "PaintInfo.h"
#include "Page.h"
#include "RenderBox.h"
#include "RenderObject.h"
#include "RenderProgress.h"
#include "RenderSlider.h"
#include <wtf/text/CString.h>

namespace WebCore {

class RenderThemeArmite : public RenderTheme {
     private:
        RenderThemeArmite(Page*);    
        ~RenderThemeArmite();

     public:
        static PassRefPtr<RenderTheme> create(Page*);
        virtual void systemFont(int cssValueId, FontDescription&) const;
        virtual String extraDefaultStyleSheet();

#if ENABLE(DATALIST_ELEMENT)
        virtual IntSize sliderTickSize() const OVERRIDE;
        virtual int sliderTickOffsetFromTrackCenter() const OVERRIDE;
        virtual LayoutUnit sliderTickSnappingThreshold() const OVERRIDE;
        virtual bool supportsDataListUI(const AtomicString&) const OVERRIDE;
        virtual bool paintSliderTrack(RenderObject*, const PaintInfo&, const IntRect&);
#endif
     private:
        Page *m_page;

};

static const char *extraDefaultStyleSheetString = NULL;
void setExtraDefaultStyleSheetString(const char *str)
{
    extraDefaultStyleSheetString = str;
}

String RenderThemeArmite::extraDefaultStyleSheet()
{
    if (extraDefaultStyleSheetString)
        return String::fromUTF8(extraDefaultStyleSheetString);
    return String();
}

void RenderThemeArmite::systemFont(int propId, FontDescription& fontDescription) const
{
    DEFINE_STATIC_LOCAL(String, fontFace, ("Sans"));

    fontDescription.firstFamily().setFamily(fontFace);
    fontDescription.setSpecifiedSize(16.0f);
    fontDescription.setIsAbsoluteSize(true);
    fontDescription.setGenericFamily(FontDescription::NoFamily);
    fontDescription.setWeight(FontWeightNormal);
    fontDescription.setItalic(false);
}

RenderThemeArmite::RenderThemeArmite(Page *page)
    :m_page(page)
{
}

RenderThemeArmite::~RenderThemeArmite()
{
    m_page = NULL;
}

PassRefPtr<RenderTheme> RenderThemeArmite::create(Page* page)
{
    return adoptRef(new RenderThemeArmite(page));
}

PassRefPtr<RenderTheme> RenderTheme::themeForPage(Page* page)
{
     if (page)
        return RenderThemeArmite::create(page);

     static RenderTheme* fallback = RenderThemeArmite::create(0).leakRef();
     return fallback;
}

#if ENABLE(DATALIST_ELEMENT)
IntSize RenderThemeArmite::sliderTickSize() const
{
    return IntSize(1, 6);
}

int RenderThemeArmite::sliderTickOffsetFromTrackCenter() const
{
    static const int sliderTickOffset = -12;

    return sliderTickOffset;
}

LayoutUnit RenderThemeArmite::sliderTickSnappingThreshold() const
{
    return 5;
}

bool RenderThemeArmite::supportsDataListUI(const AtomicString& type) const
{
    return true;
}

bool RenderThemeArmite::paintSliderTrack(RenderObject* object, const PaintInfo& info, const IntRect& rect)
{
    paintSliderTicks(object, info, rect);
    return false;
}
#endif

}



