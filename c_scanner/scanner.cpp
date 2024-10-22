#include <iostream>


#include <armadillo>


#include "signal_processor/test_processor.hpp"
#include "rtl_proxy/test_rtl_proxy.hpp"
#include "rtl_proxy/rtl_proxy.hpp"


using namespace std;
using namespace arma;

int main(void){
    mat A(4, 5, fill::randu);
    mat B(4, 5, fill::randu);
    
    cout << A*B.t() << endl;

    Test_Processor tp;
    tp.test_processor();

    Test_Rtl_Proxy rtls;
    rtls.test_rtl_proxy();

    RtlProxy rtlp;

    return 0;
}