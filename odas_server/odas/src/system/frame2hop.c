    
    #include "frame2hop.h"
    
    frame2hop_obj * frame2hop_construct_zero(const unsigned int hopSize, const unsigned int frameSize, const unsigned int nSignals) {

        frame2hop_obj * obj;
        unsigned int iSignal;

        obj = (frame2hop_obj *) malloc(sizeof(frame2hop_obj));

        obj->hopSize = hopSize;
        obj->frameSize = frameSize;
        obj->nSignals = nSignals;

        obj->array = (float **) malloc(sizeof(float *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            obj->array[iSignal] = (float *) malloc(sizeof(float) * frameSize);
            memset(obj->array[iSignal], 0x00, sizeof(float) * frameSize);
        }

        return obj;

    }

    void frame2hop_destroy(frame2hop_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            free((void *) obj->array[iSignal]);
        }

        free((void *) obj->array);

        free((void *) obj);

    }

    void frame2hop_process(frame2hop_obj * obj, const frames_obj * frames, hops_obj * hops) {

        unsigned int iSignal;
        unsigned int iSample;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            memmove(&(obj->array[iSignal][0]),
                    &(obj->array[iSignal][obj->hopSize]),
                    sizeof(float) * (obj->frameSize - obj->hopSize));

            memset(&(obj->array[iSignal][obj->frameSize - obj->hopSize]),
                   0x00,
                   sizeof(float) * (obj->hopSize));

            for (iSample = 0; iSample < obj->frameSize; iSample++) {

                obj->array[iSignal][iSample] += frames->array[iSignal][iSample];

            }

            memcpy(&(hops->array[iSignal][0]),
                   &(obj->array[iSignal][0]),
                   sizeof(float) * obj->hopSize);

        }

    }