/**
	restc

	REST���ʽӿڿ�
	REST-api client

	v2.1    2019.1
	v1.0.2	2017.8.21
	v1.0	2015.11.27

**/

#ifndef RESTC_H_INCLUDED
#define RESTC_H_INCLUDED
#pragma once

#include <stdlib.h>

///DLL for Windows
#ifdef _WIN32
#ifdef RESTC_EXPORTS
#ifdef __cplusplus
#define RESTC_API extern "C" __declspec(dllexport)
#else
#define RESTC_API __declspec(dllexport)
#endif
#else
#ifdef __cplusplus
#define RESTC_API extern "C" __declspec(dllimport)
#else
#define RESTC_API __declspec(dllexport)
#endif
#endif ///REST_EXPORTS

///Shared library for Linux
#else
#ifdef __cplusplus
#define RESTC_API extern "C"
#else
#define RESTC_API
#endif
#endif /// _WIN32

#define __IN
#define __OUT
#define __INOUT

typedef void *		RESTC_PTR;
#ifdef _UNICODE
typedef wchar_t		RCHAR;
#else
typedef char	    RCHAR;
#endif
typedef unsigned short PORT_NUM;
typedef RESTC_PTR	RestConn;		/** REST���Ӿ�� **/
typedef RESTC_PTR	RestHeaders;
#define NullConn     NULL

enum RestcErrorCode{
	EC_OK		= 0,				/** �������óɹ� **/
	EC_FAIL		= -1,				/** ��������ʧ�� **/
	EC_BUFSZ    = -2,				/** ���������� **/
	EC_NETWORK  = -3,				/** ������� **/
    EC_NOT_SUPPORTED = -4,
};

/** ȫ�ֺ��� Global libray functions **/
/** �̳߳ش�С�����ݼ�������û�������ȷ������Ҫ��������һ����CPU�ĺ�����һ�¿��Է����������, ���κ�������ǰ���÷�����Ч
    Try to set it according to your number of CPU cores so you can
    make use of the whole performace of your computer.  Call before any stream operations initiated **/
RESTC_API void restc_set_thread_num(int num);
RESTC_API void restc_cleanup();
RESTC_API int restc_get_version(__IN unsigned int *,__OUT char * buf,__INOUT size_t * bsz);



/** HTTPͷ���� HTTP header operations **/
RESTC_API RestHeaders restc_create_headers();
RESTC_API int restc_destroy_headers(RestHeaders);

RESTC_API int restc_add_header(RestHeaders,__IN const char * key,__IN const char * value);
RESTC_API int restc_get_header_num(RestHeaders);
RESTC_API int restc_get_header(RestHeaders,int idx,__IN char * key,__IN size_t * ksz,__OUT char * value,__INOUT size_t * vsz);
RESTC_API int restc_find_header(RestHeaders,__IN const char * key,__OUT char * value,__INOUT size_t * vsz);

/** �������� restc connection **/
RESTC_API RestConn restc_create_connection(__IN const char * host,PORT_NUM);
RESTC_API RestConn restc_create_usb_connection(PORT_NUM vid,PORT_NUM pid);
RESTC_API int restc_destroy_connection(RestConn);
RESTC_API int restc_set_authroization(__IN const char * user,__IN const char * passwd);
RESTC_API int restc_set_timeout(RestConn,int timeout_ms);

/** REST���� REST operations **/
/** ������ӳɹ���REST����������HTTP״̬�룬���򷵻ظ�����
	These functions will return HTTP status code from the server
    when HTTP transaction completes.
      If any network error occur in midst of the transaction,
	it will return a negative integer value in RestcErrorCode.

	���ڻ�����
	���еĲ��������������ɵ��ö�����ռ䣬һ��������ָ����Ҫ�Ļ�������СΪ1KB
	You should at least allocate 1KB memory as operation text buffer.
**/
/** REST GET ����
	���룺
		c		RestConn���Ӿ��
		path	URL·��
		hdr		�����HTTPͷ,����Ϊ��(NULL)
		buf		���յ������Ľ������ڴ˻�������
		bufsz	�����buf�Ĵ�С��SDKд��ķ����������ݲ��ᳬ���˽��ޣ�����������ĳ���bufsz����������EC_BUFSZ��
	�����
		length	Զ�˷��ص����ĳ���

	���أ�
		����ͨ������ʱ����HTTP״̬�룬����������ظ�ֵ
**/
RESTC_API int restc_get(RestConn c,__IN const char * path,RestHeaders hdr,__OUT char * buf,size_t bufsz,__OUT size_t * length);
/** REST PUT ����
	���룺
		c		RestConn���Ӿ��
		path	URL·��
		hdr		�����HTTPͷ,����Ϊ��(NULL)
		buf		�����͵��������ģ����յ�������Ҳ�������ڴ˻������У������������ݻᱻ����
		bufsz	�����buf�Ĵ�С��SDKд��ķ����������ݲ��ᳬ���˽��ޣ�����������Ĺ��󣬺�������EC_BUFSZ��
		length	�����͵��������ĳ���
	�����
		length	Զ�˷��ص����ĳ���

	���أ�
		����ͨ������ʱ����HTTP״̬�룬����������ظ�ֵ
**/
RESTC_API int restc_put(RestConn c,__IN const char * path,RestHeaders hdr,__INOUT char * buf,size_t bufsz,__INOUT size_t * length);

/** REST DELETE ����
	DELETEһ��û�����ķ��أ�buf����Ϊ��(NULL)
	���룺
		c		RestConn���Ӿ��
		path	URL·��
		hdr		�����HTTPͷ,����Ϊ��(NULL)
		buf		���յ������Ľ������ڴ˻�������
		bufsz	�����buf�Ĵ�С
	�����
		length	Զ�˷��ص����ĳ���

	���أ�
		����ͨ������ʱ����HTTP״̬�룬����������ظ�ֵ
**/
RESTC_API int restc_del(RestConn c,__IN const char * path,RestHeaders hdr,__OUT char * buf,size_t bufsz,__OUT size_t * length);

/** REST POST ����
	���룺
		c		RestConn���Ӿ��
		path	URL·��
		hdr		�����HTTPͷ,����Ϊ��(NULL)
		buf		�����͵��������ģ����յ�������Ҳ�������ڴ˻������У������������ݻᱻ����
		bufsz	�����buf�Ĵ�С��SDKд��ķ����������ݲ��ᳬ���˽��ޣ�����������Ĺ��󣬺�������EC_BUFSZ��
		length	�����͵��������ĳ���
	�����
		length	Զ�˷��ص����ĳ���

	���أ�
		����ͨ������ʱ����HTTP״̬�룬����������ظ�ֵ
**/
RESTC_API int restc_post(RestConn c,__IN const char * path,RestHeaders hdr,__INOUT char * buf,size_t bufsz,__INOUT size_t * length);

/** REST POST ����,�ϴ�ָ���ļ�
	���룺
		c		RestConn���Ӿ��
		path	URL·��
		hdr		�����HTTPͷ,����Ϊ��(NULL)
		filepath	���ϴ��ļ��ı���·��
		buf		���յ������Ľ������ڴ˻�������
		bufsz	�����buf�Ĵ�С��SDKд��ķ����������ݲ��ᳬ���˽��ޣ�����������Ĺ��󣬺�������EC_BUFSZ��
	�����
		length	Զ�˷��ص����ĳ���

	���أ�
		����ͨ������ʱ����HTTP״̬�룬����������ظ�ֵ
**/
RESTC_API int restc_post_file(RestConn c,__IN const char * path,RestHeaders hdr
							  ,__IN const char * filepath,__OUT char * buf,size_t bufsz,__OUT size_t * length);

/** REST POST ����,�ϴ�ָ���ڴ�����
	���룺
		c		RestConn���Ӿ��
		path	URL·��
		hdr		�����HTTPͷ,����Ϊ��(NULL)
		send_buf	���ϴ��ڴ���ʼָ��
		send_sz		�ϴ��ڴ��С
		reply_buf	���յ������Ľ������ڴ˻�������
		reply_sz	�����buf�Ĵ�С��SDKд��ķ����������ݲ��ᳬ���˽��ޣ�����������Ĺ��󣬺�������EC_BUFSZ��
	�����
		reply_sz	Զ�˷��ص����ĳ���

	���أ�
		����ͨ������ʱ����HTTP״̬�룬����������ظ�ֵ
**/
RESTC_API int restc_post_buffer(RestConn c,__IN const char * path,RestHeaders hdr
							  ,__IN const char * send_buf,size_t send_sz,
							  __OUT char * reply_buf,__INOUT size_t * reply_sz);

RESTC_API int restc_usb_grab(RestConn c,__OUT char * grab_buf,size_t grab_sz);

#endif ///RESTC_H_INCLUDED
