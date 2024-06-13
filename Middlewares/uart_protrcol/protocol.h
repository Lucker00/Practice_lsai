#pragma once

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>



#define PROTOCOL_FRAME_MAXLEN (1024)
#define PROTOCOL_RING_BUFFER_SIZE_DEFAULT (PROTOCOL_FRAME_MAXLEN * 2)
#define PROTOCOL_RING_BUFFER_SIZE PROTOCOL_RING_BUFFER_SIZE_DEFAULT


typedef struct 
{
    uint32_t valid_len;
    union
    {
        uint8_t data[PROTOCOL_FRAME_MAXLEN];
        struct{
            struct 
            {   
                uint16_t tag;
                uint16_t len;
                uint8_t frame_id;
                uint8_t head_check;
            }header;
            struct{
                uint8_t type;
                uint8_t address;
                uint8_t cmd;
                uint8_t cmd_index;
                uint8_t data[64];
            }body;
        }frame;
    };
    
}pcl_frame_t;

#pragma pack(1)

typedef int (*cmd_unpack_handler_t)(pcl_frame_t *frame);
typedef int (*send_handler_t)(uint8_t *data, uint32_t len);


int pcl_init(cmd_unpack_handler_t handler,send_handler_t send_handler);
int pcl_reset(void);
int pcl_data_input(uint8_t *data,uint32_t len,bool isSyncUnpack);
