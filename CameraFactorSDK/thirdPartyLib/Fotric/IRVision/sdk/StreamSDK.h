/*
 * StreamSDK 1.2
 * Copyright 2017, IRS.cn
 *
 * ��ȡ�����������������ݵĽӿڿ�
 * library for grabbing stream data from IIR device
*/

#ifndef STREAMSDK_H_INCLUDED
#define STREAMSDK_H_INCLUDED

#pragma once

#ifdef _WIN32
#ifdef STREAMSDK_EXPORTS
#ifdef __cplusplus
#define STREAMSDK_API extern "C" __declspec(dllexport)
#else
#define STREAMSDK_API __declspec(dllexport)
#endif
#else
#ifdef __cplusplus
#define STREAMSDK_API extern "C" __declspec(dllimport)
#else
#define STREAMSDK_API __declspec(dllexport)
#endif
#endif

#ifndef CALLBACK
#define CALLBACK __stdcall
#endif

#else
#ifdef __cplusplus
#define STREAMSDK_API extern "C"
#else
#define STREAMSDK_API
#endif
#ifndef CALLBACK
#define CALLBACK
#endif
#endif


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define __IN
#define __OUT

#pragma pack(push,8)
enum streamsdk_enum_error_code
{
	STREAMSDK_EC_OK = 0,				/** �������óɹ� **/
	STREAMSDK_EC_FAIL = 1,				/** ��������ʧ�� **/
	STREAMSDK_EC_TIMEOUT = 2,			/** ���糬ʱ **/
	STREAMSDK_EC_LIMIT,
};

/* StreamSDK �ӿ�
 * StreamSDK Interfaces

 *  �����ַ����ĺ������������ڴ���bufferָ��ǰ����Ҫ���䲻С��STREAMSDK_STR_BUFSZ�ֽڵ��ڴ�ռ�
 *  Caller should be responsible for allocating enough memory, when passing char * buffers.
    The buffer size should be at least STREAMSDK_STR_BUFSZ bytes, if no other request is specified.
 *  Callback function pointer may be set to NULL to disable callback
 *  
 */
enum streamsdk_enum_buffer
{
	STREAMSDK_STR_BUFSZ = 256,
};

/** ͼ�����ص���ɫ��ʽ **/
enum streamsdk_enum_pix_type
{
	STREAMSDK_PIX_RGB,					/** RGBRGB... ÿ������24λ��������**/
	STREAMSDK_PIX_Y420,					/** YUV420��Yƽ�棬Uƽ���Vƽ�� **/
	STREAMSDK_PIX_GRAY,					/** �Ҷȣ�ÿ������8λ **/
	STREAMSDK_PIX_BGR,					/** BGRBGR... **/
};

/** ֡���������� **/
typedef struct streamsdk_st_buffer_
{
	void *			buf_ptr;			/** ֡������ָ�� **/
	unsigned int	buf_size;			/** ֡��С **/
	unsigned int	buf_pts;			/** ֡���к� **/
} streamsdk_st_buffer;

/** ͼ������ **/
typedef struct streamsdk_st_image_
{
	void *	img_ptr;					/** ͼ�����ָ�� **/
	int		img_w;						/** ͼ����(����) **/
	int		img_h;						/** ͼ��߶�(����) **/
	int		img_linesize;				/** ͼ���д�С(�ֽ�) **/
	int		img_pts;					/** ͼ�����к� **/
	int		img_type;					/** ͼ�����ظ�ʽ, streamsdk_enum_pix_type **/
} streamsdk_st_image;

/** ����������� **/
typedef struct streamsdk_st_decoder_param_
{
	int		dec_w;						/** ������(����) **/
	int		dec_h;						/** ����߶�(����) **/
	int		pix_type;					/** ͼ�����ظ�ʽ, streamsdk_enum_pix_type **/
} streamsdk_st_decoder_param;

typedef struct streamsdk_st_recorder_param_
{
	int		rec_w;
	int		rec_h;
	float	fps;
} streamsdk_st_recorder_param;

typedef struct streamsdk_st_event_
{
	char * event;
	char * id;
	int pts;
	double value;
}streamsdk_st_event;

typedef void * HSTREAM;					/** ����� **/
typedef void * HDECODER;				/** ��������� **/
typedef void * HRECORDER;				/** ¼������� **/

/** ����֡�ص����� **/
typedef void (CALLBACK * streamsdk_cb_grabber)(int error,__IN streamsdk_st_buffer * ,__IN void * user_data);
/** ͼ��֡�ص����� **/
typedef void (CALLBACK * streamsdk_cb_image_grabber)(int error,__IN streamsdk_st_image * ,__IN void * user_data);
/** �¼�֡�ص����� **/
typedef void (CALLBACK * streamsdk_cb_event_grabber)(int error,__IN streamsdk_st_event * ,__IN void * user_data);
#pragma pack(pop)

/********** ͨ�� common **********/
/** �汾����4��������������Ҫ�ɵ��ö����䣬
    version number is an array of 4 integers, caller should allocate the array before passing the pointer 
**/
STREAMSDK_API int streamsdk_get_version(__OUT int * ver_no);	
STREAMSDK_API int streamsdk_get_version_str(__OUT char * ver_info);
/** �̳߳ش�С�����ݼ�������û�������ȷ������Ҫ��������һ����CPU�ĺ�����һ�¿��Է����������, ���κ�������ǰ���÷�����Ч
    Try to set it according to your number of CPU cores so you can 
    make use of the whole performace of your computer.  Call before any stream operations initiated **/
STREAMSDK_API int streamsdk_set_thread_pool_size(int num);	

/********** ������ stream operations **********/
/** �̰߳�ȫ��
      ��ͬһ��HSTREAM����Ĳ���ȫ
	  �Բ�ͬHSTREAM�����ȫ
**/

/** ����һ���������HSTREAM�������ҪHSTREAM
	���룺
		link		Ŀ���豸IP��ַ������
		port_no		����˿ں�
	�����
		hstream		HSTREAM���
	���أ�
		�ɹ�����STREAMSDK_EC_OK����������STREAMSDK_EC_FAIL
**/
STREAMSDK_API int streamsdk_create_stream(__IN char * link,unsigned short port_no,__OUT HSTREAM *);		

/** ����HSTREAM���
	���룺
		hstream		HSTREAM���
	�����
		
	���أ�
		�ɹ�����STREAMSDK_EC_OK����������STREAMSDK_EC_FAIL
**/
STREAMSDK_API int streamsdk_destroy_stream(HSTREAM hstream);

/** ��ʼ�����գ��趨����֡�ص�����
	����:
		hstream				HSTREAM���
		path				��������URL·��
		max_packet_size		���֡��С,������ʱ����Ļ������Ĵ�С
		grabber				����֡�ص�����,��(NULL)��ʾ���趨�ص�����
		user_data			�û�ָ�룬�ⲻ��ı������ݣ�ֱ���ڻص������з���
	����:
		�ɹ�����STREAMSDK_EC_OK�����糬ʱ����STREAMSDK_EC_TIMEOUT����������STREAMSDK_EC_FAIL
**/
STREAMSDK_API int streamsdk_start_stream(HSTREAM hstream,__IN char * path,int max_packet_size,streamsdk_cb_grabber grabber,__IN void * user_data);

/** ֹͣ�����գ��ص������ڴ˺������óɹ��󽫲��ᱻ����
	���룺
		hstream				HSTREAM���
	���أ�
		�ɹ�����STREAMSDK_EC_OK����������STREAMSDK_EC_FAIL
**/
STREAMSDK_API int streamsdk_stop_stream(HSTREAM hstream);

/** �޸Ļص�����ָ��
	���룺
		hstream		HSTREAM���
		grabber		����ص�����ָ�룬��(NULL)��ʾ���趨�ص�����
		user_data	�û�ָ�룬�ⲻ��ı������ݣ�ֱ���ڻص������з���
	���أ�
		�ɹ�����STREAMSDK_EC_OK����������STREAMSDK_EC_FAIL
**/
STREAMSDK_API int streamsdk_set_stream_grabber(HSTREAM hstream,streamsdk_cb_grabber grabber,__IN void * user_data); 

/********** ���������� decoder operations **********/
/** �̰߳�ȫ��
      ��ͬһ��HDECODER����Ĳ���ȫ
	  �Բ�ͬHDECODER�����ȫ
**/

/** ����һ������������HSTREAMָ���������
    ����:
	    hstream		������������
		param		�������Ĳ���
	���:
		hdecoder	���������
	���أ�
		�ɹ�����STREAMSDK_EC_OK����������STREAMSDK_EC_FAIL
**/
STREAMSDK_API int streamsdk_create_h264_decoder(HSTREAM hstream,__IN streamsdk_st_decoder_param *param,__OUT HDECODER *hdecoder);

/** ���ٽ����� 
	���룺
		hdecoder	���������
	���أ�
		�ɹ�����STREAMSDK_EC_OK����������STREAMSDK_EC_FAIL
**/
STREAMSDK_API int streamsdk_destroy_h264_decoder(HDECODER hdecoder);

/** ��ʼ���� 
	���룺
		hdecoder	���������
		grabber		����ص�����ָ��,��(NULL)��ʾ���趨�ص�����
		user_data	�û�ָ�룬�ⲻ��ı������ݣ�ֱ���ڻص������з���
	�����
	
	���أ�
		�ɹ�����STREAMSDK_EC_OK����������STREAMSDK_EC_FAIL
**/
STREAMSDK_API int streamsdk_start_h264_decoder(HDECODER hdecoder,streamsdk_cb_image_grabber grabber,__IN void * user_data);

/** ֹͣ���룬�ص������ڴ˺������óɹ��󽫲��ᱻ����
	���룺
		hdecoder	HDECODER���

	���أ�
		�ɹ�����STREAMSDK_EC_OK����������STREAMSDK_EC_FAIL
**/
STREAMSDK_API int streamsdk_stop_h264_decoder(HDECODER hdecoder);

/** �޸Ļص�����ָ��
	���룺
		hdecoder	HDECODER���
		grabber		����ص�����ָ�룬��(NULL)��ʾ���趨�ص�����
		user_data	�û�ָ�룬�ⲻ��ı������ݣ�ֱ���ڻص������з���
	���أ�
		�ɹ�����STREAMSDK_EC_OK����������STREAMSDK_EC_FAIL
**/
STREAMSDK_API int streamsdk_set_image_grabber(HDECODER hdecoder,streamsdk_cb_image_grabber grabber,__IN void * user_data);

/***** recorder operations ****/
STREAMSDK_API int streamsdk_create_mp4_recorder(HSTREAM h,__IN char * filename,__IN streamsdk_st_recorder_param *,__OUT HRECORDER *);
STREAMSDK_API int streamsdk_destroy_mp4_recorder(HRECORDER h);
STREAMSDK_API int streamsdk_start_mp4_recorder(HRECORDER h);
STREAMSDK_API int streamsdk_stop_mp4_recorder(HRECORDER h);

/***** event operations ****/
STREAMSDK_API int streamsdk_create_event_decoder(HSTREAM h,__OUT HDECODER *);
STREAMSDK_API int streamsdk_destroy_event_decoder(HDECODER h);
STREAMSDK_API int streamsdk_start_event_decoder(HDECODER h,streamsdk_cb_event_grabber grabber,__IN void * user_data);
STREAMSDK_API int streamsdk_stop_event_decoder(HDECODER h);
STREAMSDK_API int streamsdk_set_event_grabber(HDECODER h,streamsdk_cb_event_grabber grabber,__IN void * user_data);
#endif
