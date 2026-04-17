#ifndef MCU_BUSINESS_H_5738974
#define MCU_BUSINESS_H_5738974

#define MAX_RSP_PACKET_SIZE 908

typedef enum //数据是小端保存
{
	CMD_HEARTBEAT = 		0X511A,
	CMD_MTOS = 				0X522A,
	CMD_STOM = 				0X533A,
	CMD_IPC_ALARM = 		0X544A,
	CMD_ALARM = 			0X555A,
	CMD_MCU_PLAY_AUDIO = 	0X566A,
	CMD_MCU_STOP_AUDIO = 	0X577A,
	CMD_IPC_START_RECORD = 	0X588A,
	CMD_MCU_OSD_DISP	= 	0x599A,
	
}MCU_CMD;

//1.mcu 的心跳信息
typedef struct 
{
	uchar_t alarm_status;
	ushort_t alarm_left_time;
	uchar_t armed_status;
	uchar_t power_status;
	uchar_t work_mode;
}MCU_HEARTBEAT;

// IPC 回应心跳
typedef struct 
{
	uchar_t call_status;
	uchar_t net_status;
	uchar_t sound_status;
	uchar_t video_status;
	uchar_t time[5]; // 月，日，时，分，秒；16进制存放，比如59分，存为 0x59
}IPC_STAT;

//2.透传信息
typedef struct 
{
	uchar_t data[MAX_RSP_PACKET_SIZE];
	int len;
	
	uchar_t is_exist; // 0, 表示没有， 1，表示有待处理的数据
}MCU_TO_SERVER_DATA;

//3. 服务器下发信息 
typedef struct 
{
	uchar_t data[MAX_RSP_PACKET_SIZE];
	int len;
	
	uchar_t is_exist; // 0, 表示没有， 1，表示有待处理的数据
}SERVER_TO_MCU_DATA;

//4. IPC报警信息 
typedef struct 
{
	uchar_t type;
	uchar_t code;
	uchar_t entertype;
	uchar_t enterdef;
	uchar_t cartype;
	uchar_t cardef ;
	
	uchar_t is_exist; // 0, 表示没有， 1，表示有待处理的数据
}IPC_ALARM_DATA;

typedef struct 
{
	uchar_t type;
	uchar_t code;
	uchar_t video_upload;
	ushort_t pretime;
	ushort_t sustaindtime;
	ushort_t video_interval;
	uchar_t pict_upload;
	uchar_t pict_quality; 
	ushort_t pict_interval;
	char filename[14];
	
}MCU_RSP_ALARM;

//5. MCU请求上传视频和图片
typedef MCU_RSP_ALARM MCU_REQUEST_UPLOAD;

//6. MCU 请求播放语音
typedef struct 
{
	uchar_t times;
	ushort_t sound_id;
}MCU_REQUEST_PLAY_AUDIO;

//8, IPC 回应开始录像
typedef struct 
{
	uchar_t type;
	uchar_t code;
	uchar_t video_upload;
	uchar_t pict_upload;
	uchar_t load_status; 
}IPC_START_RECORD;

//9 OSD 显示 
typedef struct 
{
	uchar_t type; 
	uchar_t code;
	ushort_t x;
	ushort_t y;
	ushort_t font_size;
	char data[48];
	
	uchar_t is_exist; // 0, 表示没有， 1，表示有待处理的数据
}MCU_OSD_DATA;


#ifdef __cplusplus
extern "C" {
#endif

// set/get 接口，用于与外界更新信息。 

bool ysb_set_mcu_hb(MCU_HEARTBEAT *data);
bool ysb_get_mcu_hb(MCU_HEARTBEAT *data);

bool ysb_set_ipc_stat(IPC_STAT *data);
bool ysb_get_ipc_stat(IPC_STAT *data);

bool ysb_set_mtos_data(MCU_TO_SERVER_DATA *data);
bool ysb_get_mtos_data(MCU_TO_SERVER_DATA *data);

bool ysb_set_stom_data(SERVER_TO_MCU_DATA *data);
bool ysb_get_stom_data(SERVER_TO_MCU_DATA *data);

bool ysb_set_ipc_alarm_data(IPC_ALARM_DATA *data);
bool ysb_get_ipc_alarm_data(IPC_ALARM_DATA *data);

bool ysb_set_ipc_mcu_alarm(MCU_RSP_ALARM *data);
bool ysb_get_ipc_mcu_alarm(MCU_RSP_ALARM *data);

bool ysb_set_mcu_play_audio(MCU_REQUEST_PLAY_AUDIO *data);
bool ysb_get_mcu_play_audio(MCU_REQUEST_PLAY_AUDIO *data);

bool ysb_set_ipc_start_record(IPC_START_RECORD *data);
bool ysb_get_ipc_start_record(IPC_START_RECORD *data);

#ifdef __cplusplus
};
#endif
#endif