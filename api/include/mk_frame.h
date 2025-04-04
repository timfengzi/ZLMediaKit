﻿/*
 * Copyright (c) 2016-present The ZLMediaKit project authors. All Rights Reserved.
 *
 * This file is part of ZLMediaKit(https://github.com/ZLMediaKit/ZLMediaKit).
 *
 * Use of this source code is governed by MIT-like license that can be found in the
 * LICENSE file in the root of the source tree. All contributing project authors
 * may be found in the AUTHORS file in the root of the source tree.
 */

#ifndef ZLMEDIAKIT_MK_FRAME_H
#define ZLMEDIAKIT_MK_FRAME_H

#include "mk_common.h"

#ifdef __cplusplus
extern "C" {
#endif

// 是否为关键帧  [AUTO-TRANSLATED:b999067c]
// cpp
//是否为关键帧
#define MK_FRAME_FLAG_IS_KEY (1 << 0)
// 是否为配置帧(sps/pps/vps等)  [AUTO-TRANSLATED:cf504832]
// 是否为配置帧(sps/pps/vps等)
#define MK_FRAME_FLAG_IS_CONFIG (1 << 1)
// 是否可丢弃的帧(sei/aud)  [AUTO-TRANSLATED:6481fe69]
// 是否可丢弃的帧(sei/aud)
#define MK_FRAME_FLAG_DROP_ABLE  (1 << 2)
// 是否不可单独解码的帧(多slice的非vcl帧)  [AUTO-TRANSLATED:cb4da662]
// 是否不可单独解码的帧(多slice的非vcl帧)
#define MK_FRAME_FLAG_NOT_DECODE_ABLE (1 << 3)

// codec id常量定义  [AUTO-TRANSLATED:dbc838b6]
// codec id常量定义
API_EXPORT extern const int MKCodecH264;
API_EXPORT extern const int MKCodecH265;
API_EXPORT extern const int MKCodecAAC;
API_EXPORT extern const int MKCodecG711A;
API_EXPORT extern const int MKCodecG711U;
API_EXPORT extern const int MKCodecOpus;
API_EXPORT extern const int MKCodecL16;
API_EXPORT extern const int MKCodecVP8;
API_EXPORT extern const int MKCodecVP9;
API_EXPORT extern const int MKCodecAV1;
API_EXPORT extern const int MKCodecJPEG;

typedef struct mk_frame_t *mk_frame;

// 用户自定义free回调函数  [AUTO-TRANSLATED:dc96ff2d]
// 用户自定义free回调函数
typedef void(API_CALL *on_mk_frame_data_release)(void *user_data, char *ptr);

/**
 * 创建frame对象，并返回其引用
 * @param codec_id 编解码类型，请参考MKCodecXXX定义
 * @param dts 解码时间戳，单位毫秒
 * @param pts 显示时间戳，单位毫秒
 * @param data 单帧数据
 * @param size 单帧数据长度
 * @param cb data指针free释放回调, 如果为空，内部会拷贝数据
 * @param user_data data指针free释放回调用户指针
 * @return frame对象引用
 * Create a frame object and return its reference.
 * @param codec_id Encoding and decoding type, please refer to MKCodecXXX definition.
 * @param dts Decoding timestamp, in milliseconds.
 * @param pts Display timestamp, in milliseconds.
 * @param data Single frame data.
 * @param size Single frame data length.
 * @param cb data pointer free release callback, if empty, the data will be copied internally.
 * @param user_data data pointer free release callback user pointer.
 * @return frame object reference.
 
 * [AUTO-TRANSLATED:0481221b]
 */
API_EXPORT mk_frame API_CALL mk_frame_create(int codec_id, uint64_t dts, uint64_t pts, const char *data, size_t size,
                                            on_mk_frame_data_release cb, void *user_data);
API_EXPORT mk_frame API_CALL mk_frame_create2(int codec_id, uint64_t dts, uint64_t pts, const char *data, size_t size,
                                             on_mk_frame_data_release cb, void *user_data, on_user_data_free user_data_free);
/**
 * 减引用frame对象
 * @param frame 帧对象引用
 * Decrement the reference of the frame object.
 * @param frame Frame object reference.
 
 * [AUTO-TRANSLATED:53b5a750]
 */
API_EXPORT void API_CALL mk_frame_unref(mk_frame frame);

/**
 * 引用frame对象
 * @param frame 被引用的frame对象
 * @return 新的对象引用
 * Reference the frame object.
 * @param frame The referenced frame object.
 * @return New object reference.
 
 * [AUTO-TRANSLATED:f772813d]
 */
API_EXPORT mk_frame API_CALL mk_frame_ref(mk_frame frame);

/**
 * 获取frame 编码codec类型，请参考MKCodecXXX定义
 * Get the frame encoding codec type, please refer to MKCodecXXX definition.
 
 * [AUTO-TRANSLATED:b3a34bb8]
 */
API_EXPORT int API_CALL mk_frame_codec_id(mk_frame frame);

/**
 * 获取帧编码codec名称
 * Get the frame encoding codec name.
 
 * [AUTO-TRANSLATED:6c3129d7]
 */
API_EXPORT const char* API_CALL mk_frame_codec_name(mk_frame frame);

/**
 * 帧是否为视频
 * Whether the frame is video.
 
 * [AUTO-TRANSLATED:c43dbd4e]
 */
API_EXPORT int API_CALL mk_frame_is_video(mk_frame frame);

/**
 * 获取帧数据指针
 * Get the frame data pointer.
 
 * [AUTO-TRANSLATED:bf454f3b]
 */
API_EXPORT const char* API_CALL mk_frame_get_data(mk_frame frame);

/**
 * 获取帧数据指针长度
 * Get the length of the frame data pointer.
 
 * [AUTO-TRANSLATED:8a76acf2]
 */
API_EXPORT size_t API_CALL mk_frame_get_data_size(mk_frame frame);

/**
 * 返回帧数据前缀长度，譬如H264/H265前缀一般是0x00 00 00 01,那么本函数返回4
 * Return the length of the frame data prefix, for example, the H264/H265 prefix is generally 0x00 00 00 01, then this function returns 4.
 
 * [AUTO-TRANSLATED:352c7cfc]
 */
API_EXPORT size_t API_CALL mk_frame_get_data_prefix_size(mk_frame frame);

/**
 * 获取解码时间戳，单位毫秒
 * Get the decoding timestamp, in milliseconds.
 
 * [AUTO-TRANSLATED:049f1339]
 */
API_EXPORT uint64_t API_CALL mk_frame_get_dts(mk_frame frame);

/**
 * 获取显示时间戳，单位毫秒
 * Get the display timestamp, in milliseconds.
 
 * [AUTO-TRANSLATED:4ab081a7]
 */
API_EXPORT uint64_t API_CALL mk_frame_get_pts(mk_frame frame);

/**
 * 获取帧flag，请参考 MK_FRAME_FLAG
 * Get the frame flag, please refer to MK_FRAME_FLAG.
 
 * [AUTO-TRANSLATED:6fdf971c]
 */
API_EXPORT uint32_t API_CALL mk_frame_get_flags(mk_frame frame);

//////////////////////////////////////////////////////////////////////

typedef struct mk_buffer_t *mk_buffer;
typedef struct mk_frame_merger_t *mk_frame_merger;

/**
 * 创建帧合并器
 * @param type 起始头类型，0: none, 1: h264_prefix/AnnexB(0x 00 00 00 01), 2: mp4_nal_size(avcC)
 * @return 帧合并器
 * Create a frame merger.
 * @param type Starting header type, 0: none, 1: h264_prefix/AnnexB(0x 00 00 00 01), 2: mp4_nal_size(avcC)
 * @return Frame merger.
 
 * [AUTO-TRANSLATED:385eedd7]
 */
API_EXPORT mk_frame_merger API_CALL mk_frame_merger_create(int type);

/**
 * 销毁帧合并器
 * @param ctx 对象指针
 * Destroy the frame merger.
 * @param ctx Object pointer.
 
 * [AUTO-TRANSLATED:0c9aad7b]
 */
API_EXPORT void API_CALL mk_frame_merger_release(mk_frame_merger ctx);

/**
 * 清空merger对象缓冲，方便复用
 * @param ctx 对象指针
 * Clear the merger object buffer for reuse.
 * @param ctx Object pointer.
 
 * [AUTO-TRANSLATED:6b1d2209]
 */
API_EXPORT void API_CALL mk_frame_merger_clear(mk_frame_merger ctx);

/**
 * 合并帧回调函数
 * @param user_data 用户数据指针
 * @param dts 解码时间戳
 * @param pts 显示时间戳
 * @param buffer 合并后数据buffer对象
 * @param have_key_frame 合并后数据中是否包含关键帧
 * Frame merging callback function.
 * @param user_data User data pointer.
 * @param dts Decoding timestamp.
 * @param pts Display timestamp.
 * @param buffer Merged data buffer object.
 * @param have_key_frame Whether the merged data contains a key frame.
 
 * [AUTO-TRANSLATED:ff78df4f]
 */
typedef void(API_CALL *on_mk_frame_merger)(void *user_data, uint64_t dts, uint64_t pts, mk_buffer buffer, int have_key_frame);

/**
 * 输入frame到merger对象并合并
 * @param ctx 对象指针
 * @param frame 帧数据
 * @param cb 帧合并回调函数
 * @param user_data 帧合并回调函数用户数据指针
 * Input frame to the merger object and merge.
 * @param ctx Object pointer.
 * @param frame Frame data.
 * @param cb Frame merging callback function.
 * @param user_data Frame merging callback function user data pointer.
 
 * [AUTO-TRANSLATED:83aa1436]
 */
API_EXPORT void API_CALL mk_frame_merger_input(mk_frame_merger ctx, mk_frame frame, on_mk_frame_merger cb, void *user_data);

/**
 * 强制flush merger对象缓冲，调用此api前需要确保先调用mk_frame_merger_input函数并且回调参数有效
 * @param ctx 对象指针
 * Force flush the merger object buffer. Before calling this API, make sure to call the mk_frame_merger_input function first and the callback parameters are valid.
 * @param ctx Object pointer.
 
 * [AUTO-TRANSLATED:42bb104c]
 */
API_EXPORT void API_CALL mk_frame_merger_flush(mk_frame_merger ctx);

//////////////////////////////////////////////////////////////////////

typedef struct mk_mpeg_muxer_t *mk_mpeg_muxer;

/**
 * mpeg-ps/ts 打包器输出回调函数
 * @param user_data 设置回调时的用户数据指针
 * @param muxer 对象
 * @param frame 帧数据
 * @param size 帧数据长度
 * @param timestamp 时间戳
 * @param key_pos 是否关键帧
 * mpeg-ps/ts packer output callback function.
 * @param user_data User data pointer set during callback.
 * @param muxer Object.
 * @param frame Frame data.
 * @param size Frame data length.
 * @param timestamp Timestamp.
 * @param key_pos Whether it is a key frame.
 
 * [AUTO-TRANSLATED:14c103a2]
 */
typedef void(API_CALL *on_mk_mpeg_muxer_frame)(void *user_data, mk_mpeg_muxer muxer, const char *frame, size_t size, uint64_t timestamp, int key_pos);

/**
 * mpeg-ps/ts 打包器
 * @param cb 打包回调函数
 * @param user_data 回调用户数据指针
 * @param is_ps 是否是ps
 * @return 打包器对象
 * mpeg-ps/ts packer.
 * @param cb Packing callback function.
 * @param user_data Callback user data pointer.
 * @param is_ps Whether it is ps.
 * @return Packer object.
 
 * [AUTO-TRANSLATED:6526b871]
 */
API_EXPORT mk_mpeg_muxer API_CALL mk_mpeg_muxer_create(on_mk_mpeg_muxer_frame cb, void *user_data, int is_ps);

/**
 * 删除mpeg-ps/ts 打包器
 * @param ctx 打包器
 * Delete the mpeg-ps/ts packer.
 * @param ctx Packer.
 
 * [AUTO-TRANSLATED:0b533391]
 */
API_EXPORT void API_CALL mk_mpeg_muxer_release(mk_mpeg_muxer ctx);

/**
 * 添加音视频track
 * @param ctx mk_mpeg_muxer对象
 * @param track mk_track对象，音视频轨道
 * Add audio/video track.
 * @param ctx mk_mpeg_muxer object.
 * @param track mk_track object, audio/video track.
 
 * [AUTO-TRANSLATED:f2082619]
 */
API_EXPORT void API_CALL mk_mpeg_muxer_init_track(mk_mpeg_muxer ctx, void* track);

/**
 * 初始化track完毕后调用此函数，
 * 在单track(只有音频或视频)时，因为ZLMediaKit不知道后续是否还要添加track，所以会多等待3秒钟
 * 如果产生的流是单Track类型，请调用此函数以便加快流生成速度，当然不调用该函数，影响也不大(会多等待3秒)
 * @param ctx 对象指针
 * Call this function after the track is initialized.
 * In the case of a single track (only audio or video), because ZLMediaKit does not know whether to add more tracks later, it will wait for an additional 3 seconds.
 * If the generated stream is a single Track type, please call this function to speed up the stream generation. Of course, if you don't call this function, the impact is not big (it will wait for an additional 3 seconds).
 * @param ctx Object pointer.
 
 * [AUTO-TRANSLATED:f40d41cb]
 */
API_EXPORT void API_CALL mk_mpeg_muxer_init_complete(mk_mpeg_muxer ctx);

/**
 * 输入frame对象
 * @param ctx mk_mpeg_muxer对象
 * @param frame 帧对象
 * @return 1代表成功，0失败
 * Input frame object.
 * @param ctx mk_mpeg_muxer object.
 * @param frame Frame object.
 * @return 1 means success, 0 means failure.
 
 
 * [AUTO-TRANSLATED:46523906]
 */
API_EXPORT int API_CALL mk_mpeg_muxer_input_frame(mk_mpeg_muxer ctx, mk_frame frame);

//////////////////////////////////////////////////////////////////////
#if defined(ENABLE_RTPPROXY)

typedef struct mk_ps_decoder_t *mk_ps_decoder;

typedef void (API_CALL *on_mk_ps_decoder_stream)(void *user_data, int stream, int codecid, const void *ext, size_t ext_len, int finish);
typedef void(API_CALL *on_mk_ps_decoder_frame)(void *user_data, int stream, int codecid, int flags, int64_t pts, int64_t dts, const void *data, size_t bytes);

/**
 * 创建一个ps解析器
 * @param scb stream 回调; 可选, 如果明确知道数据类型也许不需要此回调创建track?
 * @param dcb 数据回调；必填
 * @param user_data 用户自定义数据
 * @return
 */
API_EXPORT mk_ps_decoder API_CALL mk_ps_decoder_create(on_mk_ps_decoder_stream scb, on_mk_ps_decoder_frame dcb, void * user_data);

/**
 * 释放ps解析器
 * @param ctx
 */
API_EXPORT void API_CALL mk_ps_decoder_release(mk_ps_decoder ctx);

/**
 * 输入ps数据
 * @param ctx ps解析器指针
 * @param data ps数据指针
 * @param bytes 数据长度
 */
API_EXPORT void API_CALL mk_ps_decoder_input(mk_ps_decoder ctx, const char * data, size_t bytes);


# endif

#ifdef __cplusplus
}
#endif

#endif //ZLMEDIAKIT_MK_FRAME_H
