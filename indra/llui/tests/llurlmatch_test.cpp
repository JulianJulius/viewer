/**
 * @file llurlmatch_test.cpp
 * @author Martin Reddy
 * @brief Unit tests for LLUrlMatch
 *
 * $LicenseInfo:firstyear=2009&license=viewerlgpl$
 * Second Life Viewer Source Code
 * Copyright (C) 2010, Linden Research, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation;
 * version 2.1 of the License only.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Linden Research, Inc., 945 Battery Street, San Francisco, CA  94111  USA
 * $/LicenseInfo$
 */

#include "linden_common.h"

#include "../llurlmatch.h"
#include "../llrender/lluiimage.h"
#include "../test/lldoctest.h"

// link seams

LLUIColor::LLUIColor()
    : mColorPtr(NULL)
{}

LLStyle::Params::Params()
{
}

LLUIImage::LLUIImage(const std::string& name, LLPointer<LLTexture> image)
{
}

LLUIImage::~LLUIImage()
{
}

//virtual
S32 LLUIImage::getWidth() const
{
    return 0;
}

//virtual
S32 LLUIImage::getHeight() const
{
    return 0;
}

namespace LLInitParam
{
    ParamValue<LLUIColor>::ParamValue(const LLUIColor& color)
    :   super_t(color)
    {}

    void ParamValue<LLUIColor>::updateValueFromBlock()
    {}

    void ParamValue<LLUIColor>::updateBlockFromValue(bool)
    {}

    bool ParamCompare<const LLFontGL*, false>::equals(const LLFontGL* a, const LLFontGL* b)
    {
        return false;
    }


    ParamValue<const LLFontGL*>::ParamValue(const LLFontGL* fontp)
    :   super_t(fontp)
    {}

    void ParamValue<const LLFontGL*>::updateValueFromBlock()
    {}

    void ParamValue<const LLFontGL*>::updateBlockFromValue(bool)
    {}

    void TypeValues<LLFontGL::HAlign>::declareValues()
    {}

    void TypeValues<LLFontGL::VAlign>::declareValues()
    {}

    void TypeValues<LLFontGL::ShadowType>::declareValues()
    {}

    void ParamValue<LLUIImage*>::updateValueFromBlock()
    {}

    void ParamValue<LLUIImage*>::updateBlockFromValue(bool)
    {}

    bool ParamCompare<LLUIImage*, false>::equals(
        LLUIImage* const &a,
        LLUIImage* const &b)
    {
        return false;
    }

    bool ParamCompare<LLUIColor, false>::equals(const LLUIColor &a, const LLUIColor &b)
    {
        return false;
    }

}

//static
LLFontGL* LLFontGL::getFontDefault()
{
    return NULL;
}


TEST_SUITE("LLUrlMatch") {

TEST_CASE("test_1")
{

        //
        // test the empty() method
        //
        LLUrlMatch match;
        CHECK_MESSAGE(match.empty(, "empty()"));

        match.setValues(0, 1, "http://secondlife.com", "", "Second Life", "", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(! match.empty(, "! empty()"));
    
}

TEST_CASE("test_2")
{

        //
        // test the getStart() method
        //
        LLUrlMatch match;
        CHECK_MESSAGE(match.getStart() == 0, "getStart() == 0");

        match.setValues(10, 20, "", "", "", "", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getStart() == 10, "getStart() == 10");
    
}

TEST_CASE("test_3")
{

        //
        // test the getEnd() method
        //
        LLUrlMatch match;
        CHECK_MESSAGE(match.getEnd() == 0, "getEnd() == 0");

        match.setValues(10, 20, "", "", "", "", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getEnd() == 20, "getEnd() == 20");
    
}

TEST_CASE("test_4")
{

        //
        // test the getUrl() method
        //
        LLUrlMatch match;
        CHECK_MESSAGE(match.getUrl() == "", "getUrl() == ''");

        match.setValues(10, 20, "http://slurl.com/", "", "", "", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getUrl() == "http://slurl.com/", "getUrl() == 'http://slurl.com/'");

        match.setValues(10, 20, "", "", "", "", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getUrl() == "", "getUrl() == '' (2)");
    
}

TEST_CASE("test_5")
{

        //
        // test the getLabel() method
        //
        LLUrlMatch match;
        CHECK_MESSAGE(match.getLabel() == "", "getLabel() == ''");

        match.setValues(10, 20, "", "Label", "", "", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getLabel() == "Label", "getLabel() == 'Label'");

        match.setValues(10, 20, "", "", "", "", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getLabel() == "", "getLabel() == '' (2)");
    
}

TEST_CASE("test_6")
{

        //
        // test the getTooltip() method
        //
        LLUrlMatch match;
        CHECK_MESSAGE(match.getTooltip() == "", "getTooltip() == ''");

        match.setValues(10, 20, "", "", "", "Info", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getTooltip() == "Info", "getTooltip() == 'Info'");

        match.setValues(10, 20, "", "", "", "", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getTooltip() == "", "getTooltip() == '' (2)");
    
}

TEST_CASE("test_7")
{

        //
        // test the getIcon() method
        //
        LLUrlMatch match;
        CHECK_MESSAGE(match.getIcon() == "", "getIcon() == ''");

        match.setValues(10, 20, "", "", "", "", "Icon", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getIcon() == "Icon", "getIcon() == 'Icon'");

        match.setValues(10, 20, "", "", "", "", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getIcon() == "", "getIcon() == '' (2)");
    
}

TEST_CASE("test_8")
{

        //
        // test the getMenuName() method
        //
        LLUrlMatch match;
        CHECK_MESSAGE(match.getMenuName(, "getMenuName() empty").empty());

        match.setValues(10, 20, "", "", "", "", "Icon", LLStyle::Params(), "xui_file.xml", "", LLUUID::null);
        ensure_equals("getMenuName() == \"xui_file.xml\"", match.getMenuName(), "xui_file.xml");

        match.setValues(10, 20, "", "", "", "", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getMenuName(, "getMenuName() empty (2)").empty());
    
}

TEST_CASE("test_9")
{

        //
        // test the getLocation() method
        //
        LLUrlMatch match;
        CHECK_MESSAGE(match.getLocation(, "getLocation() empty").empty());

        match.setValues(10, 20, "", "", "", "", "Icon", LLStyle::Params(), "xui_file.xml", "Paris", LLUUID::null);
        ensure_equals("getLocation() == \"Paris\"", match.getLocation(), "Paris");

        match.setValues(10, 20, "", "", "", "", "", LLStyle::Params(), "", "", LLUUID::null);
        CHECK_MESSAGE(match.getLocation(, "getLocation() empty (2)").empty());
    
}

} // TEST_SUITE

