/*#include "ton.hpp"

bool TON::operator() () {
    update();
    return Q;
}

bool TON::operator()(std::chrono::milliseconds pt_in, bool in_in) {
    pt = pt_in;
    in = in_in;

    update();
    return Q;
}

void TON::update() {
    // Positive edge
    if (in && !M){
        start = std::chrono::system_clock::now();
    }

    if (!in){
        //et = 0;
    }
    else{
        et = std::chrono::system_clock::now() - start;
    }

    Q = et >= pt;
    M = in;
}
*/