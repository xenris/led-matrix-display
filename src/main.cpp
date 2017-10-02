#include "main.hpp"

INCLUDE_DEFAULT_CALLBACK();
INCLUDE_TIMERCOUNTER_OUTPUT_CALLBACK(1, A);
INCLUDE_TIMERCOUNTER_OUTPUT_CALLBACK(1, B);
INCLUDE_TIMERCOUNTER_OVERFLOW_CALLBACK(1);
INCLUDE_USART_CALLBACK(0, RX);
INCLUDE_USART_CALLBACK(0, DE);

void main() {
    const uint32_t CpuFreq = 16000000;

    using SystemTimer = nbavr::hw::TimerCounter1;
    // using SerialUsart = nbavr::hw::Usart0;
    // using cout_t = nbavr::Queue<char, 40>;
    // using cin_t = nbavr::Queue<char, 40>;

    using Clock = nbavr::Clock<SystemTimer, CpuFreq, 0>;

    // static cout_t cout;
    // static cin_t cin;

    // nbavr::Serial<SerialUsart, cout_t, cin_t>::init(CpuFreq, 115200, &cout, &cin);

    uint8_t m[8] = {};

    // static Hello<Clock, cout_t, cin_t> hello(cout, cin, m);
    static Rain<Clock> rain(m);
    static Display<Clock> display(m);

    static nbavr::Task<Clock>* tasks[] = {&rain, &display};

    static nbavr::TaskManager<Clock> tm(tasks);
}
