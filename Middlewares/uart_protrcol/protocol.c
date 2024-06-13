#include "protocol.h"



pcl_frame_t  pcl_frame;
struct ring_buf pcl_ringbuf;
uint8_t * pcl_ring_buffer[PROTOCOL_RING_BUFFER_SIZE];

cmd_unpack_handler_t cmd_unpack_handler = NULL;
send_handler_t send_handler = NULL;

int pcl_init(cmd_unpack_handler_t handler,send_handler_t send_handler_t){
    pcl_frame.valid_len = 0;
    ring_buffer_init(&pcl_ringbuf, sizeof(pcl_ring_buffer),pcl_ring_buffer);
    cmd_unpack_handler = handler;
    send_handler = send_handler_t;
    return 0;

}

int pcl_reset(void){
    ring_buffer_reset(&pcl_ringbuf);
    memset(pcl_ring_buffer,0,sizeof(pcl_ring_buffer));
    pcl_frame.valid_len = 0;
    return 0;
}

int pcl_data_input(uint8_t *data,uint32_t len,bool isSyncUnpack){
    uint32_t rb_len;
    rb_len = ring_buf_put(&pcl_ringbuf, data, len);
    if (rb_len < len)
    {
        CLOGE("Protocol drop %lu bytes", len - rb_len);
    }
    //TODO
}



