#ifndef __GBTLIB_H__
#define __GBTLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#define 	VOIP_CODE_SIZE					32
#define		VOIP_PASSWD_SIZE				32
#define		VOIP_USERNAME_SIZE				32
#define		VOIP_IP_SIZE					64
#define		VOIP_DOMAIN_SIZE				16
#define		VOIP_STRING_LEN					32
#define		VOIP_MAX_CAMERA_COUNT			64
#define		VOIP_MAX_ALARMIN_COUNT			8
#define		VOIP_MAX_ALARMOUT_COUNT			8
#define		VOIP_DESCRIPTION_LEN			32

#define		MAX_VOIP_BODY_LENGTH			4096
#define 	MAX_VOIP_FRAME_SZIE				512*1024
#define 	MAX_VOIP_NAL_NUM 				12
#define		MAX_VOIP_DIAL_NUM				4
/*****************************************************
		regState value  注册的3种状态值
******************************************************/

#define 	VOIP_REGISTER_NON 				0x00	//没有注册
#define		VOIP_REGISTER_NOW				0x01	//正在注册			
#define 	VOIP_REGISTER_DONE 				0x02	//注册成功
#define		VOIP_LOGOUT_REQUEST				0x04	//请求注销
#define		VOIP_LOGOUT_NOW					0x08	//发送第一次注销成功
#define		VOIP_LOGOUT_DONE				0x10	//注销成功
#define 	VOIP_REGISTER_READY				0x20	//每次准备注册前，要先注销下设备
#define 	VOIP_REGISTER_RUNNING			0x40	//正常操作状态
#define 	VOIP_REQUEST_READY_REGISTER		0x80

typedef struct _VOIP_ChnInfo_T_				//通道信息，包括视频通道，报警输入通道，报警输出通道
{
	int 	chnType;						//通道类型
	int     chnNo;							//通道号			//从1开始
	char    chnID[VOIP_CODE_SIZE];			//通道ID
	char 	chnName[VOIP_STRING_LEN];		//通道名称
}VOIP_ChnInfo;

typedef struct _VOIP_Platform_T_				//平台参数
{
	int			GBT_enable;						//0:不使能 1:使能   平台使能标志
	int  		connectType;						//连接协议    0:tcp  1:udp
	
	char 		platformIP[VOIP_IP_SIZE];    		//平台IP地址
	int  		platformPort;						//平台端口    5060
	char 		platformCode[VOIP_CODE_SIZE];   	//平台编码

	char 		DevDomainID[VOIP_DOMAIN_SIZE];		//设备域ID
	char 		DevCode[VOIP_CODE_SIZE];  			//设备编码或者设备ID
	char		DevAlarmCode[VOIP_CODE_SIZE];		//设备告警业务编码
	char 		password[VOIP_PASSWD_SIZE];  		//设备密码,用于平台验证
	char 		userName[VOIP_USERNAME_SIZE];
	int			expiresTime;						//注册的有效期限
	int			keepAliveTIme;						//心跳保活周期

	int 		cameraCount;						//视频通道数量
	VOIP_ChnInfo cameraInfo[VOIP_MAX_CAMERA_COUNT];
	
	int 		alarmInCount;							//告警输入通道数量
	VOIP_ChnInfo alarmInInfo[VOIP_MAX_ALARMIN_COUNT];	
		
	int 		alarmOutCount;							//告警输出通道数量
	VOIP_ChnInfo alarmOutInfo[VOIP_MAX_ALARMOUT_COUNT];

	int			audioIn_enable;
	VOIP_ChnInfo audioInInfo;						//语音对讲的id

	int			audioOut_enable;
	VOIP_ChnInfo audioOutInfo;

	int 		dialCount;						//预置的电话号码个数
	int			currDialIndex;					//当前拨号号码
	char 		DialNum[MAX_VOIP_DIAL_NUM][VOIP_CODE_SIZE];	// 预置的电话号码
}VOIP_Platform_T;

typedef struct _VOIP_Time_T_		
{
	int 	year;   				//年
	int 	month;					//月
	int 	day;					//日
	int 	hour;					//时
	int 	minute;					//分
	int 	second;					//秒
	int 	zone;					//时区
}VOIP_Time_T;

typedef struct __voip_frame_head_t 
{
    unsigned int	device_type;
    unsigned int	frame_size;
    unsigned int	frame_no;
	unsigned char	video_resolution;
    unsigned char	frame_type;
	unsigned char	frame_rate;
	unsigned char	video_standard;
	unsigned int	sec;
   unsigned int	usec;
	long long		pts;
}voip_frame_head_t;


typedef struct __voip_video_cfg_t
{
	int profile;
	int level_id;
}voip_video_cfg_t;
typedef struct __voip_audio_cfg_t
{
	char	sample_rate;	/* 采样率 0:8k, 1:11.025k, 2:16K, 3:22.050K, 4:24K, 5:32K, 6:44.1K, 7:48K */
	char	bit_width;	/* 位宽 0: 8bit, 1: 16bit */
	char	encode_type;	/* 编码方式 0:原始码流, 1:g711a, 2:g711u, 3:ADPCM, 4:g726_16K, 5: g726_24K*/
}voip_audio_cfg_t;
/******************************************************************************************
*										定义回调类型
*******************************************************************************************/

typedef int(* VOIP_GetPlatformInfo_CB)(void *p_platform);
typedef int(* VOIP_SetPlatformInfo_CB)(void *p_platform);

typedef int(* VOIP_OpenRealTimeChannel_CB)(int chn, int *p_handle, int reserve);
typedef int(* VOIP_CloseRealTimeChannel_CB)(int handle);
typedef int(* VOIP_GetRealTimeFrame_CB)(int handle, char *p_buff, int *p_len);

typedef int(* VOIP_SetDevTime_CB)(void *p_time);

typedef int(* VOIP_Open_AudioChannel)(int chn, int *p_handle, int reserve);			//打开语音
typedef int(* VOIP_GetAudioFrame_CB)(int handle, char *p_buff, int *p_len);			//获取语音
typedef int(* VOIP_SendAudioFrame_CB)(int handle, char *p_buff, int p_len);			//发送语音
typedef int(* VOIP_Close_AudioChannel)(int handle);								//关闭语音

typedef int(* VOIP_GetAudioConfig_CB)(int ch,void *p_audioCfg);
typedef int(* VOIP_GetVideoConfig_CB)(int ch,void *p_videoCfg);

/*********************************************************************************************
								    GBT库启动接口
**********************************************************************************************/

int ST_VOIP_Start(); 
int ST_VOIP_RegState();

int ST_VOIP_startDialog(const char *pDevCode);
int ST_VOIP_stopDialog(const char *pDevCode);

/*********************************************************************************************
								    平台参数回调注册接口
**********************************************************************************************/

void ST_VOIP_RegisterPlatformParamCallBack(VOIP_GetPlatformInfo_CB);		  	//获取平台参数
void ST_VOIP_RegisterSetPlatformParamCallBack(VOIP_SetPlatformInfo_CB);		//设置平台参数

/******************************************************************************************************
									实时流回调注册接口
******************************************************************************************************/

void ST_VOIP_RegisterOpenRealTimeChannelCallBack(VOIP_OpenRealTimeChannel_CB);
void ST_VOIP_RegisterGetRealTimeFrameCallBack(VOIP_GetRealTimeFrame_CB);  	//实时流回调注册接口
void ST_VOIP_RegisterCloseRealTimeChannelCallBack(VOIP_CloseRealTimeChannel_CB);


/********************************************************************************************************
									校时回调注册接口
*********************************************************************************************************/

void ST_VOIP_RegisterSetDevTimeCallBack(VOIP_SetDevTime_CB);


/*******************************************************************************************************
									对讲通道
********************************************************************************************************/


void ST_VOIP_RegisterOpenAudioChannelCallBack(VOIP_Open_AudioChannel);
void ST_VOIP_RegisterCloseAudioChannelCallBack(VOIP_Close_AudioChannel);
void ST_VOIP_RegisterGetAudioFrameCallBack(VOIP_GetAudioFrame_CB);
void ST_VOIP_RegisterSendAudioFrameCallBack(VOIP_SendAudioFrame_CB);
void ST_VOIP_RegisterGetAudioCfgCallBack(VOIP_GetAudioConfig_CB);
void ST_VOIP_RegisterGetVideoCfgCallBack(VOIP_GetVideoConfig_CB);


#ifdef __cplusplus
}
#endif

#endif

