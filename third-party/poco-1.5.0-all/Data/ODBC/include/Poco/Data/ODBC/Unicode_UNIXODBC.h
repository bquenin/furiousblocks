//
// Unicode.h
//
// $Id: //poco/Main/Data/ODBC/include/Poco/Data/ODBC/Unicode_UNIXODBC.h#4 $
//
// Library: ODBC
// Package: ODBC
// Module:  Unicode_UNIX
//
// Definition of Unicode_UNIX.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Data_ODBC_Unicode_UNIX_INCLUDED
#define Data_ODBC_Unicode_UNIX_INCLUDED


namespace Poco {
namespace Data {
namespace ODBC {


void makeUTF16(SQLCHAR* pSQLChar, SQLINTEGER length, std::string& target);
	/// Utility function for conversion from UTF-8 to UTF-16


inline void makeUTF16(SQLCHAR* pSQLChar, SQLSMALLINT length, std::string& target)
	/// Utility function for conversion from UTF-8 to UTF-16.
{
	makeUTF16(pSQLChar, (SQLINTEGER) length, target);
}


inline void makeUTF8(Poco::Buffer<SQLWCHAR>& buffer, int length, SQLPOINTER pTarget, SQLINTEGER targetLength);
	/// Utility function for conversion from UTF-16 to UTF-8.


inline void makeUTF8(Poco::Buffer<SQLWCHAR>& buffer, int length, SQLPOINTER pTarget, SQLSMALLINT targetLength)
	/// Utility function for conversion from UTF-16 to UTF-8.
{
	makeUTF8(buffer, length, pTarget, (SQLINTEGER) targetLength);
}


} } } // namespace Poco::Data::ODBC


#endif // Data_ODBC_Unicode_UNIX_INCLUDED
