#pragma once
#ifndef  _VID_FFMPEG_H
#define _VID_FFMPEG_H
#endif // ! _VID_FFMPEG_H


extern "C" {
#include "inttypes.h"    
#include "libavcodec/avcodec.h"    
#include "libavformat/avformat.h"    
#include "libavfilter/avfilter.h"    
#include "libavfilter/buffersink.h"    
#include "libavfilter/buffersrc.h"    
#include "libavutil/avutil.h"    
#include "libswscale/swscale.h"  
#include "libswresample/swresample.h"  
#include "libavutil/avassert.h"  
#include "libavutil/channel_layout.h"  
#include "libavutil/opt.h"  
#include "libavutil/mathematics.h"  
#include "libavutil/timestamp.h"  
};
#include<opencv2\opencv.hpp>
using namespace cv;
#ifndef SERVERDLL_EXPORTS
#define SERVERDLL_API __declspec(dllexport)
#else
#define SERVERDLL_API __declspec(dllimport)
#endif


typedef struct {
	const char *input_file_name;
	const char *output_file_name;
	int frame_width;
	int frame_height;
} IOParam;

typedef struct {
	AVStream *st;
	int64_t next_pts;
	int samples_count;
	AVFrame *frame;
	AVFrame *tmp_frame;

	float t, tincr, tincr2;
	struct SwsContext *sws_ctx;
	struct SwrContext *swr_ctx;
} OutputStream;

class SERVERDLL_API videoWriterFFmpeg
{
public:
	videoWriterFFmpeg();
	~videoWriterFFmpeg();
	//file_name ,bitrate,frame_rate,width,height
	int open(char *, int, int, int, int);
	int write(Mat);
	void close();
private:
	IOParam io;
	int stream_frame_rate;
	int frame_rate;
	int bitrate;
	int videoFrameIdx;
	OutputStream video_st;
	AVOutputFormat *fmt;
	AVFormatContext *oc;
	AVCodec *video_codec;

	//struct SwsContext* sws_ctx;//��ʽת����
	enum AVPixelFormat src_pix_fmt;//��ʽ����
	enum AVPixelFormat dst_pix_fmt;//��ʽ����
	int imgwidthlen;//�п��
};