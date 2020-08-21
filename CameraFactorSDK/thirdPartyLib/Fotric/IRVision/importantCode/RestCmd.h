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
  * ��restc.dll�ķ�װ���������豸����HTTP����,����JSON���н���
  *
  *	���г�Ա�����ڷ���restc����ʱΪ�׳�std::runtime_error�쳣��
  *	JSON���������׳�Json::Exception�쳣
**/
class RestCmd
{
public:

	/* ���캯��ֻ������Դ���������ӻ�δ���� */
	RestCmd(const std::string & ip, unsigned short port);
	~RestCmd();

	/** �豸������������,�������ݲμ��ֲ� **/
	static void setAuthorization(const std::string & user, const std::string & passwd);
	/** ��ʱ�Ժ���Ϊ��λ��Ĭ�����ӳ�ʱΪ30000���� **/
	void setTimeout(int seconds);

	/* HTTP GET ���� */
	void restGet(const std::string & url_path, Json::Value & reply, int & statusCode);
	void restGetBin(const std::string & url_path, char * buf);
	/* HTTP PUT ����, �豸������Ϣ�ǿ�ѡ�� */
	void restPut(const std::string & url_path, const Json::Value & request, Json::Value *preply, int & statusCode);
	/* HTTP POST �����豸������Ϣ�ǿ�ѡ�� */
	void restPost(const std::string & url_path, const Json::Value & request, Json::Value *preply, int & statusCode);
	/* HTTP DELETE ���� */
	void restDel(const std::string & url_path, int & statusCode);

private:
	/** POST �� PUT ���� **/
	void _restPut(const std::string & url_path, const Json::Value & request, Json::Value *preply, int & statusCode
		, int(*put_func)(RestConn, const char *, RestHeaders, char *, size_t, size_t *));

	RestConn _rest_conn;
	char * _rest_buf;
	Json::CharReader* _reader;
};
