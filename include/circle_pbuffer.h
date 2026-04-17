#ifndef CIRCLE_PBUFFEER__H__
#define CIRCLE_PBUFFEER__H__ 

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
//针对单生产者，多消费者的设计; 针对数据以包-packet的形式传输
// c_num, --- 消费者数量， c_id --- 消费者id.
void* circle_pbuffer_init(int size, int c_num) ;
void circle_pbuffer_deinit(void * hd_) ;

/* 每次写一个包 */
int circle_pbuffer_write_data(void *hd_, unsigned char *buff, int len);

/* 添加接口，一个包的数据分几次写； 这种做法可以在某些情况下，节省数据 copy ；但需要知道整个包的长度。 */
int circle_pbuffer_write_head(void *hd_, unsigned char *buff, int len, int whole_len);
int circle_pbuffer_write_middle_data(void *hd_, unsigned char * buff, int len, int offset);
int circle_pbuffer_write_last_data(void *hd_, unsigned char * buff, int len, int offset);


/*每次读一个包*/
int circle_pbuffer_read_data(void *hd_, int c_id, unsigned char *buff);

//使能对应读 id;
//注意: 如何要防止 丢失 “第一“ 个数据包，这个函数要放在circle_pbuffer_write_** 之前调用。
int circle_pbuffer_start_read(void *hd_,  int c_id);
bool circle_pbuffer_is_start(void *hd_,  int c_id);

/* 得到没有使用 的 id*/
bool circle_pbuffer_get_cid(void *hd_,  int * c_id);

/* 得到可以读取的包数 */
int circle_pbuffer_get_pkt_num(void *hd_, int c_id);
void circle_pbuffer_clear(void *hd_, int c_id);

//取消对应读 id;
int circle_pbuffer_stop_read(void *hd_,  int c_id);



int circle_pbuffer_get_write_room(void *hd_);
int circle_pbuffer_get_read_room(void *hd_, int c_id);

// 下面两个函数，相当于将 circle_pbuffer_read_data 的功能拆分开。

//只读取一个包的数据，不移动读指针
int circle_pbuffer_pick_data(void *hd_, int c_id, unsigned char *buff);

//只更新读指针, 且只更新一个包的位置，配合circle_pbuffer_pick_data的使用
int circle_pbuffer_update_read_pos(void *hd_, int c_id);

#ifdef __cplusplus
};
#endif

#endif
