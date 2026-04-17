#include "common.h"

#include "comm_type.h"
#include "comm_codec.h"
#include <rga/rga.h>
#include <rga/im2d.h>

#include "codec2_process.h"
#include "osd_if.h"
// #include "rga_proc.h"
#include "RgaProc.h"

#include "snapshot.h"
#include <rk_mpi_mb.h>
#include "rkai_demo.h"

// void * rga_hd[2];
RgaProc *rga_hd[2];

static unsigned char *rgb_buff[MAX_STREAM_NUM];
static CROP_RECT crop[] = {
	{100, 100, 640, 480},
	{100, 100, 640, 480},
	{100, 100, 640, 480},
	{100, 100, 640, 480}
};

extern "C" int yuv_data_coming(int stream_index, void *mb); 

extern "C" void notify_ROI_changed(int channel_no)
{
	;
}

static nn_object_array_t ai_result;

static void * ss_hd ;  //截图句柄


//#define RGB_SAVE_TO_FILE
#define JPEG_OSD_TEST
#define TEST_AI_RESULT
#define RK_IVA_ENABLE



extern "C" int comm_ai_process(int stream_index, void * mb, void *puser)
{
	int ret;
	static int count = 0;
		   
	if(stream_index == CAM0_STREAM_MAIN)
	{
		// void * hd;]
        RgaProc * hd;
		unsigned char * buff = rgb_buff[CAM0_STREAM_MAIN];
		bool ret;
//		os_dbg("CAM%d_STREAM process(%d)...", stream_index);
		//1. 格式转换, yuv -> crop & rgb
		hd = rga_hd[app_get_camid(stream_index)];		
		if(hd)
		{
            ret = hd->rga_proc_covert_rgb((VIDEO_FRAME_INFO_S *)mb, &crop[stream_index], &buff, true);
			// ret = rga_proc_covert_rgb(hd, (VIDEO_FRAME_INFO_S *)mb, &crop[stream_index], &buff, true);
			if(ret == false) os_dbg("rga convert fail!!!");
		}

#ifdef RGB_SAVE_TO_FILE
		os_dbg("rga_proc_covert_rgb return = %d", ret);
		if(ret)
		{
			
			if((count % 10) == 0)
			{
				char fn[80];
				sprintf(fn, "/mnt/sdcard/%d.rgb", count);
				FILE *fp = fopen(fn, "wb");
				if(fp && buff)
				{
						fwrite(buff, 1, crop.w * crop.h * 3, fp);
						fclose(fp);
				}
			}
		}
#endif 	

#ifdef JPEG_OSD_TEST
		if(ss_hd && ((count % 50) == 0))
		{
			char fn[70];
			char osd_str[50];
			Osd_If * osd_hd = (Osd_If*)snapshot_get_osd_hd(ss_hd);
			osd_hd->set_font_bg_color(FONT_BG_COLOR_1);
			sprintf(osd_str, "snap test %d....", count);
			if(osd_hd)osd_hd->SetOsdTip(0, 300, 300, osd_str, 0xff0000, 50, true);
			
			os_dbg("+++++++++++++++++++++++++++++");
			sprintf(fn, "/userdata/snapshot/ss.jpg");
			snapshot_run_once(ss_hd, (unsigned char*)RK_MPI_MB_Handle2VirAddr(((VIDEO_FRAME_INFO_S*)mb)->stVFrame.pMbBlk), fn);
			os_dbg("-----------------------------");
		}
#endif
	
		//2. 这里开始AI处理,
#ifdef RK_IVA_ENABLE
		rmm_process_rgb(buff, crop[stream_index].w, crop[stream_index].h);
#endif		
		
		//3. 后处理，比如根据结果，画osd 等。
#ifdef TEST_AI_RESULT 
		if((count % 10) == 0) // 注意： 坐标没有变化的话，不需要重复更新。
		{
			int i;
			ai_result.count = 8;
			ai_result.object[0].box.left = 100;
			ai_result.object[0].box.right = 180;
			ai_result.object[0].box.top = 100;
			ai_result.object[0].box.bottom = 180;
			ai_result.object[0].color = 0xffff00;
			ai_result.object[0].id = 1;

			for(i = 1; i <  ai_result.count; i++)
			{
				ai_result.object[i].box.left = ai_result.object[i-1].box.left + 85;
				ai_result.object[i].box.right = ai_result.object[i-1].box.right + 85;
				ai_result.object[i].box.top = 100;
				ai_result.object[i].box.bottom = 180;
				ai_result.object[i].id = i + 1;
				if(i < 4)
					ai_result.object[i].color = 0xff0000;
				else if ( i < 6 ) 
					ai_result.object[i].color = 0x00ff00;
				else if ( i < 8 )
					ai_result.object[i].color = 0x0000ff;
			}
			
			// AI 分辨率可能与 stream main/sub 分辨率不同，需要转换坐标。
			int target_stream = app_get_main_index_from_ai(stream_index);
			app_covert_nn_coordinate(stream_index, target_stream, &ai_result);
			
			ret = app_set_nn_obj(target_stream, &ai_result);  //表示rtsp 的主流
			//os_dbg("app_set_nn_obj ret = %d", ret);
			
			//测试YUV画线
			avcodec_osd_line_t oline;
			oline.index = 3;
			oline.enable = 1;
			oline.x = 12; oline.y = 12;
			oline.x2 = 1910; oline.y2 = 1070;
			oline.thick = 2;
			oline.color = 0xff0000;
			app_set_stream_sw_osd_line(CAM0_STREAM_MAIN, &oline);

			oline.index = 4;
			oline.x = 10; oline.y = 10;
			oline.x2 = 1910; oline.y2 = 10;
			oline.color = 0xff;
			app_set_stream_sw_osd_line(CAM0_STREAM_MAIN, &oline);
		}
#endif		
	}
	else
	{
//		os_dbg("not process stream(%d)!!!",  stream_index);
	}
	
	count ++;
    	
	return OS_SUCCESS;
}

extern "C" int comm_ai_init()
{
	int ret;
		int w, h;
	os_dbg(" enter");

	app_get_resolution(CAM0_STREAM_MAIN, &w, &h, NULL);
    rga_hd[app_get_camid(CAM0_STREAM_MAIN)] = new RgaProc(w, h, RK_FMT_YUV420SP);
	// rga_hd[app_get_camid(CAM0_STREAM_MAIN)] = rga_proc_init(w, h, RK_FMT_YUV420SP);
	
	//. set para
	app_set_ai_process_para(CAM0_STREAM_MAIN, comm_ai_process,   4, NULL);
	
	rgb_buff[CAM0_STREAM_MAIN] = (unsigned char *)malloc(w * h * 3);
	
	//for test
	ss_hd = snapshot_init(w, h, 7, RK_FMT_YUV420SP);
	
	
	//AI 初始化...
#ifdef RK_IVA_ENABLE
	rmm_yuv_handle_init();
#endif	
	
	os_dbg(" exit");
	return OS_SUCCESS;
}



