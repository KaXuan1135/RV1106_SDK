/*
	RGB -> jpg file
 */
#ifndef __SNAPSHOT_H__
#define __SNAPSHOT_H__

#include "rk_mpi_sys.h"
#include <rga/im2d.h>
#include <rga/rga.h>


#ifdef __cplusplus
extern "C" {
#endif
// input format : RK_FORMAT_RGBA_8888, RK_FORMAT_BGR_888, IMAGE_TYPE_RGB888, IMAGE_TYPE_NV12 ...
// channel: 0 ~15, cannot use same value in multi process.
void * snapshot_init(int w, int h, int channel, int format);
void* snapshot_get_osd_hd(void *hd_);
int snapshot_run_once(void *hd_, unsigned char *nv12_data,  char *out_file_path);
int snapshot_run_once_ex(void *hd_, unsigned char *nv12_data,  char *pbuff,int *nBuffLen);
void snapshot_deinit(void *hd_);

int snapshot_yuv_drawBox(void *hd_, unsigned char *nv12_data,int x_p, int y_p, int w_p, int h_p, int thick, unsigned int color);

int snapshot_yuv_drawRoiAera(void *hd_,unsigned char *nv12_data,void *pAera , int thick, unsigned int color);

//hard osd : 0 <= id < 8
int snapshot_yuv_drawOsd(void *hd_, int Id,unsigned char *nv12_data,int x_p, int y_p,const char *pData, int font_size,unsigned int color);
//soft osd : call times have no limit
int snapshot_yuv_drawSwOsd(void *hd_, unsigned char *nv12_data,int x_p, int y_p,const char *pData, int font_size,unsigned int color);

int snapshot_yuv_draw_line(void *hd_, unsigned char *nv12_data,int x1, int y1, int x2, int y2, int thick,unsigned int color);

int snapshot_set_quality(void *hd_, int qfactor);

#ifdef __cplusplus
}
#endif

#endif
