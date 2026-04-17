#ifndef OSD_C_IF_H
#define OSD_C_IF_H

#include <stdbool.h>

#define FONT_BG_TABLE_LEN 5

enum BorderEffect {
  BORDER_LINE = 0,
  BORDER_DOTTED,
  BORDER_WATERFULL_LIGHT,
};

typedef enum {
	FONT_BG_COLOR_0 =0,
	FONT_BG_COLOR_1 ,
	FONT_BG_COLOR_2,
	FONT_BG_COLOR_3,
	FONT_BG_COLOR_4,
	FONT_BG_COLOR_TOP = FONT_BG_TABLE_LEN,
}FONT_BG_COLOR_INDEX;



//void * osd_create(int enc_chan_id_p, int w, int h);

bool osd_set_tip(void *hd,int region_id,  int x, int y, char* str, unsigned int color,  int font_size, bool have_background);
bool osd_set_bmp(void *hd, int region_id,  int x, int y, char* bmp_path);
bool osd_set_line(void *hd, int region_id, int x1, int y1, int x2, int y2, int display_style, int thick, unsigned int color);
bool osd_set_region_border(void *hd, int region_id, int x_p, int y_p, int w_p, int h_p,  int display_style, int thick, unsigned int color);
bool osd_clear(void * hd, int region_id);
bool osd_config_font_etc(unsigned char alpha, unsigned int* bg_palette_table, const char * fontpath);
bool osd_set_font_bg_color(void *hd, FONT_BG_COLOR_INDEX color);

//下面函数，是软件直接在yuv 画点的
bool yuv_set_region_border(void *hd, void* nv12_buff, int w, int h, int x_p, int y_p, int w_p, int h_p, int thick, unsigned int color);
//bool yuv_set_line(void *hd, void* mb, int x1, int y1, int x2, int y2, int thick, unsigned int color);
void* yuv_get_line_info(void *hd, int x1, int y1, int x2, int y2, int thick, int line_type);
bool yuv_set_line(void *hd, void* line_info, void* nv12_buff, unsigned int color);
bool yuv_release_osd_line_info(void * hd, void * line_info);

bool yuv_set_bitmap(void *hd, void*bitmap, void* nv12_buff, 
									int x, int y, int w, int h, unsigned int color);

// 用于画字符串
void * yuv_get_osd_str_info(void *hd, int x, int y, char* str, unsigned int color,   int font_size);
bool  yuv_set_tip(void *hd, void * nv12_buff, void * str_info);
bool  yuv_release_osd_str_info(void *hd, void * str_info);

//void  osd_delete(void *hd);




#endif