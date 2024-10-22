#ifndef RTL_PROXY_HPP
#define RTL_PROXY_HPP

#define RTLOUTBUFSZ 1024
#define INTRATE 12500
#define MAXNBCHANNELS 16
#define DEFAULT_BUFFER_SIZE 16384    // Buffer size for reading samples

#define DEFAULT_FREQUENCY 131825000
#define DEFAULT_GAIN 5
#define DEFAULT_PPM 0
#define DEFAULT_SAMPLERATE 2048000




#include "rtl-sdr.h"

static rtlsdr_dev_t* dev = (rtlsdr_dev_t*)0; 





class RtlProxy {
    private:
        bool read_config_file(char*);
        float* available_bandwidths;
        float* available_sample_rates;
        float frequency_range_min;
        float frequency_range_max;
        
    public:
        ~RtlProxy();
        RtlProxy();
        RtlProxy(char[]);
        bool rtl_sdr_collector(float,float);
};

#endif