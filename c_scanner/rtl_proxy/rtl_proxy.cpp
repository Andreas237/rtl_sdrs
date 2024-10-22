#include "rtl_proxy.hpp"

#include <fstream>
#include <iostream>

#include "rtl-sdr.h"

RtlProxy::RtlProxy() {
    read_config_file("../rtl_proxy/radio_params.txt");
    std::cout << 
    "min freq:\t" << this->frequency_range_min <<
    std::endl << 
    "max freq:\t" << this->frequency_range_max <<
    std::endl;

    std::cout << "Found " << 
    rtlsdr_get_device_count() << 
    " rtl sdrs connected to this computer" << 
    std::endl;
}


bool RtlProxy::read_config_file( char* fin) {
    std::ifstream fs(fin);

    std::cout << 
    "bad()" << fs.bad() << std::endl <<
    "good()" << fs.good() << std::endl <<
    "fail()" << fs.fail() << std::endl <<
    "eof()" << fs.eof() << std::endl <<
    std::endl;
    if (! fs.is_open()) {
        std::cerr << "Error opening " << fin << std::endl;
        return false;
    }
    
    std::string line;
    while (getline(fs, line))
        std::cout << line << std::endl;
    fs.close();
    return true;
}


