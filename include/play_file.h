#ifndef PLAY_FILE_32487238794
#define PLAY_FILE_32487238794
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool play_file_init(void);
bool play_file_stop(void);
bool play_file_start(char *fn);
bool play_file_is_stop(void);
bool play_file_deinit(void);









#ifdef __cplusplus
};
#endif
#endif