// -*- mode: C++; coding: utf-8 -*-
#ifndef NET_SERVER_H_
#define NET_SERVER_H_ 1
/* *******************************************************************
* File: net/server.h                            Part of Shadow World *
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

#include <boost/asio.hpp>

namespace shadow {
namespace net {

/* **************************************************************** */

template<class ProtoT>
class server
{
public:
	typedef ProtoT protocol_type;

private:
	protocol_type protocol_;
};

/* **************************************************************** */

namespace server {

/* **************************************************************** */

// TODO: New concept: Have the server class generic (i.e. templated)
//       with the template being a "protocol implementation", that handles
//       all the protocol specific bit. This `Server` class handles the
//       the actual accepting of connections and not much more.
// TODO: Also try to make the protocol bits more abstract, especially
//       try to hide the Boost stuff behgind our own classes and aliases.
class Server
{
public:
	// Disable copying
	Server(const Server &) = delete;
	Server(const Server &&) = delete;
	Server &operator=(const Server &) = delete;

	virtual ~Server()
		{ }

	virtual void start_accept() = 0;

protected:
	Server(boost::asio::io_service &service)
		: io_service_(service)
		{ }

	boost::asio::io_service &io_service() const
		{ return io_service_; }

private:
	boost::asio::io_service &io_service_;
};

/* **************************************************************** */

} // namespace server
} // namespace net
} // namespace shadow

#endif // NET_SERVER_H_
