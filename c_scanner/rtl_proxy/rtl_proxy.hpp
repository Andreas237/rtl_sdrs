#ifndef RTL_PROXY_HPP
#define RTL_PROXY_HPP

class RtlProxy {
    private:
        bool read_config_file(char*);
        float* available_bandwidths;
        float* available_sample_rates;
        float frequency_range_min;
        float frequency_range_max;
    public:
        RtlProxy();
        RtlProxy(char[]);
};

#endif