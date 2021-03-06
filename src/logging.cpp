// -*- coding: utf-8 -*-
/* *******************************************************************
* File: logging.cpp                             Part of Shadow World *
*                                                                    *
* Copyright (C) 2012, Joachim Pileborg and individual contributors.  *
* All rights reserved.                                               *
*                                                                    *
* Redistribution and use in source and binary forms, with or without *
* modification, are permitted provided that the following conditions *
* are met:                                                           *
*                                                                    *
*   o Redistributions of source code must retain the above copyright *
*     notice, this list of conditions and the following disclaimer.  *
*   o Redistributions in binary form must reproduce the above        *
*     copyright notice, this list of conditions and the following    *
*     disclaimer in the documentation and/or other materials         *
*     provided with the distribution.                                *
*   o Neither the name of Shadow World nor the names of its          *
*     contributors may be used to endorse or promote products        *
*     derived from this software without specific prior written      * 
*     permission.                                                    *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS  *
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,*
* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,           *
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY       *
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR     *
* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF *
* THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF    *
* SUCH DAMAGE.                                                       *
*                                                                    *
******************************************************************* */

#include "shadow.h"

#include <boost/log/core.hpp>
#include <boost/log/filters.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/formatters.hpp>
#include <boost/log/utility/init/common_attributes.hpp>
#include <boost/log/utility/empty_deleter.hpp>
#include <boost/log/utility/init/to_console.hpp>

namespace logger = boost::log;

namespace shadow {
namespace logging {

/* **************************************************************** */

bool init()
{
	logger::add_common_attributes();

	auto core = logger::core::get();

#ifndef DEBUG
	// In release mode, we don't need debug/trace level logging
	core->set_filter(
		logger::filter::attr<logger::trivial::severity_level>("Severity") >= logger::trivial::info
    );
#endif

	// TODO: Option to log to file
	auto sink = logger::init_log_to_console();

	// TODO: Setup formating
	sink->set_formatter
	(
		logger::formatters::stream
			<< logger::formatters::date_time("TimeStamp", "%Y-%m-%d %H:%M:%S") << " :: "
			<< logger::formatters::attr<logger::trivial::severity_level>("Severity") << " :: "
			<< logger::formatters::message()
	);

	core->add_sink(sink);

	return true;
}

void clean()
{
}

/* **************************************************************** */

} // namespace logging
} // namespace shadow
