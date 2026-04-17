#include "common.h"
#include "comm_type.h"
#include "param.h"
#include "comm_codec.h"
#include "codec2_process.h"
#include "comm_app.h"
#include "comm_misc.h"
#include "encnetLib.h"
#include "webrtc.h"
#include "atLib.h"
#include "rknn_api.h"
static int g_rtsp_port = 554;

////////////////////  音视频回调函数，不要阻塞 ///////////////

//#define TEST_SAVE_FRAME

static int g_test_fd = -1;
static int g_frame_count =0;
static char *g_test_name = "/tmp/test.h264";
static int g_bfirst = 1;
int comm_app_stream_callback(int ch,int sub_ch,void *pData,void *user_data)
{
	av_frame_t *pFrame = (av_frame_t *)pData;
	if(pFrame)
	{
#ifdef TEST_SAVE_FRAME	
		if(sub_ch == 0)	//only main stream
		{
			if(g_bfirst == 1)
			{
				if(pFrame->frame_head.frame_type != CODEC_I_FRAME_TYPE)
				{
					return 0;
				}
				else
				{
					g_bfirst = 0;
				}
			}
			if(g_frame_count <3000)
			{
				if(g_test_fd == -1)
				{
					g_test_fd = open(g_test_name,O_RDWR|O_CREAT);
				}
				
				if(g_test_fd && pFrame->frame_head.frame_type != CODEC_A_FRAME_TYPE)
				{
					os_comm_writen(g_test_fd,pFrame->frame_data,pFrame->frame_head.frame_size);
					g_frame_count ++;
				}
			}
			else if(g_test_fd != -1)
			{
				os_close(g_test_fd);
				g_test_fd = -1;
			}
		}
#endif		
	}
	return 0;
}

//extern "C" int webrtc_init();
void start_app_service()
{
	//system init
//	system("rk_mpi_amix_test -C 0 --control \"ADC Mode\" --value \"SingadcL\"");
//	system("rk_mpi_amix_test -C 0 --control \"ADC Digital Left Volume\"  --value \"250\"");	
	
	comm_sys_config_t sys_config;
	server_config_t *pConfig = get_server_config();
	comm_param_getSysConfig(&sys_config);
	os_dbg("onvif_enable :%d",pConfig->onvif_enable);
	if(pConfig->onvif_enable)
	{
		app_init_onvif();
	}
	os_dbg("rtsp_enable :%d",pConfig->rtsp_enable);
	if(pConfig->rtsp_enable)
	{	
		comm_start_rtsp(g_rtsp_port);
	}
#if 1	
	os_dbg("gb28181_enable :%d wdt_enable :%d ",pConfig->gb28181_enable,pConfig->wdt_enable);
	if(pConfig->gb28181_enable)
	{
		comm_init_gbtPlatform();
	}
	if(sys_config.enable_4G ||pConfig->dial_enable)		//
	{
		atLib_init();
		atLib_set_apn(pConfig->apn,pConfig->apn_user,pConfig->apn_passwd);
		atLib_startService();
	}	
	if(pConfig->voip_enable)
	{
		comm_init_voip();
	}
	if(pConfig->wdt_enable)
	{
		comm_app_startFeedwatchdogService();
	}
	if(pConfig->rtmp_enable)
	{
		comm_rtmp_init();
	}
#endif	
	comm_custom_rtmp_init();
//	usleep(500000);
//	comm_rtmp_start_push_stream(0,"rtmp://127.0.0.1:1935/live","mainstream");
//	comm_rtmp_start_push_stream(1,"rtmp://127.0.0.1:1935/live","substream");
//  comm_rtmp_stop_push_stream(0);
//  comm_rtmp_stop_push_stream(1)

//	webrtc_init();
}

void start_app()
{
    #define STEP_LOG(step) fprintf(stderr, "\n[STEP CHECK] ===> %s SUCCESS\n", step)

    init_common_lib();
    STEP_LOG("init_common_lib");

    comm_param_initRtcTime();
    comm_param_initParamLib();
    STEP_LOG("comm_param_init (Time/Lib)");

    comm_param_startParamService();
    STEP_LOG("comm_param_startParamService");

    comm_param_startNetwork();
    STEP_LOG("comm_param_startNetwork");

    Client_initService(); // 启动简易客户端服务
    STEP_LOG("Client_initService");

    comm_init_sched();
    STEP_LOG("comm_init_sched");

    comm_app_register_stream_callback(comm_app_stream_callback, NULL);
    comm_app_init();
    STEP_LOG("comm_app_init (Media System Ready)");

    // --- AI 相关：这是你最关心的部分 ---
    comm_ai_init();
    STEP_LOG("comm_ai_init (Algorithm Loaded)");

    app_start_ai_process();
    STEP_LOG("app_start_ai_process (AI Thread Started)");

    // --- 其他外设 ---
    app_init_ircut();
    STEP_LOG("app_init_ircut");

    comm_com_initComLib();
    comm_ptz_start_3AService();
    STEP_LOG("comm_ptz_3AService");

    st_net_startEncNetService();
    STEP_LOG("st_net_startEncNetService");

    start_app_service();
    STEP_LOG("start_app_service (Network Services Ready)");

    app_play_start_voice();
    STEP_LOG("app_play_start_voice (All Systems Go)");
//	st_3512_cncPlatform();
    #undef STEP_LOG
}

void stop_app()
{
	comm_app_deinit();
}
