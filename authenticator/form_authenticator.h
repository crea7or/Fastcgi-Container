// Fastcgi Container - framework for development of high performance FastCGI applications in C++
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

#ifndef INCLUDE_FORM_AUTHENTICATOR_H_
#define INCLUDE_FORM_AUTHENTICATOR_H_

#include <string>
#include <memory>
#include <regex>

#include "fastcgi3/component.h"
#include "details/globals.h"

#include "abstract_authenticator.h"

namespace fastcgi
{

class Request;

namespace security
{

/**
 * Form-based authentication is a term of art in the context of Web- and Internet-based online networked computer systems.
 * In general, it refers to the notion of a user being presented with an editable "form" to fill in and submit in order
 * to log into some system or service.
 *
 * The steps of the technique are:
 *    1. An unauthenticated user agent requests a web page from a website, via the HTTP protocol.
 *    2. The website returns an HTML web page to the unauthenticated user agent. The web page consists minimally of an
 *       HTML-based web form which prompts the user for their username and password, along with a button labeled "login" or "submit".
 *    3. The user fills in his username and password, and then presses the submit button.
 *    4. The user agent sends the web form data (which includes the username and password) to the web server.
 *    5. The website implementation, running on the web server, performs some verification and validation operations on the web-form data.
 *       If successful, the website considers the user agent to be authenticated.
 *
 */
class FormAuthenticator : virtual public AbstractAuthenticator {
public:
	static const std::string COMPONENT_NAME;
	static const std::string SECURITY_CHECK_URL;
	static const std::string FORM_ACTION;
	static const std::string FORM_USERNAME;
	static const std::string FORM_PASSWORD;
	static const std::string DEFAULT_CACHE_DIR;
protected:
	static const std::string PARAM_NAME_STORED_REQUEST;
	static const std::string PARAM_NAME_STORED_REQUEST_URI;

public:
	FormAuthenticator(std::shared_ptr<fastcgi::ComponentContext> context);
	virtual ~FormAuthenticator();

	void doFilter(fastcgi::Request *request, fastcgi::HandlerContext *context, std::function<void(fastcgi::Request *request, fastcgi::HandlerContext *context)> next) override;

	virtual bool authenticate(fastcgi::Request* request) const override;

	std::string getSecurityCheckUrl(fastcgi::Request *request) const;
	const std::string& getFormUsername() const;
	const std::string& getFormPassword() const;

protected:
	virtual bool isAuthenticationRequired(fastcgi::Request* request) const override;

	fastcgi::DataBuffer createFileBuffer(const std::string &key) const;

private:
	std::string urlPrefix_;
	std::string securityCheckUrl_;
	std::string formAction_;

	std::string cache_dir_;
	std::uint64_t window_;

	std::regex securityCheckUrlRegex_;
	bool storeRequest_;
};


} // namespace security


} // namespace fastcgi

#endif /* INCLUDE_FORM_AUTHENTICATOR_H_ */
