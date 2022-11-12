#ifndef TIMEDIFF_H
#define TIMEDIFF_H

#include <chrono>
#include <iostream>

template<typename T>
void print_time_diff(std::ostream& out, T prior, T latter)
{
    namespace sc = std::chrono;
    auto diff = sc::duration_cast<sc::milliseconds>(latter - prior).count();
    auto const msecs = diff % 1000;
    diff /= 1000;
    auto const secs = diff % 60;
    diff /= 60;
    auto const mins = diff % 60;
    diff /= 60;
    auto const hours = diff % 24;
    diff /= 24;
    auto const days = diff;

    bool printed_earlier = false;
    if (days >= 1) {
        printed_earlier = true;
        out << days << (1 != days ? " days" : " day") << ' ';
    }
    if (printed_earlier || hours >= 1) {
        printed_earlier = true;
        out << hours << (1 != hours ? " hours" : " hour") << ' ';
    }
    if (printed_earlier || mins >= 1) {
        printed_earlier = true;
        out << mins << (1 != mins ? " minutes" : " minute") << ' ';
    }
    if (printed_earlier || secs >= 1) {
        printed_earlier = true;
        out << secs << (1 != secs ? " seconds" : " second") << ' ';
    }
    if (printed_earlier || msecs >= 1) {
        printed_earlier = true;
        out << msecs << (1 != msecs ? " milliseconds" : " millisecond");
    }
}

#endif 
