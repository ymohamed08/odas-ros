#ifndef __ODAS_SYSTEM_FREQ2FREQ
#define __ODAS_SYSTEM_FREQ2FREQ

    #include <stdlib.h>
    #include <math.h>

    #include "../signal/freq.h"
    #include "../signal/env.h"
    #include "../signal/pair.h"
    #include "../signal/track.h"
    
    typedef struct freq2freq_phasor_obj {

        unsigned int halfFrameSize;
        float epsilon;

    } freq2freq_phasor_obj;

    typedef struct freq2freq_weightedphasor_obj {

        unsigned int halfFrameSize;
        float epsilon;

    } freq2freq_weightedphasor_obj;

    typedef struct freq2freq_product_obj {

        unsigned int halfFrameSize;

    } freq2freq_product_obj;

    typedef struct freq2freq_lowpass_obj {

        unsigned int halfFrameSize;
        unsigned int lowPassCut;

    } freq2freq_lowpass_obj;

    typedef struct freq2freq_interpolate_obj {

        unsigned halfFrameSize;
        unsigned halfFrameSizeInterp;

    } freq2freq_interpolate_obj;

    typedef struct freq2freq_gain_obj {

        unsigned int halfFrameSize;

    } freq2freq_gain_obj;

    freq2freq_phasor_obj * freq2freq_phasor_construct_zero(const unsigned int halfFrameSize, const float epsilon);

    void freq2freq_phasor_destroy(freq2freq_phasor_obj * obj);

    void freq2freq_phasor_process(freq2freq_phasor_obj * obj, const freqs_obj * freqs, freqs_obj * phasors);

    freq2freq_weightedphasor_obj * freq2freq_weightedphasor_construct_zero(const unsigned int halfFrameSize, const float epsilon);

    void freq2freq_weightedphasor_destroy(freq2freq_weightedphasor_obj * obj);

    void freq2freq_weightedphasor_process(freq2freq_weightedphasor_obj * obj, const freqs_obj * freqs, const envs_obj * weights, freqs_obj * weightedphasors);

    freq2freq_product_obj * freq2freq_product_construct_zero(const unsigned int halfFrameSize);

    void freq2freq_product_destroy(freq2freq_product_obj * obj);

    void freq2freq_product_process(freq2freq_product_obj * obj, const freqs_obj * freqs1, const freqs_obj * freqs2, const pairs_obj * pairs, freqs_obj * freqs12);

    freq2freq_lowpass_obj * freq2freq_lowpass_construct_zero(const unsigned int halfFrameSize, const unsigned int lowPassCut);

    void  freq2freq_lowpass_destroy(freq2freq_lowpass_obj * obj);

    void freq2freq_lowpass_process(freq2freq_lowpass_obj * obj, const freqs_obj * freqsAllPass, freqs_obj * freqsLowPass);

    freq2freq_interpolate_obj * freq2freq_interpolate_construct_zero(const unsigned int halfFrameSize, const unsigned int halfFrameSizeInterp);

    void freq2freq_interpolate_destroy(freq2freq_interpolate_obj * obj);

    void freq2freq_interpolate_process(freq2freq_interpolate_obj * obj, const freqs_obj * freqs, const freqs_obj * freqsInterp);

    freq2freq_gain_obj * freq2freq_gain_construct_zero(const unsigned int halfFrameSize);

    void freq2freq_gain_destroy(freq2freq_gain_obj * obj);

    void freq2freq_gain_process(freq2freq_gain_obj * obj, const freqs_obj * freqsIn, const envs_obj * envsIn, freqs_obj * freqsOut);

#endif