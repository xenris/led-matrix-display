#ifndef HELLO_HPP
#define HELLO_HPP

#include <nbavr.hpp>

template <class Nbavr>
struct Hello : Task<Nbavr> {
    Stream<char>& stdout;
    uint16_t count = 0;

    Hello(Stream<char>& stdout) : stdout(stdout) {
    }

    void loop() override {
        stdout << "hello! (" << count << ')' << endl;

        count++;

        this->sleep(Nbavr::millisToTicks(1000));
    }
};

#endif
