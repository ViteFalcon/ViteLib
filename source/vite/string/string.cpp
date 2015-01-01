/**
* The MIT License (MIT)
*
* Copyright (c) 2014 Abi George Ullattil (Vite Falcon)

* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include "string.h"
#include <cinttypes>
#include <cwctype>
#include <boost/locale.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <boost/scoped_array.hpp>
#if defined(_WIN32) || defined(_WIN64)
#   define WIN32_LEAN_AND_MEAN
#   include <Windows.h>
#endif // WINDOWNS

const vite::String vite::String::EMPTY;

vite::String::~String()
{

}

vite::String::String()
{

}

vite::String::String(const std::wstring& str)
{
    assign(str);
}

vite::String::String(const wchar_t* str)
{
    assign(str);
}

vite::String::String(const wchar_t* str, size_type length)
{
    assign(str, length);
}

vite::String::String(const std::string& str)
{
    assign(str);
}

vite::String::String(const char* str)
{
    assign(str);
}

vite::String::String(const char* str, size_type length)
{
    assign(str, length);
}

vite::String::String(size_type length, wchar_t ch)
{
    assign(length, ch);
}

vite::String::size_type vite::String::size() const
{
    return mString.size();
}

vite::String::size_type vite::String::length() const
{
    return mString.length();
}

vite::String::size_type vite::String::max_size() const
{
    return mString.max_size();
}

void vite::String::reserve(vite::String::size_type size)
{
    mString.reserve(size);
}

void vite::String::resize(vite::String::size_type num, const wchar_t& val /*= 0*/)
{
    mString.resize(num, val);
}

void vite::String::swap(vite::String& from)
{
    mString.swap(from.mString);
}

bool vite::String::empty() const
{
    return mString.empty();
}

const wchar_t* vite::String::c_str() const
{
     return mString.c_str();
}

vite::String::size_type vite::String::capacity() const
{
    return mString.capacity();
}

void vite::String::clear()
{
    mString.clear();
}

vite::String vite::String::substr(vite::String::size_type index, vite::String::size_type num /*= npos*/) const
{
    return mString.substr(index, num);
}

void vite::String::push_back(wchar_t val)
{
    mString.push_back(val);
}

void vite::String::push_back(char val)
{
    mString.push_back(val);
}

wchar_t& vite::String::at(vite::String::size_type pos)
{
    return mString.at(pos);
}

const wchar_t& vite::String::at(vite::String::size_type pos) const
{
    return mString.at(pos);
}

vite::String::iterator vite::String::begin()
{
    return mString.begin();
}

vite::String::const_iterator vite::String::begin() const
{
    return mString.begin();
}

vite::String::iterator vite::String::end()
{
    return mString.end();
}

vite::String::const_iterator vite::String::end() const
{
    return mString.end();
}

vite::String::reverse_iterator vite::String::rbegin()
{
    return mString.rbegin();
}

vite::String::const_reverse_iterator vite::String::rbegin() const
{
    return mString.rbegin();
}

vite::String::reverse_iterator vite::String::rend()
{
    return mString.rend();
}

vite::String::const_reverse_iterator vite::String::rend() const
{
    return mString.rend();
}

vite::String& vite::String::assign(const std::wstring& str)
{
    mString.assign(str);
    return *this;
}

vite::String& vite::String::assign(const wchar_t* str)
{
    mString.assign(str);
    return *this;
}

vite::String& vite::String::assign(const wchar_t* str, size_t length)
{
    mString.assign(str, length);
    return *this;
}

vite::String& vite::String::assign(const std::string& str)
{
    mString.assign(boost::locale::conv::utf_to_utf<wchar_t>(str));
    return *this;
}

vite::String& vite::String::assign(const char* str)
{
    mString.assign(boost::locale::conv::utf_to_utf<wchar_t>(str));
    return *this;
}

vite::String& vite::String::assign(const char* str, size_t length)
{
    mString.assign(boost::locale::conv::utf_to_utf<wchar_t>(str, str+length));
    return *this;
}

vite::String& vite::String::assign(size_t length, wchar_t ch)
{
    mString.assign(length, ch);
    return *this;
}

vite::String& vite::String::append(const vite::String& str)
{
    mString.append(str.mString);
    return *this;
}

vite::String& vite::String::append(const wchar_t* str)
{
    mString.append(str);
    return *this;
}

vite::String& vite::String::append(const char* str)
{
    mString.append(boost::locale::conv::utf_to_utf<wchar_t>(str));
    return *this;
}

vite::String& vite::String::append(const vite::String& str, vite::String::size_type index, vite::String::size_type len)
{
    mString.append(str.mString, index, len);
    return *this;
}

vite::String& vite::String::append(vite::String::iterator start, vite::String::iterator end)
{
    mString.append(start, end);
    return *this;
}

vite::String& vite::String::append(const wchar_t* str, size_type num)
{
    mString.append(str, num);
    return *this;
}

vite::String& vite::String::append(size_type num, wchar_t ch)
{
    mString.append(num, ch);
    return *this;
}

vite::String& vite::String::append(const char* str, size_type num)
{
    mString.append(boost::locale::conv::utf_to_utf<wchar_t>(str, str+num));
    return *this;
}

vite::String& vite::String::append(size_type num, char ch)
{
    mString.append(num, ch);
    return *this;
}

vite::String::iterator vite::String::insert(iterator i, const wchar_t& ch)
{
    return mString.insert(i, ch);
}

vite::String& vite::String::insert(size_type pos, const String& str)
{
    mString.insert(pos, str.mString);
    return *this;
}

vite::String& vite::String::insert(size_type pos, const wchar_t* str)
{
    mString.insert(pos, str);
    return *this;
}

vite::String& vite::String::insert(size_type pos, const String& str, size_type subpos, size_type sublen)
{
    mString.insert(pos, str.mString, subpos, sublen);
    return *this;
}

void vite::String::insert(iterator i, iterator start, iterator end)
{
    mString.insert(i, start, end);
}

vite::String& vite::String::insert(size_type pos, const wchar_t* str, size_type num)
{
    mString.insert(pos, str, num);
    return *this;
}

vite::String& vite::String::insert(size_type pos, const char* str, size_type num)
{
    mString.insert(pos, boost::locale::conv::utf_to_utf<wchar_t>(str).c_str(), num);
    return *this;
}

vite::String& vite::String::insert(size_type pos, size_type num, wchar_t ch)
{
    mString.insert(pos, num, ch);
    return *this;
}

vite::String& vite::String::insert(size_type pos, size_type num, char ch)
{
    mString.insert(pos, num, ch);
    return *this;
}

void vite::String::insert(iterator i, size_type num, wchar_t ch)
{
    mString.insert(i, num, ch);
}

void vite::String::insert(iterator i, size_type num, char ch)
{
    mString.insert(i, num, ch);
}

vite::String::iterator vite::String::erase(iterator loc)
{
    return mString.erase(loc);
}

vite::String::iterator vite::String::erase(iterator start, iterator end)
{
    return mString.erase(start, end);
}

vite::String& vite::String::erase(size_type pos /*= 0*/, size_type num /*= npos*/)
{
    mString.erase(pos, num);
    return *this;
}

vite::String& vite::String::replace(size_type pos, size_type len, const String& str)
{
    mString.replace(pos, len, str.mString);
    return *this;
}

vite::String& vite::String::replace(size_type pos, size_type len, const String& str, size_type sublen)
{
    mString.replace(pos, len, str.mString.c_str(), sublen);
    return *this;
}

vite::String& vite::String::replace(size_type pos, size_type len, const String& str, size_type subpos, size_type sublen)
{
    mString.replace(pos, len, str.mString, subpos, sublen);
    return *this;
}

vite::String& vite::String::replace(size_type pos, size_type len, size_type num, wchar_t ch)
{
    mString.replace(pos, len, num, ch);
    return *this;
}

vite::String& vite::String::replace(iterator start, iterator end, size_type num, wchar_t ch)
{
    mString.replace(start, end ,num, ch);
    return *this;
}

int vite::String::compare(const String& str) const
{
    return mString.compare(str.mString);
}

int vite::String::compare(const wchar_t* str) const
{
    return mString.compare(str);
}

int vite::String::compare(size_type pos, size_type len, const String& str) const
{
    return mString.compare(pos, len, str.mString);
}

int vite::String::compare(size_type pos, size_type len, const String& str, size_type subpos, size_type sublen) const
{
    return mString.compare(pos, len, str.mString, subpos, sublen);
}

int vite::String::compare(size_type pos, size_type len, const wchar_t* str, size_type num) const
{
    return mString.compare(pos, len, str, num);
}

int vite::String::compare(size_type pos, size_type len, const char* str, size_type num) const
{
    return mString.compare(pos, len, boost::locale::conv::utf_to_utf<wchar_t>(str).c_str(), num);
}

vite::String::size_type vite::String::find(const String& str, size_type index /*= 0*/) const
{
    return mString.find(str, index);
}

vite::String::size_type vite::String::find(const char* str, size_type index, size_type length) const
{
    return mString.find(boost::locale::conv::utf_to_utf<wchar_t>(str).c_str(), index, length);
}

vite::String::size_type vite::String::find(const wchar_t* str, size_type index, size_type length) const
{
    return mString.find(str, index, length);
}

vite::String::size_type vite::String::find(char ch, size_type index /*= 0*/) const
{
    return mString.find(ch, index);
}

vite::String::size_type vite::String::find(wchar_t ch, size_type index /*= 0*/) const
{
    return mString.find(ch, index);
}

vite::String::size_type vite::String::rfind(const String& str, size_type index /*= 0*/) const
{
    return mString.rfind(str, index);
}

vite::String::size_type vite::String::rfind(const wchar_t* str, size_type index, size_type num) const
{
    return mString.rfind(str, index, num);
}

vite::String::size_type vite::String::rfind(const char* str, size_type index, size_type num) const
{
    return mString.rfind(boost::locale::conv::utf_to_utf<wchar_t>(str).c_str(), index, num);
}

vite::String::size_type vite::String::rfind(char ch, size_type index /*= 0*/) const
{
    return mString.rfind(ch, index);
}

vite::String::size_type vite::String::rfind(wchar_t ch, size_type index) const
{
    return mString.rfind(ch, index);
}

vite::String::size_type vite::String::find_first_of(const String &str, size_type index /*= 0*/, size_type num /*= npos*/) const
{
    return mString.find_first_of(str.mString.c_str(), index, num);
}

vite::String::size_type vite::String::find_first_of(wchar_t ch, size_type index /*= 0*/) const
{
    return mString.find_first_of(ch, index);
}

vite::String::size_type vite::String::find_first_of(char ch, size_type index /*= 0*/) const
{
    return mString.find_first_of(ch, index);
}

vite::String::size_type vite::String::find_first_not_of(const String& str, size_type index /*= 0*/, size_type num /*= npos*/) const
{
    return mString.find_first_not_of(str.mString.c_str(), index, num);
}

vite::String::size_type vite::String::find_first_not_of(wchar_t ch, size_type index /*= 0*/) const
{
    return mString.find_first_not_of(ch, index);
}

vite::String::size_type vite::String::find_first_not_of(char ch, size_type index /*= 0*/) const
{
    return mString.find_first_not_of(ch, index);
}

vite::String::size_type vite::String::find_last_of(const String& str, size_type index /*= npos*/, size_type num /*= npos*/) const
{
    return mString.find_last_of(str.mString.c_str(), index, num);
}

vite::String::size_type vite::String::find_last_of(wchar_t ch, size_type index /*= npos*/) const
{
    return mString.find_last_of(ch, index);
}

vite::String::size_type vite::String::find_last_of(char ch, size_type index /*= npos*/) const
{
    return mString.find_last_of(ch, index);
}

vite::String::size_type vite::String::find_last_not_of(const String& str, size_type index /*= npos*/, size_type num /*= npos*/) const
{
    return mString.find_last_not_of(str.mString.c_str(), index, num);
}

vite::String::size_type vite::String::find_last_not_of(wchar_t ch, size_type index /*= npos*/) const
{
    return mString.find_last_not_of(ch, index);
}

vite::String::size_type vite::String::find_last_not_of(char ch, size_type index /*= npos*/) const
{
    return mString.find_last_not_of(ch, index);
}

bool vite::String::operator<(const String& right) const
{
    return compare(right) < 0;
}

bool vite::String::operator<=(const String& right) const
{
    return compare(right) <= 0;
}

bool vite::String::operator>(const String& right) const
{
    return compare(right) > 0;
}

bool vite::String::operator>=(const String& right) const
{
    return compare(right) >= 0;
}

bool vite::String::operator==(const String& right) const
{
    return compare(right) == 0;
}

bool vite::String::operator!=(const String& right) const
{
    return !operator==(right);
}

vite::String& vite::String::operator=(const String& s)
{
    mString.operator =(s.mString);
    return *this;
}

vite::String& vite::String::operator=(wchar_t ch)
{
    mString.operator =(ch);
    return *this;
}

vite::String& vite::String::operator=(char ch)
{
    mString.operator =(ch);
    return *this;
}

wchar_t& vite::String::operator[](size_type index)
{
    return mString.operator [](index);
}

const wchar_t& vite::String::operator[](size_type index) const
{
    return mString.operator [](index);
}

vite::String::operator const std::wstring&() const
{
    return mString;
}

vite::String::operator const std::string&() const
{
    return asUTF8();
}

const std::string& vite::String::asUTF8() const
{
    mUTF8StringStock = boost::locale::conv::utf_to_utf<char>(mString);
    return mUTF8StringStock;
}

const char* vite::String::asUTF8_c_str() const
{
    return asUTF8().c_str();
}

const std::wstring& vite::String::asWStr() const
{
    return mString;
}

const wchar_t* vite::String::asWStr_c_str() const
{
    return c_str();
}

const vite::String::size_type vite::String::npos = String::wstring_type::npos;

vINLINE const std::string& getCurrentLocale()
{
    static boost::optional<std::string> staticCurrentLocale;

    if (!staticCurrentLocale.is_initialized())
    {
#ifdef _WIN32
        // Corresponded and copied from boost\libs\locale\src\encoding\wconv_codepage.ipp
        struct WindowsEncoding
        {
            char const *name;
            std::uint32_t codepage;
        } allWindowsEncodings[] =
        {
            { "big5",       950 },
            { "cp1250",     1250 },
            { "cp1251",     1251 },
            { "cp1252",     1252 },
            { "cp1253",     1253 },
            { "cp1254",     1254 },
            { "cp1255",     1255 },
            { "cp1256",     1256 },
            { "cp1257",     1257 },
            { "cp874",      874 },
            { "cp932",      932 },
            { "eucjp",      20932 },
            { "euckr",      51949 },
            { "gb18030",    54936 },
            { "gb2312",     936 },
            { "iso2022jp",  50220 },
            { "iso2022kr",  50225 },
            { "iso88591",   28591 },
            { "iso885913",  28603 },
            { "iso885915",  28605 },
            { "iso88592",   28592 },
            { "iso88593",   28593 },
            { "iso88594",   28594 },
            { "iso88595",   28595 },
            { "iso88596",   28596 },
            { "iso88597",   28597 },
            { "iso88598",   28598 },
            { "iso88599",   28599 },
            { "koi8r",      20866 },
            { "koi8u",      21866 },
            { "shiftjis",   932 },
            //{ "sjis",     932 },
            { "usascii",    20127 },
            { "utf8",       65001 },
            { "windows1250",1250 },
            { "windows1251",1251 },
            { "windows1252",1252 },
            { "windows1253",1253 },
            { "windows1254",1254 },
            { "windows1255",1255 },
            { "windows1256",1256 },
            { "windows1257",1257 },
            { "windows874", 874 },
            { "windows932", 932 },
        };

        char buffer[64];
        GetLocaleInfoA(LOCALE_USER_DEFAULT, LOCALE_IDEFAULTANSICODEPAGE, buffer, sizeof(buffer));

        std::uint32_t systemCodepage = boost::lexical_cast<std::uint32_t>(buffer);
        std::uint32_t availableCodepageCount = sizeof(allWindowsEncodings) / sizeof(allWindowsEncodings[0]);

        for (std::uint32_t index = 0; index < availableCodepageCount; ++index)
        {
            if (systemCodepage == allWindowsEncodings[index].codepage)
            {
                staticCurrentLocale = allWindowsEncodings[index].name;
                break;
            }
        }
#else
        staticCurrentLocale = "UTF-8";
#endif
    }

    return staticCurrentLocale.get();
}


vite::String vite::String::FromEucKr(const std::string& str)
{
#ifdef _WIN32
    return FromEncoding(str, "euckr");
#else
    // ICU's EUC-KR locale name
    return FromEncoding(str, "cp949");
#endif
}

std::string vite::String::FromEucKrAsUtf8(const std::string& str)
{
    return FromEucKr(str).asUTF8();
}

vite::String vite::String::FromCurrentEncoding(const std::string& str)
{
    return boost::locale::conv::to_utf<char>(str, getCurrentLocale());
}

std::string vite::String::ToCurrentEncoding(const String& str)
{
    return boost::locale::conv::from_utf(str.asWStr(), getCurrentLocale());
}

vite::String vite::String::FromEncoding(const std::string& str, const std::string& encodingName)
{
    return boost::locale::conv::to_utf<char>(str.data(), encodingName);
}

std::string vite::String::ToEncoding(const String& str, const std::string& encodingName)
{
    return boost::locale::conv::from_utf(str.asWStr(), encodingName);
}


vINLINE vite::String readUtf8FromStream(std::istream& stream, std::uint32_t lengthInBytes)
{
    boost::scoped_array<char> buffer(new char[lengthInBytes]);
    stream.read(buffer.get(), lengthInBytes);
    buffer[lengthInBytes-1] = 0;

    return boost::locale::conv::utf_to_utf<wchar_t>(buffer.get());
}

vINLINE vite::String readUtf16LittleEndianFromStream(std::istream& stream, std::uint32_t lengthInBytes)
{
    std::uint32_t textSize = lengthInBytes / 2;
    boost::scoped_array<std::uint16_t> buffer(new std::uint16_t[textSize]);
    stream.read((char*)buffer.get(), lengthInBytes);
    buffer[textSize-1] = 0;

    return boost::locale::conv::utf_to_utf<wchar_t>(buffer.get());
}

vINLINE vite::String readUtf16BigEndianFromStream(std::istream& stream, std::uint32_t lengthInBytes)
{
    std::uint32_t textSize = lengthInBytes / 2;
    boost::scoped_array<std::uint16_t> buffer(new std::uint16_t[textSize]);
    stream.read((char*)buffer.get(), lengthInBytes);
    buffer[textSize-1] = 0;

    for (std::uint32_t pos = 0; pos < textSize; ++pos)
        buffer[pos] = (buffer[pos] >> 8) | (buffer[pos] << 8);

    return boost::locale::conv::utf_to_utf<wchar_t>(buffer.get());
}

vINLINE vite::String readAnsiStringFromStream(std::istream& stream, std::uint32_t lengthInBytes)
{
    boost::scoped_array<char> buffer(new char[lengthInBytes]);
    stream.read(buffer.get(), lengthInBytes);
    buffer[lengthInBytes-1] = 0;

    return vite::String::FromCurrentEncoding(buffer.get());
}

vite::String vite::String::FromStream(std::istream& stream)
{
    stream.seekg(0, std::ios::end);
    std::uint32_t streamSize = (std::uint32_t)stream.tellg();
    stream.seekg(0, std::ios::beg);

    std::uint32_t byteMarks = 0;
    stream.read((char*)&byteMarks, 4);

    if ((byteMarks & 0x00FFFFFF) == 0x00BFBBEF)
    {
        stream.seekg(3, std::ios::beg);
        return readUtf8FromStream(stream, streamSize - 3);
    }
    else if ((byteMarks & 0x0000FFFF) == 0x0000FEFF)
    {
        stream.seekg(2, std::ios::beg);
        return readUtf16LittleEndianFromStream(stream, streamSize - 2);
    }
    else if ((byteMarks & 0x0000FFFF) == 0x0000FFFE)
    {
        stream.seekg(2, std::ios::beg);
        return readUtf16BigEndianFromStream(stream, streamSize - 2);
    }

    stream.seekg(0, std::ios::beg);
    return readAnsiStringFromStream(stream, streamSize);
}

namespace std
{
    hash<vite::String>::result_type hash<vite::String>::operator()(argument_type const& value) const
    {
        return std::hash<std::string>()(value.asUTF8());
    }
}

