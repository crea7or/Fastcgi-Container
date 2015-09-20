// Fastcgi Container - framework for development of high performance FastCGI applications in C++
// Copyright (C) 2011 Ilya Golubtsov <golubtsov@yandex-team.ru> (Fastcgi Daemon)
// Copyright (C) 2015 Alexander Ponomarenko <contact@propulsion-analysis.com>

// This file is part of Fastcgi Container.
//
// Fastcgi Container is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License (LGPL) as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Fastcgi Container is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License (LGPL) for more details.
//
// You should have received a copy of the GNU Lesser General Public License (LGPL)
// along with Fastcgi Container. If not, see <http://www.gnu.org/licenses/>.

#ifndef _FASTCGI_DETAILS_STRING_BUFFER_H_
#define _FASTCGI_DETAILS_STRING_BUFFER_H_

#include <string>
#include <vector>

#include "fastcgi3/data_buffer.h"
#include "details/data_buffer_impl.h"

namespace fastcgi
{

class StringBuffer : public DataBufferImpl {
public:
	StringBuffer(const char *data, std::uint64_t size);
	virtual ~StringBuffer();
	virtual std::uint64_t read(std::uint64_t pos, char *data, std::uint64_t len);
	virtual std::uint64_t write(std::uint64_t pos, const char *data, std::uint64_t len);
	virtual char at(std::uint64_t pos);
	virtual std::uint64_t find(std::uint64_t begin, std::uint64_t end, const char* buf, std::uint64_t len);
	virtual std::pair<std::uint64_t, std::uint64_t> trim(std::uint64_t begin, std::uint64_t end) const;
	virtual std::pair<char*, std::uint64_t> chunk(std::uint64_t pos) const;
	virtual std::pair<std::uint64_t, std::uint64_t> segment(std::uint64_t pos) const;
	virtual std::uint64_t size() const;
	virtual void resize(std::uint64_t size);
	virtual const std::string& filename() const;
	virtual DataBufferImpl* getCopy() const;
private:
	std::shared_ptr<std::vector<char>> data_;
};

} // namespace fastcgi

#endif // _FASTCGI_DETAILS_STRING_BUFFER_H_
