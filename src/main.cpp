#include "main.hpp"

INCLUDE_DEFAULT_CALLBACK();
INCLUDE_TIMERCOUNTER_OUTPUT_CALLBACK(1, A);
INCLUDE_TIMERCOUNTER_OUTPUT_CALLBACK(1, B);
INCLUDE_TIMERCOUNTER_OVERFLOW_CALLBACK(1);
// INCLUDE_USART_CALLBACK(0, RX);
// INCLUDE_USART_CALLBACK(0, DE);

void main() {
    const uint32_t CpuFreq = 16000000;

    typedef TimerCounter1 systemTimer;
    // typedef Usart0 serialUsart;

    typedef Clock<systemTimer, CpuFreq> Clock;

    // StreamBuffer<char, 40> stdout;
    // StreamBuffer<char, 40> stdin;
    //
    // Serial<serialUsart>::init(CpuFreq, 9600, &stdout, &stdin);
    Clock::init();

    uint8_t m[8] = {};

    // Hello<Clock> hello(stdout, stdin, m);
    Rain<Clock> rain(m);
    Display<Clock> display(m);

    Task<Clock>* tasks[] = {&rain, &display};

    TaskManager<Clock> tm(tasks);
}
