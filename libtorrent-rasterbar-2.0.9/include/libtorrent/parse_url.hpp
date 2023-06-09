/*

Copyright (c) 2008-2009, 2014, 2016-2017, 2020, Arvid Norberg
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef TORRENT_PARSE_URL_HPP_INCLUDED
#define TORRENT_PARSE_URL_HPP_INCLUDED

#include "libtorrent/config.hpp"

#include <tuple>
#include <string>

#include "libtorrent/error_code.hpp"
#include "libtorrent/string_view.hpp"

namespace libtorrent {

	// returns protocol, auth, hostname, port, path
	TORRENT_EXTRA_EXPORT std::tuple<std::string, std::string
		, std::string, int, std::string>
		parse_url_components(std::string url, error_code& ec);

	// split a URL in its base and path parts
	TORRENT_EXTRA_EXPORT std::tuple<std::string, std::string>
		split_url(std::string url, error_code& ec);

	// returns true if the hostname contains any IDNA (internationalized domain
	// name) labels.
	TORRENT_EXTRA_EXPORT bool is_idna(string_view hostname);

	// the query string is the part of the URL immediately following "?", i.e.
	// the query string arguments. This function returns true if any of the
	// arguments are "info_hash", "port", "key", "event", "uploaded",
	// "downloaded", "left" or "corrupt".
	TORRENT_EXTRA_EXPORT bool has_tracker_query_string(string_view query_string);
}

#endif
