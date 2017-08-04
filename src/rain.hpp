#ifndef RAIN_HPP
#define RAIN_HPP

#include <nbavr.hpp>
#include <stdlib.h>

template <class Nbavr>
struct Rain : Task<Nbavr> {
    uint8_t (&m)[8];

    Rain(uint8_t (&m)[8]) : m(m) {
    }

    void loop() override {
        m[1] = 0;

        for(int8_t i = 0; i < 8; i++) {
            if(m[0] & bv(i)) {
                if((rand() % 64) >= 62) {
                    m[1] |= bv(i);
                    m[0] &= ~bv(i);
                }
            }
        }

        for(int8_t i = 7; i >= 2; i--) {
            m[i] = m[i - 1];
        }

        for(int8_t i = 0; i < 8; i++) {
            if((rand() % 64) >= 63) {
                m[0] |= bv(i);
            }
        }

        this->sleep(Nbavr::millisToTicks(50));
    }
};

#endif
