#ifndef RAIN_HPP
#define RAIN_HPP

#include <nbavr.hpp>
#include <stdlib.h>

struct Drop {
    enum class State : int8_t {
        Blank,
        Top,
        Fall,
        Splash,
    };

    State state = State::Blank;
    uint32_t startTime = 0;
    float pos = 0;
    const float acc = 9.8 * 2;
};

template <class Nbavr>
struct Rain : Task<Nbavr> {
    uint8_t (&m)[8];
    Drop mDrops[8] = {};

    Rain(uint8_t (&m)[8]) : m(m) {
    }

    void loop() override {
        for(int8_t i = 0; i < 8; i++) {
            if((rand() % 100) < 1) {
                if(mDrops[i].state == Drop::State::Blank) {
                    mDrops[i].state = Drop::State::Top;
                } else if(mDrops[i].state == Drop::State::Top) {
                    mDrops[i].state = Drop::State::Fall;
                    mDrops[i].startTime = Nbavr::getTicks();
                }
            }
        }

        uint32_t now = Nbavr::getTicks();

        for(int8_t i = 0; i < 8; i++) {
            Drop& drop = mDrops[i];

            if(drop.state == Drop::State::Fall) {
                float dTime = float(now - drop.startTime) / Nbavr::millisToTicks(1000);

                drop.pos = drop.acc * dTime * dTime;

                if(drop.pos > 9) {
                    drop.pos = 0;
                    drop.state = Drop::State::Blank;
                }
            }
        }

        for(int8_t i = 0; i < 8; i++) {
            m[i] = 0;
        }

        for(int8_t i = 0; i < 8; i++) {
            Drop& drop = mDrops[i];

            if(drop.state == Drop::State::Fall) {
                uint8_t row = drop.pos;

                if(row < 8) {
                    m[row] |= bv(i);
                }
            } else if(drop.state == Drop::State::Top) {
                m[0] |= bv(i);
            }
        }

        this->sleep(Nbavr::millisToTicks(40));
    }
};

#endif
