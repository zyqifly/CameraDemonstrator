//#include "stdafx.h"
#include <exception>
#include "json.h"

#include "RestCmd.h"


RestCmd::RestCmd(const std::string & ip, unsigned short port)
{
	_rest_conn = restc_create_connection(ip.c_str(), port);
	if (_rest_conn == NULL)
		throw std::runtime_error("restc_create_connection failure");
	_rest_buf = new char[RESTCMD_BUFSZ];

	Json::CharReaderBuilder builder;
	_reader = builder.newCharReader();
}

RestCmd::~RestCmd()
{
	restc_destroy_connection(_rest_conn);
	delete[]_rest_buf;
	delete _reader;
}


void
RestCmd::setAuthorization(const std::string & user, const std::string & passwd)
{
	if (restc_set_authroization(user.c_str(), passwd.c_str()) != 0)
		throw std::runtime_error("restc_set_authroization failure");
}

void
RestCmd::setTimeout(int micro_seconds)
{
	if (restc_set_timeout(_rest_conn, micro_seconds) != EC_OK)
		throw std::runtime_error("restc_set_timeout failure");
}


void
RestCmd::restGet(const std::string & url_path, Json::Value & reply, int & statusCode)
{
	std::size_t length = 0;

	/** RestHeaders 为空时表示没有额外的HTTP头 **/
	statusCode = restc_get(_rest_conn, url_path.c_str(), NULL, _rest_buf, RESTCMD_BUFSZ, &length);
	if (statusCode != HTTP_OK)
		throw std::runtime_error("restc_get failure");
	if (length > 0)
	{
		if (!_reader->parse(_rest_buf, _rest_buf + length, &reply, NULL))
			throw Json::Exception("fail to parse reply");
	}
}

void  RestCmd::restGetBin(const std::string & url_path, char * buf)
{
	std::size_t length = 1024000;

	/** RestHeaders 为空时表示没有额外的HTTP头 **/
	restc_get(_rest_conn, url_path.c_str(), NULL, buf, length, &length);
}


void
RestCmd::restDel(const std::string & url_path, int & statusCode)
{
	std::size_t length = 0;

	/** RestHeaders 为空时表示没有额外的HTTP头 **/
	statusCode = restc_del(_rest_conn, url_path.c_str(), NULL, _rest_buf, RESTCMD_BUFSZ, &length);
	if (statusCode != HTTP_OK)
		throw std::runtime_error("restc_del failure");

}

void
RestCmd::restPut(const std::string & url_path, const Json::Value & request, Json::Value * preply, int & statusCode)
{
	_restPut(url_path, request, preply, statusCode, restc_put);
}

void
RestCmd::restPost(const std::string & url_path, const Json::Value & request, Json::Value * preply, int & statusCode)
{
	_restPut(url_path, request, preply, statusCode, restc_post);
}

void
RestCmd::_restPut(const std::string & url_path, const Json::Value & request, Json::Value * preply, int & statusCode
	, int(*put_func)(RestConn, const char *, RestHeaders, char *, size_t, size_t *))
{
	Json::FastWriter writer;
	std::string buf = writer.write(request);
	if (buf.size() > RESTCMD_BUFSZ)
		throw std::runtime_error("rest command is too long");
	memcpy(_rest_buf, buf.data(), buf.size());

	size_t length = buf.size();
	statusCode = put_func(_rest_conn, url_path.c_str(), NULL, _rest_buf, RESTCMD_BUFSZ, &length);
	if (statusCode != HTTP_OK && statusCode != HTTP_Created)
		throw std::runtime_error("restc_put failure");

	if (preply)
	{
		if (!_reader->parse(_rest_buf, _rest_buf + length, preply, NULL))
			throw Json::Exception("fail to parse reply");
	}
}
