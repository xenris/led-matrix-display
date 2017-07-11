#include "main.hpp"

INCLUDE_DEFAULT_CALLBACK;
INCLUDE_TIMERCOUNTER_OUTPUT_CALLBACK(1, A);
INCLUDE_TIMERCOUNTER_OUTPUT_CALLBACK(1, B);
INCLUDE_TIMERCOUNTER_OVERFLOW_CALLBACK(1);
INCLUDE_USART_CALLBACK(0, RX);
INCLUDE_USART_CALLBACK(0, DE);

void main() {
    const uint32_t CpuFreq = 16000000;

    typedef PinB5 ledPin;
    typedef TimerCounter1 systemTimer;
    typedef Usart0 serialUsart;

    typedef Nbavr<systemTimer, CpuFreq> Nbavr;

    Nbavr::init();

    StreamBuffer<char, 40> stdout;
    StreamBuffer<char, 0> stdin;

    Serial<serialUsart> serial(stdout, stdin);
    Hello<Nbavr> hello(stdout);
    Flash<Nbavr, ledPin> flash;

    Task* tasks[] = {&serial, &hello, &flash};

    TaskManager<Nbavr> tm(tasks);
}
