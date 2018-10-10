//-*- mode: c++; indent-tabs-mode: t; -*-
//
// File: common Copyright (c) 2018 Manuel Cano
// Author: manuel.cano@amadeus.com
// Date: Tue Oct 09 10:00:22 2018
// Time-stamp: <>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
//   02110-1301	USA
//
//
// Includes
//
#ifndef common_h
#define common_h

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <fstream>

#include <windows.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "resource.h"

#ifdef UNICODE
#define stringcopy wcscpy
#else
#define stringcopy strcpy
#endif

#ifdef WITH_LOG
#define logp(p, str) mc::sys::log << "[" << __FILE__	\
	<< ":" << __LINE__ << "] " << str << std::endl
#define logf(p) mc::sys::log << "[" << __FILE__							\
	<< ":" << __LINE__ << ": "											\
	<< __PRETTY_FUNCTION__ << "] " << std::endl
#else
#define logp(p, str)
#define logf(p)
#endif

const std::string FILE_NAME ("window_list.json");

class win_t
{
public:
	HWND _hwnd;
	WINDOWPLACEMENT _place;
	bool _deserialized;
	std::string _title;
	std::string _class_name;

	win_t ()
		: _hwnd{},
		  _deserialized{}
		{}
};
typedef std::map<HWND, win_t> mapwin_t;

namespace mc {
	namespace sys {

#ifdef WITH_LOG
		extern std::ofstream log;
#endif

		template<typename Type>
		Type min (Type a, Type b)
		{
			return a < b ? a : b;
		}

		enum e_prio {
			e_debug,
			e_warning,
			e_error,
			e_critical,
			e_failure
		};

		int atoi (std::string & str);

		class stat_t
		{
		public:
			stat_t (std::string file_name);
			operator bool () { return _good; }
			size_t size ();
		private:
			bool _good;
			struct stat _st;
		};
		class file_t
		{
		public:
			file_t (std::string file_name);
			~file_t () { if (_file) ::fclose(_file); }
			operator bool () { return _good; }
			size_t size () { return _size; }
			char & operator [] (int i);
		private:
			bool _good;
			FILE * _file;
			size_t _size;
			char * _buf;
		};

	} // namespace sys
} // namespace mc

#endif // common_h
