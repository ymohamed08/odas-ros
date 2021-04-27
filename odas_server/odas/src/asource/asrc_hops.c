    
    #include "asrc_hops.h"

    asrc_hops_obj * asrc_hops_construct(const src_hops_cfg * src_hops_config, const msg_hops_cfg * msg_hops_config) {

        asrc_hops_obj * obj;

        obj = (asrc_hops_obj *) malloc(sizeof(asrc_hops_obj));

        obj->src_hops = src_hops_construct(src_hops_config, msg_hops_config);
        obj->out = (amsg_hops_obj *) NULL;

        obj->thread = thread_construct(&asrc_hops_thread, (void *) obj);

        return obj;

    }

    void asrc_hops_destroy(asrc_hops_obj * obj) {

        src_hops_destroy(obj->src_hops);
        thread_destroy(obj->thread);

        free((void *) obj);

    }

    void asrc_hops_connect(asrc_hops_obj * obj, amsg_hops_obj * out) {

        obj->out = out;

    }

    void asrc_hops_disconnect(asrc_hops_obj * obj) {

        obj->out = (amsg_hops_obj *) NULL;

    }

    void * asrc_hops_thread(void * ptr) {

        asrc_hops_obj * obj;
        msg_hops_obj * msg_hops_out;
        int rtnValue;

        obj = (asrc_hops_obj *) ptr;

        // Open the source
        src_hops_open(obj->src_hops);

        while(1) {

            // Pop a message, process, and push back
            msg_hops_out = amsg_hops_empty_pop(obj->out);
            src_hops_connect(obj->src_hops, msg_hops_out);
            rtnValue = src_hops_process(obj->src_hops);
            src_hops_disconnect(obj->src_hops);
            amsg_hops_filled_push(obj->out, msg_hops_out);

            // If this is the last frame, rtnValue = -1
            if (rtnValue == -1) {
                break;
            }

            // Some other process may ask to stop the thread
            if (thread_askedToStop(obj->thread) == 1) {
                break;
            }

        }

        // Close the source
        src_hops_close(obj->src_hops);

        // Send the "0" message, that kills all connected threads
        // that will consume this message
        msg_hops_out = amsg_hops_empty_pop(obj->out);
        msg_hops_zero(msg_hops_out);
        amsg_hops_filled_push(obj->out, msg_hops_out);

    }