#pragma once

#include <iostream>
#include <string>
#include <json.h>
#include "json-forwards.h"
#include "restc.h"
#pragma comment(lib,"restc.lib")

#define RESTCMD_BUFSZ	1024

enum http_status_code
{
	HTTP_OK = 200,
	HTTP_Created = 201,
	HTTP_BadRequest = 400,
	HTTP_NotFound = 404,
	HTTP_InternalServerError = 500,
	HTTP_BadGateway = 502,
};

/** RestCmd
  * 对restc.dll的封装，用于向设备发送HTTP命令,并对JSON进行解析
  *
  *	所有成员函数在发生restc错误时为抛出std::runtime_error异常，
  *	JSON解析错误抛出Json::Exception异常
**/
class RestCmd
{
public:

	/* 构造函数只分配资源，网络连接还未建立 */
	RestCmd(const std::string & ip, unsigned short port);
	~RestCmd();

	/** 设备可以匿名访问,具体内容参见手册 **/
	static void setAuthorization(const std::string & user, const std::string & passwd);
	/** 超时以毫秒为单位，默认连接超时为30000毫秒 **/
	void setTimeout(int seconds);

	/* HTTP GET 请求 */
	void restGet(const std::string & url_path, Json::Value & reply, int & statusCode);
	void restGetBin(const std::string & url_path, char * buf);
	/* HTTP PUT 请求, 设备返回信息是可选的 */
	void restPut(const std::string & url_path, const Json::Value & request, Json::Value *preply, int & statusCode);
	/* HTTP POST 请求，设备返回信息是可选的 */
	void restPost(const std::string & url_path, const Json::Value & request, Json::Value *preply, int & statusCode);
	/* HTTP DELETE 请求 */
	void restDel(const std::string & url_path, int & statusCode);

private:
	/** POST 和 PUT 共用 **/
	void _restPut(const std::string & url_path, const Json::Value & request, Json::Value *preply, int & statusCode
		, int(*put_func)(RestConn, const char *, RestHeaders, char *, size_t, size_t *));

	RestConn _rest_conn;
	char * _rest_buf;
	Json::CharReader* _reader;
};
