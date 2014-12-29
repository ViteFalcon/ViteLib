////////////////////////////////////////////////////////////////////////////////
// This source code is part of RokLegend project.
//         (Ragnarök Online Client)
//     Copyright (c) RokLegend Team, 2013
////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef VITE_STRING_H_INCLUDED
#define VITE_STRING_H_INCLUDED

#include <string>
#include "../defines.hpp"

namespace vite
{
    class String
    {
    public:
        static const String EMPTY;

        //! Returns a string that converted from ansi string \a str with EUC-KR encoding
        static String FromEucKr(const std::string& str);

        //! Returns a UTF8 string that converted from ansi string \a str with EUC-KR encoding
        static std::string FromEucKrAsUtf8(const std::string& str);

        //! Returns a unicode string that converted from ansi string \a str with current OS specified encoding.
        static String FromCurrentEncoding(const std::string& str);

        //! Returns a ansi string that converted from unicode string \a str with current OS specified encoding.
        static std::string ToCurrentEncoding(const String& str);

        //! Returns a unicode string that converted from ansi string \a str with \a encodingName encoding.
        static String FromEncoding(const std::string& str, const std::string& encodingName);

        //! Returns a ansi string that converted from unicode string \a str with \a encodingName encoding.
        static std::string ToEncoding(const String& str, const std::string& encodingName);

        //! Load a text file from \a stream (Byte order mark supported) and returns the text content.
        static String FromStream(std::istream& stream);

        //////////////////////////////////////////////////////////////////////////

        typedef std::wstring wstring_type;
        typedef wstring_type::value_type value_type;
        typedef wstring_type::traits_type traits_type;
        typedef wstring_type::allocator_type allocator_type;
        typedef wstring_type::reference reference;
        typedef wstring_type::const_reference const_reference;
        typedef wstring_type::pointer pointer;
        typedef wstring_type::const_pointer const_pointer;
        typedef wstring_type::iterator iterator;
        typedef wstring_type::const_iterator const_iterator;
        typedef wstring_type::reverse_iterator reverse_iterator;
        typedef wstring_type::const_reverse_iterator const_reverse_iterator;
        typedef wstring_type::difference_type difference_type;
        typedef wstring_type::size_type size_type;

        static const size_type npos;

        //////////////////////////////////////////////////////////////////////////

        ~String();

        //! default constructor, creates an empty string
        String();

        //! duplicate of \a wstr
        String(const std::wstring& str);

        //! duplicate of nul-terminated \c wchar_t array
        String(const wchar_t* str);

        //! duplicate of \a str, \a length characters long
        String(const wchar_t* str, size_type length);

        //! duplicate of \a str (UTF-8 encoding)
        String(const std::string& str);

        //! duplicate of nul-terminated C-string \a str (UTF-8 encoding)
        String(const char* str);

        //! duplicate of \a str, \a length characters long (UTF-8 encoding)
        String(const char* str, size_type length);

        //! \a length copies of \a ch
        String(size_type length, wchar_t ch);

        //////////////////////////////////////////////////////////////////////////

        //! Returns the number of code points in the current string
        size_type size() const;

        //! Returns the number of code points in the current string
        size_type length() const;

        //! returns the maximum number of UTF-16 code points that the string can hold
        size_type max_size() const;

        //! sets the capacity of the string to at least \a size code points
        void reserve(size_type size);

        //! changes the size of the string to \a size, filling in any new area with \a val
        void resize(size_type num, const wchar_t& val = 0);

        //! exchanges the elements of the current string with those of \a from
        void swap(String& from);

        //! returns \c true if the string has no elements, \c false otherwise
        bool empty() const;

        //! returns a pointer to the first character in the current string
        const wchar_t* c_str() const;

        //! returns the number of elements that the string can hold before it will need to allocate more space
        size_type capacity() const;

        //! deletes all of the elements in the string
        void clear();

        //! returns a substring of the current string, starting at \a index, and \a num characters long.
        /*! If \a num is omitted, it will default to \c UString::npos, and the substr() function will simply return the remainder of the string starting at \a index. */
        String substr(size_type index, size_type num = npos) const;

        //! appends \a val to the end of the string
        void push_back(wchar_t val);

        //! appends \a val to the end of the string
        void push_back(char val);

        //! returns a reference to the element in the string at index \c loc
        wchar_t& at(size_type pos);

        //! returns a reference to the element in the string at index \c loc
        const wchar_t& at(size_type pos) const;

        //////////////////////////////////////////////////////////////////////////

        //! returns an iterator to the first element of the string
        iterator begin();

        //! returns an iterator to the first element of the string
        const_iterator begin() const;

        //! returns an iterator just past the end of the string
        iterator end();

        //! returns an iterator just past the end of the string
        const_iterator end() const;

        //! returns a reverse iterator to the last element of the string
        reverse_iterator rbegin();

        //! returns a reverse iterator to the last element of the string
        const_reverse_iterator rbegin() const;

        //! returns a reverse iterator just past the beginning of the string
        reverse_iterator rend();

        //! returns a reverse iterator just past the beginning of the string
        const_reverse_iterator rend() const;

        //////////////////////////////////////////////////////////////////////////

        //! assign \a str to the current string
        String& assign(const std::wstring& str);

        //! assign the nul-terminated \a str to the current string
        String& assign(const wchar_t* str);

        //! assign the first \a length characters of \a str to the current string
        String& assign(const wchar_t* str, size_t length);

        //! assign \a str to the current string
        String& assign(const std::string& str);

        //! assign the nul-terminated \a str to the current string
        String& assign(const char* str);

        //! assign the first \a length characters of \a str to the current string
        String& assign(const char* str, size_t length);

        //! assign \a length copies of \a ch to the current string
        String& assign(size_t length, wchar_t ch);

        //////////////////////////////////////////////////////////////////////////

        //! appends \a str on to the end of the current string
        String& append(const String& str);

        //! appends \a str on to the end of the current string
        String& append(const wchar_t* str);

        //! appends \a str on to the end of the current string
        String& append(const char* str);

        //! appends a substring of \a str starting at \a index that is \a len characters long on to the end of the current string
        String& append(const String& str, size_type index, size_type len);

        //! appends the sequence denoted by \a start and \a end on to the end of the current string
        String& append(iterator start, iterator end);

        //! appends \a num characters of \a str on to the end of the current string
        String& append(const wchar_t* str, size_type num);

        //! appends \a num repetitions of \a ch on to the end of the current string
        String& append(size_type num, wchar_t ch);

        //! appends \a num characters of \a str on to the end of the current string
        String& append(const char* str, size_type num);

        //! appends \a num repetitions of \a ch on to the end of the current string
        String& append(size_type num, char ch);

        //////////////////////////////////////////////////////////////////////////

        //! inserts \a ch before the code point denoted by \a i
        iterator insert(iterator i, const wchar_t& ch);

        //! inserts \a str into the current string, at location \a pos
        String& insert(size_type pos, const String& str);

        //! inserts \a str into the current string, at location \a pos
        String& insert(size_type pos, const wchar_t* str);

        //! inserts a substring of \a str (starting at \a subpos and \a sublen code points long) into the current string, at location \a pos
        String& insert(size_type pos, const String& str, size_type subpos, size_type sublen);

        //! inserts the code points denoted by \a start and \a end into the current string, before the code point specified by \a i
        void insert(iterator i, iterator start, iterator end);

        //! inserts \a num code points of \a str into the current string, at location \a pos
        String& insert(size_type pos, const wchar_t* str, size_type num);

        //! inserts \a num code points of \a str into the current string, at location \a pos
        String& insert(size_type pos, const char* str, size_type num);

        //! inserts \a num copies of \a ch into the current string, at location \a pos
        String& insert(size_type pos, size_type num, wchar_t ch);

        //! inserts \a num copies of \a ch into the current string, at location \a pos
        String& insert(size_type pos, size_type num, char ch);

        //! inserts \a num copies of \a ch into the current string, before the code point denoted by \a i
        void insert(iterator i, size_type num, wchar_t ch);

        //! inserts \a num copies of \a ch into the current string, before the code point denoted by \a i
        void insert(iterator i, size_type num, char ch);

        //////////////////////////////////////////////////////////////////////////

        //! removes the code point pointed to by \a loc, returning an iterator to the next character
        iterator erase(iterator loc);

        //! removes the code points between \a start and \a end (including the one at \a start but not the one at \a end), returning an iterator to the code point after the last code point removed
        iterator erase(iterator start, iterator end);

        //! removes \a num code points from the current string, starting at \a pos
        String& erase(size_type pos = 0, size_type num = npos);

        //////////////////////////////////////////////////////////////////////////

        //! replaces up to \a len code points of the current string (starting at \a pos) with \a str
        String& replace(size_type pos, size_type len, const String& str);

        //! replaces up to \a len code points of the current string (starting at \a pos) with up to \a sublen code points from \a str
        String& replace(size_type pos, size_type len, const String& str, size_type sublen);

        //! replaces up to \a len code points of the current string (starting at \a pos) with up to \a sublen code points from \a str beginning at \a subpos
        String& replace(size_type pos, size_type len, const String& str, size_type subpos, size_type sublen);

        //! replaces up to \a len code points in the current string (beginning at \a pos) with \c num copies of \c ch
        String& replace(size_type pos, size_type len, size_type num, wchar_t ch);

        //! replaces the code points in the current string from \a start to \a end with \a num copies of \a ch
        String& replace(iterator start, iterator end, size_type num, wchar_t ch);

        //////////////////////////////////////////////////////////////////////////

        //! compare \a str to the current string
        int compare(const String& str) const;

        //! compare \a str to the current string
        int compare(const wchar_t* str) const;

        //! compare \a str to a substring of the current string, starting at \a pos for \a len characters
        int compare(size_type pos, size_type len, const String& str) const;

        //! compare a substring of \a str to a substring of the current string, where \a subpos and \a sublen refer to \a str and \a pos and \a len refer to the current string
        int compare(size_type pos, size_type len, const String& str, size_type subpos, size_type sublen) const;

        //! compare a substring of \a str to a substring of the current string, where the substring of \a str begins at zero and is \a num characters long, and the substring of the current string begins at \a pos and is \a len characters long
        int compare(size_type pos, size_type len, const wchar_t* str, size_type num) const;

        //! compare a substring of \a str to a substring of the current string, where the substring of \a str begins at zero and is \a num characters long, and the substring of the current string begins at \a pos and is \a len characters long
        int compare(size_type pos, size_type len, const char* str, size_type num) const;

        //////////////////////////////////////////////////////////////////////////

        //! returns the index of the first occurrence of \a str within the current string, starting at \a index; returns \c UString::npos if nothing is found
        size_type find(const String& str, size_type index = 0) const;

        //! returns the index of the first occurrence of \a str within the current string and within \a length code points, starting at \a index; returns \c UString::npos if nothing is found
        size_type find(const char* c_str, size_type index, size_type length) const;

        //! returns the index of the first occurrence of \a str within the current string and within \a length code points, starting at \a index; returns \c UString::npos if nothing is found
        size_type find(const wchar_t* w_str, size_type index, size_type length) const;

        //! returns the index of the first occurrence \a ch within the current string, starting at \a index; returns \c UString::npos if nothing is found
        size_type find(char ch, size_type index = 0) const;

        //! returns the index of the first occurrence \a ch within the current string, starting at \a index; returns \c UString::npos if nothing is found
        size_type find(wchar_t ch, size_type index = 0) const;

        //! returns the location of the first occurrence of \a str in the current string, doing a reverse search from \a index; returns \c UString::npos if nothing is found
        size_type rfind(const String& str, size_type index = 0) const;

        //! returns the location of the first occurrence of \a str in the current string, doing a reverse search from \a index, searching at most \a num characters; returns \c UString::npos if nothing is found
        size_type rfind(const char* c_str, size_type index, size_type num) const;

        //! returns the location of the first occurrence of \a str in the current string, doing a reverse search from \a index, searching at most \a num characters; returns \c UString::npos if nothing is found
        size_type rfind(const wchar_t* w_str, size_type index, size_type num) const;

        //! returns the location of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UString::npos if nothing is found
        size_type rfind(char ch, size_type index = 0) const;

        //! returns the location of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UString::npos if nothing is found
        size_type rfind(wchar_t ch, size_type index = 0) const;

        //////////////////////////////////////////////////////////////////////////

        //! Returns the index of the first character within the current string that matches \b any character in \a str, beginning the search at \a index and searching at most \a num characters; returns \c UString::npos if nothing is found
        size_type find_first_of(const String &str, size_type index = 0, size_type num = npos) const;

        //! returns the index of the first occurrence of \a ch in the current string, starting the search at \a index; returns \c UString::npos if nothing is found
        size_type find_first_of(char ch, size_type index = 0) const;

        //! returns the index of the first occurrence of \a ch in the current string, starting the search at \a index; returns \c UString::npos if nothing is found
        size_type find_first_of(wchar_t ch, size_type index = 0) const;

        //! returns the index of the first character within the current string that does not match any character in \a str, beginning the search at \a index and searching at most \a num characters; returns \c UString::npos if nothing is found
        size_type find_first_not_of(const String& str, size_type index = 0, size_type num = npos) const;

        //! returns the index of the first character within the current string that does not match \a ch, starting the search at \a index; returns \c UString::npos if nothing is found
        size_type find_first_not_of(char ch, size_type index = 0) const;

        //! returns the index of the first character within the current string that does not match \a ch, starting the search at \a index; returns \c UString::npos if nothing is found
        size_type find_first_not_of(wchar_t ch, size_type index = 0) const;

        //! returns the index of the first character within the current string that matches any character in \a str, doing a reverse search from \a index and searching at most \a num characters; returns \c UString::npos if nothing is found
        size_type find_last_of(const String& str, size_type index = npos, size_type num = npos) const;

        //! returns the index of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UString::npos if nothing is found
        size_type find_last_of(char ch, size_type index = npos) const;

        //! returns the index of the first occurrence of \a ch in the current string, doing a reverse search from \a index; returns \c UString::npos if nothing is found
        size_type find_last_of(wchar_t ch, size_type index = npos) const;

        //! returns the index of the last character within the current string that does not match any character in \a str, doing a reverse search from \a index; returns \c UString::npos if nothing is found
        size_type find_last_not_of(const String& str, size_type index = npos, size_type num = npos) const;

        //! returns the index of the last occurrence of a character that does not match \a ch in the current string, doing a reverse search from \a index; returns \c UString::npos if nothing is found
        size_type find_last_not_of(char ch, size_type index = npos) const;

        //! returns the index of the last occurrence of a character that does not match \a ch in the current string, doing a reverse search from \a index; returns \c UString::npos if nothing is found
        size_type find_last_not_of(wchar_t ch, size_type index = npos) const;

        //////////////////////////////////////////////////////////////////////////

        bool operator<(const String& right) const;

        bool operator<=(const String& right) const;

        bool operator>(const String& right) const;

        bool operator>=(const String& right) const;

        bool operator==(const String& right) const;

        bool operator!=(const String& right) const;

        String& operator=(const String& s);

        String& operator=(wchar_t ch);

        String& operator=(char ch);

        wchar_t& operator[](size_type index);

        const wchar_t& operator[](size_type index) const;

        //////////////////////////////////////////////////////////////////////////

        operator const std::wstring&() const;

        operator const std::string&() const;

        //! returns the current string in UTF-8 form within a std::string
        const std::string& asUTF8() const;

        //! returns the current string in UTF-8 form as a nul-terminated char array
        const char* asUTF8_c_str() const;

        //! returns the current string in the native form of std::wstring
        const std::wstring& asWStr() const;

        //! returns the current string in the native form of a nul-terminated wchar_t array
        const wchar_t* asWStr_c_str() const;

    private:
        //roS11N_ALLOW_PRIVATE_ACCESS;

        //roS11N_SERIALIZE_FUNCTION
        //{
        //    archive & mString;
        //}

        std::wstring mString;
        mutable std::string mUTF8StringStock;
    };


    vINLINE std::ostream& operator << (std::ostream& os, const String& s)
    {
        return os << s.asUTF8();
    }

    vINLINE std::wostream& operator << (std::wostream& os, const String& s)
    {
        return os << s.asWStr();
    }

    vINLINE String operator+(const String& s1, const String& s2)
    {
        return String(s1).append(s2);
    }

    vINLINE String operator+(const String& s1, wchar_t c)
    {
        return String(s1).append(1, c);
    }

    vINLINE String operator+(const String& s1, char c)
    {
        return String(s1).append(1, c);
    }

    vINLINE String operator+(wchar_t c, const String& s2)
    {
        return String().append(1, c).append(s2);
    }

    vINLINE String operator+(char c, const String& s2)
    {
        return String().append(1, c).append(s2);
    }

    vINLINE bool operator == (const char* lhs, const String& rhs)
    {
        return rhs == lhs;
    }
}

namespace std
{
    template <>
    struct hash<vite::String>
    {
        typedef vite::String argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& value) const;
    };
}

#endif // VITE_STRING_H_INCLUDED
