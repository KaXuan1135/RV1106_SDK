/*
 * Copyright	：2007 santachi corp.
 * File name	：netLib.h
 * Description	：network service related global definitions. 
 * Created : liuzx 2007-03-06
 * Modified : zhnagkk 2007-03-15 
 */

#ifndef __NETLIB_H__
#define __NETLIB_H__

#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */


#define PROTOCOL_TCP 0x01
#define PROTOCOL_UDP 0x02
#define PROTOCOL_MCAST 0x03

//==================ACK========================
#define ACK_ERROR_OTHER 0xff //其他错误
#define ACK_SUCCESS 0x00 //成功
#define ACK_ERROR_NAME 0x01 //用户名错误
#define ACK_ERROR_PWD 0x02 //密码错误
#define ACK_ERROR_RIGHT 0x03 //权限不够
#define ACK_ERROR_CHANNEL 0x04 //错误的通道号
#define ACK_ERROR_PTZ_BUSY 0x05 //云台忙,暂时无法操作

#define ACK_ERROR_FORMAT_DISK   0x11    //硬盘正在格式化
#define ACK_ERROR_FDISK_DISK    0x12    //硬盘正在分区

//=====================消息类型===========================
#define MSG_LOGIN 0x0001 //登陆
#define MSG_LOGOUT 0x0002 //注消
#define MSG_OPEN_CHANNEL 0x0003 //打开通道
#define MSG_CLOSE_CHANNEL 0x0004 //关闭通道
#define MSG_START_SEND_DATA 0x0005 //开始发送数据
#define MSG_STOP_SEND_DATA 0x0006 //停止发送数据
#define MSG_PTZ_CONTROL 0x0007 //云台控制
#define MSG_DEFAULT_SETTING 0x0008 //出厂设置
#define MSG_SESSION_ID 0x0009 //会话ID

#define MSG_SET_PARAM 0x0401 //设置参数
#define MSG_GET_PARAM 0x0402 //获取参数
#define MSG_RESET_VIDEO_PARAM 0x0403 //恢复视频参数设置

#define MSG_GET_RECORD_LIST 0x0801 //查询录像
#define MSG_SET_TIME 0x0802 //设置时间
#define MSG_GET_TIME 0x0803 //获取时间
#define MSG_GET_VERSION_INFO 0x0804 //版本信息
#define MSG_HARDDISK_INFO 0x0805 //硬盘信息
#define MSG_SYSTEM_STATUS 0x0806 //系统状态
#define MSG_GET_LOG 0x0807 //查询日志
#define MSG_DELETE_LOG 0x0808 //删除日志
#define MSG_ALARM_INFO 0x0809 //告警信息
#define MSG_ALARM_CONTROL 0x080a //告警上传控制
#define MSG_UPDATE_STATUS 0x080b //升级状态
#define MSG_HEARTBEAT 0x080c //心跳包
//#define MSG_HEARTBEAT_PORT 0x080d //心跳包端口消息(未使用)
#define MSG_GET_USERINFO 0x080e //查询用户信息
#define MSG_ADD_USER 0x080f //增加用户
#define MSG_DELETE_USER 0x0810 //删除用户
#define MSG_MODIFY_USER 0x0811 //修改用户
#define MSG_GET_PLATFORM_TYPE 0x0812 //查询平台类型
//#define MSG_SET_POLL_CONFIG  0x0813 //通道轮询(未使用)
//#define MSG_TRANSPARENT_CMD 0x0814 //未使用
#define MSG_GET_AP_INFO 0x0815 //搜索无线路由器信息
//#define MSG_START_TRANSPARENT 0x0816 //开始透传(未使用)
//#define MSG_STOP_TRANSPARENT 0x0817 //停止透传(未使用)
#define MSG_SEND_TRANSPARENT 0x0818 //发送透传数据
#define MSG_REC_TRANSPARENT 0x0819 //接收透传数据

#define MSG_FORCE_KEYFRAME 0x0830 //强迫I帧
#define MSG_REMOTE_START_HAND_RECORD 0x0840 //开始手动录像
#define MSG_REMOTE_STOP_HAND_RECORD 0x0841 //停止手动录像
#define MSG_DELETE_RECORD_FILE 0x0842 //删除录像
#define MSG_REBOOT_SYSTEM 0x0843 //重启系统
#define MSG_RESET_DEFAULT_PARAM 0x0844 //恢复默认值
#define MSG_HARD_FDISK 0x0845 //硬盘分区
#define MSG_HARD_FORMAT 0x0846 //硬盘格式化
#define MSG_GET_FORMAT_STATUS 0x0847 //获得格式化进度
#define MSG_GET_FDISK_STATUS 0x0848 //获得分区进度
//#define MSG_SET_GUARD_FLAG 0x0849 //设置布防标志(未使用)
//#define MSG_SET_UNGUARD_FLAG 0x0850 //设置撤防标志(未使用)
#define MSG_BROADCAST_SEARCH 0x851 //广播搜索设备
#define MSG_BROADCAST_MODIFY 0x852 //广播修改IP 
#define MSG_RESET_FACTORY_PARAM 0x0853 //恢复出厂设置	
#define MSG_SET_VERSION_INFO 0x0854 //设置版本信息

//#define MSG_CAMERA_DEFAULT 0x0857//恢复标清CCD默认配置(未使用)
//#define MSG_ITU_DEFAULT 0x0858//恢复标清CCD ITU默认配置(未使用)

#define MSG_3G_INFO	0x0861//3G模块信息
#define MSG_SENSOR_DEFAULT 0x0875      //juice 2012.08.13
#define MSG_RESET_3G_MODULE 0x0863
#define MSG_CMOS_DEFAULT 0x0864 //MT9D131 SENSOR默认配置(未使用)
#define MSG_3GCONFIG_DEFAULT 0x0865 //恢复3G配置信息默认值
//#define MSG_GET_RFID 0x0866	//获取RF ID号(未使用)

#define MSG_HDDOME_DEFAULT 0x0867 //恢复SC110高清球默认配置

#define MSG_SONY4300_DEFAULT 0x0872 //恢复SONY4300高清球默认配置

#define MSG_BACKUP_DEFAULT_PARAM  0x0873//备份默认参数

#define MSG_DETECT_HOT_PIXEL 0x0874 //开始静态坏点检测

//#define MSG_BROADCAST 0x0f01 //广播探测消息(未使用)


//==================参数控制子类型====================
//#define PARAM_AUTO_POWEROFF 0x0001
//#define PARAM_AUTO_POWERON 0x0002
#define PARAM_USER_INFO 0x0003
#define PARAM_HAND_RECORD 0x0004
#define PARAM_NETWORK_CONFIG 0x0005
//#define PARAM_MISC_CONFIG 0x0006
#define PARAM_PROBER_ALRAM 0x0007
#define PARAM_RECORD_PARAM 0x0008
#define PARAM_TERM_CONFIG 0x0009 //PTZ
#define PARAM_TIMER_RECORD 0x000A
#define PARAM_VIDEO_LOSE 0x000B
#define PARAM_VIDEO_MOVE 0x000C /*MOTION*/
#define PARAM_VIDEO_CONFIG 0x000D
#define PARAM_VIDEO_ENCODE 0x000E
//#define PARAM_ALARM_PARAM 0x000F//?

#define PARAM_OSD_INFO 0x0011
#define PARAM_OVERLAY_INFO 0x0012

#define PARAM_PPPOE_INFO 0x0014
#define PARAM_RECORD_INFO 0x0015

#define PARAM_WIRELESS_CONFIG 0x0017//加入无线路由器
#define PARAM_EMAIL_INFO 0x0018
#define PARAM_FTP_INFO 0x0019

#define PARAM_TIMER_CAPTURE 0x001C

//#define PARAM_INSTANT_CAPTURE 0x001E
//#define PARAM_CRUISE_CONFIG 0x001F//预制位巡航

#define PARAM_NSS_CENTER 0x0020
#define PARAM_NSS_LENS 0x0021
#define PARAM_SERIAL_INFO 0x0022
#define PARAM_TRANSPARENCE_INFO 0x0023
#define PARAM_SLAVE_ENCODE 0x0024
#define PARAM_DEVICE_INFO 0x0025
#define PARAM_AUDIO_ENCODE 0x0026
#define PARAM_ONLINE_STATUS 0x0027
//#define PARAM_CAMERA_INFO 0x0028
//#define PARAM_NAS_CONFIG 0x0029
//#define PARAM_ITU_INFO 0x002a
#define PARAM_TIMER_COLOR2GRAY 0x002b
#define PARAM_NSS_TIMERREG      0x002d
#define PARAM_USB_TYPE_CONFIG 0x002F//usb外接设备

#define PARAM_WSX_PLATFORM_CONFIG 0x0031
//#define PARAM_PLS_CONFIG_INFO 0X0032
#define PARAM_SENSOR_CONFIG 0X0110                  //sensor 配置juice2012.08.13
#define PARAM_IO_CONTROL	0x0038					//IO控制 
#define PARAM_TIMER_IOCONTROL 0x0039
//#define PARAM_KEDA_PLATFORM_CONFIG 0x0040
//#define PARAM_CMOS_INFO 0x0041
#define PARAM_MODULE_CONFIG 0x0042 //3G配置信息
#define PARAM_SNAP_CONFIG 0x0043

//#define PARAM_IPASSION_INFO	0x0045 //mt9m033模组配置
//#define PARAM_IT1_INFO 0x0046 //IT1模组配置

#define PARAM_ZTE_CLINTINFO 0x0052

#define PARAM_ZTE_UDP_NAT_INFO 0x0055

//#define PARAM_RF_ALARM	0x005B	//RF报警配置
#define PARAM_VIDEO_COVER_ALARM	0x005C //视频遮挡报警配置
//#define PARAM_TIMER_INFRARED 0x005D //2102定时红外灯控制

//hxht
#define PARAM_HXHT_PLAT_PARAM 0x0062
#define PARAM_HXHT_ALARM_SCHEME 0x0063

//#define LANGTAO_PLAT_INFO 0x0068

//#define PARAM_ISHOW_PLAT_CONFIG 0x0074
#define PARAM_TIME_CHECK 0X0075
#define PARAM_ZTE_ISMA_ENABLE 0x0076

//#define PARAM_MOBILEDVR_PARAM 0x0079

#define PARAM_OSD_EX    0x0112
#define PARAM_GB_PLAT_PARAM 0x0115

//键盘参数
//#define PARAM_KEY_USER_PWD 0x0081
//#define PARAM_KEY_SERVER_INFO 0x0082
//#define PARAM_KEY_ENC_INFO 0x0083
//#define PARAM_KEY_DEC_INFO 0x0085
//#define PARAM_KEY_TOUR_INFO 0x0086
//#define PARAM_KEY_GROUP_INFO 0x0088

#define PARAM_DEV_SYSINFO 0x0090

#define PARAM_AUTO_COLOR2GRAY 0X009C //自动彩转黑参数
//#define PARAM_NETSTAR_CONFIG  0x0201
//#define PARAM_DECODE_NUM  0x0202
//#define PARAM_DECODE_STAT  0x0203
//#define PARAM_DEFAULT_ENCODER  0x0204
//#define PARAM_DECODER_OSD  0x0205
//#define TVW_CONFIG_INFO 0x206

//#define PARAM_CDMA_TIME 0x1079//定时cdma拨号
//#define PARAM_CDMA_ALARM_ENABLE	   0x1080//报警触发拨号
//#define PARAM_CDMA_NONEGO_ENABLE   0x1081//外部触发拨号
//#define PARAM_CDMA_ALARM_INFO	   0x1082//报警配置信息
//#define PARAM_CDMA_STREAM_ENABLE   0x1083//断流后自动下线

#define PARAM_HDDOME_PTZ_CONFIG		(0X2000)   //高清球云台参数
#define PARAM_HDDOME_CONFIG   		(0X2001)   //高清球摄像机参数*/

////////////////add isp adv config	///////////////
#define PARAM_ISP_CONFIG		0x0500
#define PARAM_ISP_EXPOSURE_CONFIG	0x0501
#define	PARAM_ISP_DAYNIGHT_CONFIG	0x0502
#define PARAM_ISP_BLC_CONFIG		0x0503
#define	PARAM_ISP_WB_CONFIG			0x0504
#define	PARAM_ISP_NR_CONFIG			0x0505
#define	PARAM_ISP_FORG_CONFIG		0x0506
#define	PARAM_SIP_ABC_CONFIG		0x0507
#define PARAM_ISP_MIRROR_CONFIG		0x0508
#define PARAM_ISP_ROT_CONFIG		0x0509

////////////////////////webrtc message define /////////////////////////////
#define MSG_WEBRTC_BASE									(0X11000)
#define MSG_WEBRTC_MAX									(MSG_WEBRTC_BASE +0X1000)

#define MSG_WEBRTC_LOGIN_ADDUSER						(MSG_WEBRTC_BASE + 0x0001)
#define MSG_WEBRTC_LOGIN_DELUSER						(MSG_WEBRTC_BASE + 0x0002)

#define MSG_WEBRTC_SYSTEM_REBOOT						(MSG_WEBRTC_BASE + 0x0011)
#define MSG_WEBRTC_SYSTEM_DISK_INFO						(MSG_WEBRTC_BASE + 0x0019)
#define MSG_WEBRTC_SYSTEM_FORMAT_DISK					(MSG_WEBRTC_BASE + 0x0012)
#define MSG_WEBRTC_SYSTEM_CHANGE_WEBLANGUAGE			(MSG_WEBRTC_BASE + 0x0013)
#define MSG_WEBRTC_SYSTEM_CHANGE_PARTCHN				(MSG_WEBRTC_BASE + 0x0014)
#define MSG_WEBRTC_SYSTEM_CHANGE_AUTOREBOOT				(MSG_WEBRTC_BASE + 0x0015)
#define MSG_WEBRTC_SYSTEM_RESET_CONFIG					(MSG_WEBRTC_BASE + 0x0016)
#define MSG_WEBRTC_SYSTEM_UPDATE_FROM_NET				(MSG_WEBRTC_BASE + 0x0017)
#define MSG_WEBRTC_SYSTEM_BACKUP_CONFIG					(MSG_WEBRTC_BASE + 0x0018)
 
#define MSG_WEBRTC_REALTIME_CONFIG						(MSG_WEBRTC_BASE + 0x0021)
#define MSG_WEBRTC_REALTIME_PC_SYNC						(MSG_WEBRTC_BASE + 0x0022)

#define MSG_WEBRTC_NETWORK_WIFI_CONFIG					(MSG_WEBRTC_BASE + 0x0031)
#define MSG_WEBRTC_NETWORK_4G_CONFIG					(MSG_WEBRTC_BASE + 0x0032)

#define MSG_WEBRTC_PLATFORM_CONFIG						(MSG_WEBRTC_BASE + 0x0041)

#define MSG_WEBRTC_ALARM_RCTRL_CONFIG					(MSG_WEBRTC_BASE + 0x0051)
#define MSG_WEBRTC_ALARM_WIRELESSDA_CONFIG				(MSG_WEBRTC_BASE + 0x0052)
#define MSG_WEBRTC_ALARM_WIREDDA_CONFIG					(MSG_WEBRTC_BASE + 0x0053)
#define MSG_WEBRTC_ALARM_AUTO_CONFIG					(MSG_WEBRTC_BASE + 0x0054)
#define MSG_WEBRTC_ALARM_SNDOUT_CONFIG					(MSG_WEBRTC_BASE + 0x0055)
#define MSG_WEBRTC_ALARM_VOICE_CONFIG					(MSG_WEBRTC_BASE + 0x0056)
#define MSG_WEBRTC_ALARM_VIDEO_CONFIG					(MSG_WEBRTC_BASE + 0x0057)
#define MSG_WEBRTC_ALARM_IMAGE_CONFIG					(MSG_WEBRTC_BASE + 0x0058)
#define MSG_WEBRTC_ALARM_OTHER_CONFIG					(MSG_WEBRTC_BASE + 0x0059)

#define MSG_WEBRTC_ANALYZE_ALARMSET_CONFIG 				(MSG_WEBRTC_BASE + 0x0061)
#define MSG_WEBRTC_ANALYZE_REGION_CONFIG 				(MSG_WEBRTC_BASE + 0x0062)

#define MSG_WEBRTC_PARTITION_MODE_CONFIG 				(MSG_WEBRTC_BASE + 0x0071)
#define MSG_WEBRTC_PARTITION_GB28181_CONFIG 			(MSG_WEBRTC_BASE + 0x0072)
#define MSG_WEBRTC_PARTITION_VOIPACCOUNT_CONFIG 		(MSG_WEBRTC_BASE + 0x0073)
#define MSG_WEBRTC_PARTITION_VKEY_CONFIG 				(MSG_WEBRTC_BASE + 0x0074)

#define MSG_WEBRTC_CLOUD_CONFIG 						(MSG_WEBRTC_BASE + 0x0081)



////////////////////////above webrtc message define /////////////////////////////

//=====================云台控制类型=====================
//#define PTZ_TYPE_SETPROTOCOL 0x0001 //设置云台协议
//#define PTZ_TYPE_GETPROTOCOL 0x0002 //得到云台协议
#define PTZ_TYPE_START 0x0001 //开始云台控制
#define PTZ_TYPE_STOP 0x0002 //停止云台控制
#define PTZ_TYPE_UP_START 0x0003 //上(开始)
#define PTZ_TYPE_UP_STOP 0x0004 //上(停止)
#define PTZ_TYPE_DOWN_START 0x0005 //下(开始)
#define PTZ_TYPE_DOWN_STOP 0x0006 //下(停止)
#define PTZ_TYPE_LEFT_START 0x0007 //左(开始)
#define PTZ_TYPE_LEFT_STOP 0x0008 //左(停止)
#define PTZ_TYPE_RIGHT_START 0x0009 //右(开始)
#define PTZ_TYPE_RIGHT_STOP 0x000a //右(停止)
#define PTZ_TYPE_PREVPOINTSET 0x000b //设置预置点
#define PTZ_TYPE_PREVPOINTCALL 0x000c //调用预置点
#define PTZ_TYPE_PREVPOINTDEL 0x000d //删除预置点
#define PTZ_TYPE_ZOOMADD_START 0x000e //变倍+(开始)
#define PTZ_TYPE_ZOOMADD_STOP 0x000f //变倍+(停止)
#define PTZ_TYPE_ZOOMSUB_START 0x0010 //变倍-(开始)
#define PTZ_TYPE_ZOOMSUB_STOP 0x0011 //变倍-(停止)
#define PTZ_TYPE_FOCUSADD_START 0x0012 //聚焦+(开始)
#define PTZ_TYPE_FOCUSADD_STOP 0x0013 //聚焦+(停止)
#define PTZ_TYPE_FOCUSSUB_START 0x0014 //聚焦-(开始)
#define PTZ_TYPE_FOCUSSUB_STOP 0x0015 //聚焦-(停止)
#define PTZ_TYPE_IRISADD_START 0x0016 //光圈+(开始)
#define PTZ_TYPE_IRISADD_STOP 0x0017 //光圈+(停止)
#define PTZ_TYPE_IRISSUB_START 0x0018 //光圈-(开始)
#define PTZ_TYPE_IRISSUB_STOP 0x0019 //光圈-(停止)
#define PTZ_TYPE_AUTOSCAN_START 0x001a //自动线扫-(开始)
#define PTZ_TYPE_AUTOSCAN_STOP 0x001b //自动线扫-(停止)
#define PTZ_TYPE_RANDOMSCAN_START 0x001c //随机线扫-(开始)
#define PTZ_TYPE_RANDOMSCAN_STOP 0x001d //随机线扫-(停止)

#define PTZ_TYPE_CRUISE_START           0x002b  //预制位巡航-(开始)
#define PTZ_TYPE_CRUISE_STOP            0x002c  //预制位巡航-(停止)
#define PTZ_TYPE_REPOSITION             0x002d  //预制位归位

#define MSG_DATA_LEN (100*1024)
#define MAX_NET_PACK_SIZE 1400

typedef struct __msg_head_t
{
	unsigned short msg_type; //消息类型
	unsigned short msg_subtype; //消息子类型
	unsigned int msg_size; //消息长度	
	unsigned char ack_flag; //确认标志
	unsigned char dev_type; //0: normal 1:nvr 2:...
	unsigned char chn_no;  //0锛?54:ipc ch  0xff:local
	unsigned char  msg_fmt;	// 0: binary 1:json
//	unsigned char reserved[3];
}msg_head_t;

typedef struct __net_msg_t
{
	msg_head_t msg_head; //消息头
	char msg_data[MSG_DATA_LEN]; //消息数据
}net_msg_t;

typedef struct __pack_head_t
{
	unsigned long frame_no; //视频帧序号DWORD
	unsigned long frame_size; //视频帧长度
	unsigned long pack_size; //小数据包长度	
	unsigned char pack_count; //小数据包数量
	unsigned char pack_no; //视频帧中拆分的小数据包序号
	unsigned char frame_type;
	unsigned char reserved[1];
}pack_head_t;

typedef struct __net_pack_t
{
	pack_head_t pack_head;
	unsigned char pack_data[MAX_NET_PACK_SIZE];
}net_pack_t;

typedef struct __net_pack_t_bak
{
	pack_head_t pack_head;
	unsigned char *pack_data;
}net_pack_t_bak;

typedef struct _msg_time_t
{
	int year; 
	int month;
	int day;
	int hour;
	int minute;
	int second;
}msg_time_t;

#define MSG_USER_NAME_LEN 24
#define MSG_PASSWD_LEN 24
typedef struct __msg_login_t
{
	char user_name[MSG_USER_NAME_LEN];
	char user_pwd[MSG_PASSWD_LEN];
	short unused;
	short local_right; 
	int remote_right;
	int server_type;
	msg_time_t local_time;
}msg_login_t;

typedef struct __msg_open_channel_t
{
	int channel_no;
	int protocol_type;
	/* int port_no;*/
	struct sockaddr_in client_sockaddr;
	unsigned char channel_type;
	unsigned char smoothFlag;
    unsigned char unused[2];   
}msg_open_channel_t;

typedef struct __poll_attr_t
{
    int ch;
    int enable;
    int internal_time;
    int poll_channel;
}poll_attr_t;

typedef struct __msg_close_channel_t
{
	int channel_no;
	/* int protocol_type;*/
	/*int port_no;*/
	unsigned char channel_type;
	unsigned char smoothFlag;   
	unsigned short reserved;
}msg_close_channel_t;

typedef struct __msg_mcast_t
{
	int channel_no;
	unsigned char channel_type;   
    poll_attr_t *p_ch_pollattr;
}msg_mcast_t;

typedef struct _msg_ptz_control_t
{
	int channel; //通道号
	int ptz_value; //云台参数
	char user_name[12];					
	char user_pwd[12];	
}msg_ptz_control_t;

#define MSG_RECORD_FILENAME_LEN 48 /**/
#define MSG_VERSION_LEN 24 /**/
#define MSG_DISK_NAME_LEN 12 /**/
#define MSG_MAX_PART_NUM 4	/**/
#define MSG_MAX_HARDDISK_NUM 8	/**/
#define MSG_MAX_LOG_DESC_LEN 48 /**/
#define MSG_ADDR_LEN 16 /**/

typedef struct _msg_search_record_t
{
	int channel; //通道号
	int record_type; //录像类型
	int flag; //分区标志,0:录像分区,1:备份分区
	msg_time_t s_tm; //开始时间
	msg_time_t e_tm; //结束时间
}msg_search_record_t;

typedef struct _msg_record_info_t
{
	char filename[MSG_RECORD_FILENAME_LEN];
	unsigned int filesize; //文件大小
//	unsigned int    filetype;       //录像文件类型
	// msg_time_t s_tm; //文件开始时间
	// msg_time_t e_tm; //文件结束时间
}msg_record_info_t;


// by maohw
typedef struct
{
	msg_time_t	start_time;	/*段开始时间*/
	msg_time_t	end_time;	/*段结束时间*/
	
	unsigned int data_start_offset;   /*数据起始位置*/
	unsigned int data_end_offset;     /*数据结束位置*/

	unsigned int index_start_offset;  /*帧索引起始位置*/
	unsigned int index_end_offset;    /*帧索引结束位置*/
	unsigned int record_type;         /*段录像类型*/

	char	file_name[MSG_RECORD_FILENAME_LEN];/*文件名*/
}msg_fragment_t;

typedef struct __msg_record_list_t
{
	msg_record_info_t msg_record_info;
	struct __msg_record_list_t *next;
}msg_record_list_t;

typedef struct __msg_fragment_list_t
{
	struct list_head list;	
	msg_fragment_t  msg_fragment;
}msg_fragment_list_t;

#pragma pack(4)
typedef struct _msg_part_info_t
{
	unsigned char part_no; //分区号
	unsigned char part_type; //分区类型,0:录像分区,1:备份分区
	unsigned char cur_status; //当前状态,0:未挂载,1:未用,2:正在使用
	unsigned char reserved; //保留位
	unsigned char reserved1[4]; 
	long long total_size; //分区总容量
	long long free_size; //分区剩余容量
}msg_part_info_t;

typedef struct _msg_hardisk_info_t
{
	unsigned char disk_no; //硬盘号
	unsigned char part_num; //分区数
	unsigned char filesystem; //文件系统,0:未知,1:EXT4,2:FAT32
	unsigned char part_status; //分区状态,0:未分区,1:已分区
	char diskname[MSG_DISK_NAME_LEN]; //硬盘名
	long long harddisk_size; //硬盘总容量
	msg_part_info_t partinfo[MSG_MAX_PART_NUM];
}msg_harddisk_info_t;

typedef struct _msg_harddisk_data_t
{
	int disk_num; //硬盘数
	int reserved;
	msg_harddisk_info_t hdinfo[MSG_MAX_HARDDISK_NUM];
}msg_harddisk_data_t;
#pragma pack()

#pragma pack(4)
typedef struct _msg_system_status_t
{
	int     cpu_percent;            //CPU利用率
	int     run_hour;               //运行小时数
	int     run_minute;             //运行分钟数
	int     mem_percent;
	int     flash_size;
	msg_harddisk_data_t disk_info;  //disk info
	int 	unused[64];
}msg_system_status_t;
#pragma pack()

typedef struct _msg_search_log_t
{
	int log_type; //日志类型
	msg_time_t s_tm;
	msg_time_t e_tm;
}msg_search_log_t;

typedef struct _msg_delete_log_t
{
	int log_type; //日志类型
	msg_time_t s_tm;
	msg_time_t e_tm;
}msg_delete_log_t;

typedef struct _msg_log_info_t
{
	int log_type; //日志类型
	msg_time_t tm; //日志时间
	char log_desc[MSG_MAX_LOG_DESC_LEN];
}msg_log_info_t;

typedef struct __msg_log_list_t
{
	msg_log_info_t msg_log_info;
	struct __msg_log_list_t *next;
}msg_log_list_t;

typedef struct __msg_alarm_ack_t
{
	msg_time_t tm;
	unsigned int alarm_id;
}msg_alarm_ack_t;

typedef struct _msg_alarm_control_t
{
	int status; //释放定制告警信息,0:不定制,1:定制
}msg_alarm_control_t;

typedef struct _msg_update_status_t
{
	int percent;
}msg_update_status_t;

typedef struct _msg_user_info_t
{
	char user_name[MSG_USER_NAME_LEN];
	char user_pwd[MSG_PASSWD_LEN];
	int local_right;
	int remote_right;
}msg_user_info_t;

typedef struct __msg_user_list_t
{
	msg_user_info_t msg_user_info;
	struct __msg_user_list_t *next;
}msg_user_list_t;

/**/
#define MSG_HOSTNAME_LEN 24
#define MSG_MAC_ADDR_SIZE 24
#define MSG_IP_SIZE 16
#define MSG_VERSION_LEN 24

typedef struct _msg_broadcast_t
{
	int server_type; //设备类型
	int port_no; //监听端口
	int net_type; //网络类型
	char host_name[MSG_HOSTNAME_LEN]; //设备名
	char mac_addr[MSG_MAC_ADDR_SIZE]; //MAC地址
	char ip_addr[MSG_IP_SIZE]; //IP地址
	char net_mask[MSG_IP_SIZE]; //网络掩码
	char gw_addr[MSG_IP_SIZE]; //网关地址
	char version[MSG_VERSION_LEN];
	unsigned int port_offset; //端口偏移
	char first_dns_addr[MSG_IP_SIZE]; //首选DNS地址
	char second_dns_addr[MSG_IP_SIZE]; //备用DNS地址
	unsigned short dns_manu_flag; //dns 手动标志: 1: enable, 0: disable
	unsigned short web_port; //web 端口
	char dhcp_flag; //dhcp 使能标志: 1:enable, 0: disable
	char gw_devtype; //0:使用此网卡默认网关 1：没使用此网卡的默认网关
	char unused[2];
	char device_type[MSG_VERSION_LEN];                //产品型号
	sys_config_t	sys_config;	
}msg_broadcast_t;

typedef struct _msg_broadcast_modify_info_t
{
	int src_server_type; 
	int src_port_no;
	int src_net_type;
	char src_host_name[MSG_HOSTNAME_LEN];
	char src_mac_addr[MSG_MAC_ADDR_SIZE];
	char src_ip_addr[MSG_IP_SIZE];
	char src_mask_addr[MSG_IP_SIZE]; 
	char src_gw_addr[MSG_IP_SIZE];
	char src_version_no[MSG_VERSION_LEN];
	int src_port_offset;

	int dst_server_type; 
	int dst_port_no;
	int dst_net_type;
	char dst_host_name[MSG_HOSTNAME_LEN];
	char dst_mac_addr[MSG_MAC_ADDR_SIZE];
	char dst_ip_addr[MSG_IP_SIZE];
	char dst_mask_addr[MSG_IP_SIZE]; 
	char dst_gw_addr[MSG_IP_SIZE];
	char dst_version_no[MSG_VERSION_LEN];
	int dst_port_offset;

	char src_first_dns_addr[MSG_IP_SIZE]; //首选DNS地址
	char src_second_dns_addr[MSG_IP_SIZE]; //备用DNS地址
	unsigned short src_dns_manu_flag; //dns 手动标志: 1: enable, 0: disable
	unsigned short src_web_port; //web 端口

	char dst_first_dns_addr[MSG_IP_SIZE]; //首选DNS地址
	char dst_second_dns_addr[MSG_IP_SIZE]; //备用DNS地址
	unsigned short dst_dns_manu_flag; //dns 手动标志: 1: enable, 0: disable
	unsigned short dst_web_port; //web 端口
	char dst_dhcp_flag; //dhcp 使能标志: 1:enable, 0: disable
	char unused[3];
}msg_broadcast_modify_info_t;

typedef struct _msg_broadcast_reset_t
{
	int server_type; //设备类型
	int port_no; //监听端口
	int net_type; //网络类型
	char host_name[MSG_HOSTNAME_LEN]; //设备名
	char mac_addr[MSG_MAC_ADDR_SIZE]; //MAC地址
	char ip_addr[MSG_IP_SIZE]; //IP地址
	char net_mask[MSG_IP_SIZE]; //网络掩码
	char gw_addr[MSG_IP_SIZE]; //网关地址
	char version[MSG_VERSION_LEN];
	unsigned int port_offset; //端口偏移
}msg_broadcast_reset_t;

/*////////////////////////////////////////////////////////*/
#define TCP_TYPE_PREVIEW 0x0000 //实时预览
#define TCP_TYPE_DOWNLOAD_RECORD 0x0001 //录像下载
#define TCP_TYPE_PLAY_RECORD 0x0002 //录像点播
#define TCP_TYPE_ASK_DATA 0x0003 //请求数据(点播使用)
#define TCP_TYPE_UPDATE_SYSTEM 0x0004 //升级
#define TCP_TYPE_UPDATE_RESULT 0x0005 //升级结果
#define TCP_TYPE_JPEG 0x0008 //抓拍
#define TCP_TYPE_JPEG_NET		0x0009  //抓拍
#define TCP_TYPE_3G_INFO 0x0011

#define SERVER_LISTEN_PORT 9660 //服务端使用
#define UDP_BASE_PORT 9880 //客户端使用
#define SEARCH_PORT 13451 //服务端使用
#define PC_SEARCH_PORT 13452 //服务端使用

typedef struct _msg_download_t
{
	char filename[MSG_RECORD_FILENAME_LEN];
}msg_download_t;

typedef struct _msg_filesize_t
{
	unsigned long filesize;
}msg_filesize_t;

typedef struct _msg_play_record_t
{
	char filename[MSG_RECORD_FILENAME_LEN];
}msg_play_record_t;

typedef struct _msg_delete_record_t
{
	char filename[MSG_RECORD_FILENAME_LEN];
}msg_delete_record_t;

typedef struct _msg_ask_data_t
{
	int datalen; //请求数据长度或祯个数
}msg_ask_data_t;

/*//////////////////////////////////////////2007-03-21*/
typedef struct __msg_send_data_t
{
	int channel;
	int data_type;//音视频 0 ,视频1,音频2
	unsigned char channel_type;
	unsigned char smoothFlag;
	unsigned char unusd[2];
}msg_send_data_t;

typedef struct __msg_update_info_t
{
	unsigned long filesize;
}msg_update_info_t;

#define MSG_GET_COM_INFO 0x08000018
#define MSG_SET_COM_INFO 0x08000019

typedef struct __msg_com_info_t
{
	unsigned int com_index;
	unsigned int baudrate;
	unsigned int data_bit;
	unsigned int stop_bit;
	unsigned int parity;
}msg_com_info_t;

#define OSD_LOGO_LEN 64

typedef struct __msg_osd_info_t
{
	unsigned int x_pos;
	unsigned int y_pos;
	char logo[OSD_LOGO_LEN];
}msg_osd_info_t;

#define MSG_OSD_SET 0x08000012 //OSD设置
#define MSG_OSD_QUETY 0x08000013 //OSD查询
#define MSG_OSD_ENABLE 0x08000014 //OSD显示状态
#define MSG_OSD_ENABLE_QUERY 0x08000015 //OSD显示状态查询

typedef struct __msg_osd_enable_t
{
	unsigned int logo_enable;
	unsigned int time_enable;
}msg_osd_enable_t;

#define MSG_COM_TRANSMIT 0x08000017
#define COM_DATA_LEN 512
typedef struct _msg_com_transmit_t
{
	unsigned int index;
	unsigned int len;
	char data[COM_DATA_LEN];
}msg_com_transmit_t;

#define MSG_GET_USERLOGIN_STATE 0x08000016
typedef struct __msg_user_login_state_query_t
{
	unsigned int channel_no; //0xffffffff 所有通道
}msg_user_login_state_query_t;

typedef struct __msg_user_login_state_t
{
	unsigned int channel_no;
	char user_name[MSG_USER_NAME_LEN];
	char user_ip[MSG_IP_SIZE];
	unsigned protocol_type;
	msg_time_t tm;
	unsigned int seconds;
	unsigned int net_state;
}msg_user_login_state_t;

typedef struct __msg_user_login_list_t
{
	msg_user_login_state_t msg_user_login_state;
	struct __msg_user_login_list_t *next; 
}msg_user_login_list_t;


typedef struct __msg_heartbeat_port_t
{
	int port;
}msg_heartbeat_port_t;

typedef struct __msg_preview_t
{
	int channel;
	unsigned char channel_type;//0:主码流   1:从码流
	unsigned char realTime;   
	unsigned short reserved;
}msg_preview_t;

typedef struct __msg_hand_record_t
{
	int channel;
	unsigned char record_hour_len;
	unsigned char record_minute_len;
	unsigned char record_status;
	unsigned char reserve;

}msg_hand_record_t;

typedef struct __msg_jpegsnap_t
{
	int channel;
	unsigned int picture_len;
}msg_jpegsnap_t;

typedef struct __msg_jpegsnap_stream_t
{
	unsigned char channel;
	unsigned char resolution;//0:QCIF ...
	unsigned char qValue;//Q value
	unsigned char times;//
	unsigned int picture_len;
	unsigned char format;//0:PAL  1:N
	unsigned char unused[3];
}msg_jpegsnap_stream_t;

typedef struct __msg_forceIframe_t
{
	int channel;
}msg_forceIframe_t;

typedef struct __msg_session_id_t
{
	int session_id;
}msg_session_id_t;

typedef struct __msg_play_position_t
{
	int flag;
	unsigned int frame_position;
}msg_play_position_t;

typedef struct __msg_play_info_t
{
	unsigned int frame_sum;
	unsigned int frame_firstno;
	unsigned int total_time;
}msg_play_info_t;

typedef struct __msg_hard_fdisk_t
{
	unsigned int disk_id;
	unsigned int part_num; 

}msg_hard_fdisk_t;

typedef struct __msg_hard_format_t
{
	unsigned int disk_id;
	unsigned int part_id;
	unsigned int part_type; // 0 录像分区, 1 备份分区
	// unsigned int format_flag // 0 不允许格式, 1 允许格式
}msg_hard_format_t;

typedef struct __msg_format_status_t
{
	unsigned int disk_id;
	unsigned int part_id;
	int format_status;
}msg_format_status_t;

typedef struct __msg_fdisk_status_t
{
	unsigned int disk_id;
	int fdisk_status;
}msg_fdisk_status_t;


#define MAX_TRANSPARENT_CMD_NUM 1024

typedef struct __msg_transparent_data_t
{
	int cmd_size;
	char cmd_buf[MAX_TRANSPARENT_CMD_NUM];
}msg_transparent_data_t;

#endif /*__NETLIB_H__*/

