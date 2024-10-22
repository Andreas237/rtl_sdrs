#include "signal_processor/test_processor.hpp"
#include "rtl_proxy/test_rtl_proxy.hpp"
#include "rtl_proxy/rtl_proxy.hpp"

#include <iostream>


#include <armadillo>
#include <spdlog/spdlog.h>


using namespace std;
using namespace arma;

int main(void){

    spdlog::set_level(spdlog::level::debug); // Set global log level to debug

    mat A(4, 5, fill::randu);
    mat B(4, 5, fill::randu);
    
    cout << A*B.t() << endl;

    Test_Processor tp;
    tp.test_processor();

    Test_Rtl_Proxy rtls;
    rtls.test_rtl_proxy();

    RtlProxy rtlp;

    spdlog::debug("Program finished");
    return 0;
}