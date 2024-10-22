#include "rtl_proxy.hpp"

#include <fstream>
#include <iostream>

#include <spdlog/spdlog.h>





int nearest_gain(int target_gain)
{
	int i, err1, err2, count, close_gain;
	count = rtlsdr_get_tuner_gains(dev, NULL);
	if (count <= 0) 
		return 0;
	// gains = (int*) malloc(sizeof(int) * count);
    auto gains = new int[count];
	if(gains == NULL) 
		return 0;
	count = rtlsdr_get_tuner_gains(dev, gains);
	close_gain = gains[0];
	for (i = 0; i < count; i++) {
		err1 = abs(target_gain - close_gain);
		err2 = abs(target_gain - gains[i]);
		if (err2 < err1) {
			close_gain = gains[i];
		}
	}
	delete gains;
	return close_gain;
}



RtlProxy::~RtlProxy(){
    // Teardown any allocated memory
    delete this->available_bandwidths;
    delete this->available_sample_rates;
    rtlsdr_close(dev);
}




RtlProxy::RtlProxy() {
    read_config_file("../rtl_proxy/radio_params.txt");
    uint32_t temp_freq = DEFAULT_FREQUENCY;
    uint32_t temp_sample_rate = DEFAULT_SAMPLERATE;
    if (!rtl_sdr_collector(temp_freq, temp_sample_rate)){
        spdlog::error("Failed to open RTL-SDR in the Proxy constructor");
        exit(1);
    }
}


bool RtlProxy::read_config_file( char* fin) {
    std::ifstream fs(fin);

    if (! fs.is_open()) {
        spdlog::error("Error opening ",fin);
        spdlog::error("Is the file path correct?");
        return false;
    }
    
    std::string line;
    while (getline(fs, line))
        spdlog::debug(line);
    fs.close();
    return true;
}


bool RtlProxy::rtl_sdr_collector(float freq, float sample_rate) {
/**
 * Open the RTL-SDR device with the highest index.
 */
    spdlog::debug("open RTL-SDR");
    spdlog::debug("received: frequency [",freq,"]\tsample rate [",sample_rate,"]");
    if (rtlsdr_open(&dev, rtlsdr_get_device_count()-1) < 0) {
        spdlog::error("Failed to open RTL-SDR device");
        return false;
    }
    

    if (rtlsdr_set_sample_rate(dev, sample_rate) <0){
        spdlog::error("Failed to set sample rate for RTL-SDR device");
        return false;
    }

    if (rtlsdr_set_center_freq(dev, freq) <0){
        spdlog::error("Failed to set center frequency for RTL-SDR device");
        return false;
    }

    spdlog::debug("Actual center frequency when tuned: ",rtlsdr_get_center_freq(dev)," Hz");
    
    // 0 means automatic bandwidth selection
    if (rtlsdr_set_tuner_bandwidth(dev, 0) <0){
        spdlog::error("Failed to set sample rate for RTL-SDR device");
        return false;
    }
    
    if (rtlsdr_set_tuner_gain(dev, nearest_gain(DEFAULT_GAIN)) != 0){
        spdlog::error("Failed to set gain for RTL-SDR device");
        return false;
    }

    int ppm = DEFAULT_PPM;
    ppm = rtlsdr_get_freq_correction(dev);
    if (ppm != 0){
        if (rtlsdr_set_freq_correction(dev, ppm) != 0) {
            spdlog::error("Failed to set frequency correction for RTL-SDR device");
            return false;
        }
        spdlog::debug("Frequency corrected by ",ppm," ppm");
    }
    

    rtlsdr_reset_buffer(dev);

    rtlsdr_close(dev);
    return true;
}