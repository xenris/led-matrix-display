#ifndef RAIN_HPP
#define RAIN_HPP

#include <nbavr.hpp>

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

template <class Clock>
struct Rain : nbavr::Task<Clock> {
    uint8_t (&m)[8];
    Drop mDrops[8] = {};
    nbavr::Random rand;

    Rain(uint8_t (&m)[8]) : m(m) {
    }

    void loop() override {
        for(int8_t i = 0; i < 8; i++) {
            if((rand.next<int16_t>() % 100) < 1) {
                if(mDrops[i].state == Drop::State::Blank) {
                    mDrops[i].state = Drop::State::Top;
                } else if(mDrops[i].state == Drop::State::Top) {
                    mDrops[i].state = Drop::State::Fall;
                    mDrops[i].startTime = Clock::getTicks();
                }
            }
        }

        uint32_t now = Clock::getTicks();

        for(int8_t i = 0; i < 8; i++) {
            Drop& drop = mDrops[i];

            if(drop.state == Drop::State::Fall) {
                float dTime = float(now - drop.startTime) / Clock::millisToTicks(1000);

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
                    m[row] |= nbavr::bv(i);
                }
            } else if(drop.state == Drop::State::Top) {
                m[0] |= nbavr::bv(i);
            }
        }

        this->sleep(Clock::millisToTicks(40));
    }
};

#endif
