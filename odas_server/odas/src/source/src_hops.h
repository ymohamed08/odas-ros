#ifndef __ODAS_SOURCE_HOPS
#define __ODAS_SOURCE_HOPS

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <alsa/asoundlib.h>

    #include "../general/format.h"
    #include "../general/interface.h"
    #include "../message/msg_hops.h"
    #include "../signal/hop.h"
    #include "../utils/pcm.h"

    typedef struct src_hops_obj {

        unsigned long long timeStamp;

        unsigned int hopSize;
        unsigned int nChannels;
        unsigned int fS;

        format_obj * format;
        interface_obj * interface;

        FILE * fp;
        snd_pcm_t * ch;

        char * buffer;
        unsigned int bufferSize;

        char bytes[4];

        msg_hops_obj * out;

    } src_hops_obj;

    typedef struct src_hops_cfg {

        format_obj * format;
        interface_obj * interface;

    } src_hops_cfg;

    src_hops_obj * src_hops_construct(const src_hops_cfg * src_hops_config, const msg_hops_cfg * msg_hops_config);

    void src_hops_destroy(src_hops_obj * obj);

    void src_hops_connect(src_hops_obj * obj, msg_hops_obj * out);

    void src_hops_disconnect(src_hops_obj * obj);

    void src_hops_open(src_hops_obj * obj);

    void src_hops_open_interface_file(src_hops_obj * obj);

    void src_hops_open_interface_soundcard(src_hops_obj * obj);

    void src_hops_close(src_hops_obj * obj);

    void src_hops_close_interface_file(src_hops_obj * obj);

    void src_hops_close_interface_soundcard(src_hops_obj * obj);

    int src_hops_process(src_hops_obj * obj);

    int src_hops_process_interface_file(src_hops_obj * obj);

    int src_hops_process_interface_soundcard(src_hops_obj * obj);

    void src_hops_process_format_binary_int08(src_hops_obj * obj);

    void src_hops_process_format_binary_int16(src_hops_obj * obj);

    void src_hops_process_format_binary_int24(src_hops_obj * obj);

    void src_hops_process_format_binary_int32(src_hops_obj * obj);

    src_hops_cfg * src_hops_cfg_construct(void);

    void src_hops_cfg_destroy(src_hops_cfg * src_hops_config);

#endif