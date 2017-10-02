#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <nbavr.hpp>

template <class Clock>
struct Display : nbavr::Task<Clock> {
    // Positive. Switches between High and Low.
    using PinRow0 = nbavr::hw::PinB2;
    using PinRow1 = nbavr::hw::PinB4;
    using PinRow2 = nbavr::hw::PinD5;
    using PinRow3 = nbavr::hw::PinB3;
    using PinRow4 = nbavr::hw::PinB1;
    using PinRow5 = nbavr::hw::PinD6;
    using PinRow6 = nbavr::hw::PinB0;
    using PinRow7 = nbavr::hw::PinD7;

    // Negative. Switches between Output and Input.
    using PinCol0 = nbavr::hw::PinC2;
    using PinCol1 = nbavr::hw::PinC4;
    using PinCol2 = nbavr::hw::PinC3;
    using PinCol3 = nbavr::hw::PinD4;
    using PinCol4 = nbavr::hw::PinC5;
    using PinCol5 = nbavr::hw::PinC1;
    using PinCol6 = nbavr::hw::PinD3;
    using PinCol7 = nbavr::hw::PinC0;

    uint8_t (&m)[8];
    int8_t mCurrentCol = 7;

    Display(uint8_t (&m)[8]) : m(m) {
        block {
            for(int8_t i = 0; i < 8; i++) {
                directionRow(i, nbavr::hw::Direction::Output);
                directionCol(i, nbavr::hw::Direction::Input);
                outputRow(i, nbavr::hw::Value::Low);
                outputCol(i, nbavr::hw::Value::Low);
            }
        }
    }

    void loop() override {
        // Turn off previous column.
        block {
            directionCol(mCurrentCol, nbavr::hw::Direction::Input);
        }

        // Go to next column.
        mCurrentCol = (mCurrentCol + 1) % 8;

        // Set next row.
        block {
            for(int8_t i = 0; i < 8; i++) {
                outputRow(i, (m[i] & nbavr::bv(7 - mCurrentCol)) ? nbavr::hw::Value::High : nbavr::hw::Value::Low);
            }
        }

        // Turn on next column.
        block {
            directionCol(mCurrentCol, nbavr::hw::Direction::Output);
        }

        this->sleep(Clock::millisToTicks(1));
    }

private:

    force_inline void directionRow(int8_t r, nbavr::hw::Direction d) {
        switch(r) {
        case 0:
            PinRow0::direction(d);
            break;
        case 1:
            PinRow1::direction(d);
            break;
        case 2:
            PinRow2::direction(d);
            break;
        case 3:
            PinRow3::direction(d);
            break;
        case 4:
            PinRow4::direction(d);
            break;
        case 5:
            PinRow5::direction(d);
            break;
        case 6:
            PinRow6::direction(d);
            break;
        case 7:
            PinRow7::direction(d);
            break;
        }
    }

    force_inline void directionCol(int8_t c, nbavr::hw::Direction d) {
        switch(c) {
        case 0:
            PinCol0::direction(d);
            break;
        case 1:
            PinCol1::direction(d);
            break;
        case 2:
            PinCol2::direction(d);
            break;
        case 3:
            PinCol3::direction(d);
            break;
        case 4:
            PinCol4::direction(d);
            break;
        case 5:
            PinCol5::direction(d);
            break;
        case 6:
            PinCol6::direction(d);
            break;
        case 7:
            PinCol7::direction(d);
            break;
        }
    }

    force_inline void outputRow(int8_t r, nbavr::hw::Value o) {
        switch(r) {
        case 0:
            PinRow0::output(o);
            break;
        case 1:
            PinRow1::output(o);
            break;
        case 2:
            PinRow2::output(o);
            break;
        case 3:
            PinRow3::output(o);
            break;
        case 4:
            PinRow4::output(o);
            break;
        case 5:
            PinRow5::output(o);
            break;
        case 6:
            PinRow6::output(o);
            break;
        case 7:
            PinRow7::output(o);
            break;
        }
    }

    force_inline void outputCol(int8_t c, nbavr::hw::Value o) {
        switch(c) {
        case 0:
            PinCol0::output(o);
            break;
        case 1:
            PinCol1::output(o);
            break;
        case 2:
            PinCol2::output(o);
            break;
        case 3:
            PinCol3::output(o);
            break;
        case 4:
            PinCol4::output(o);
            break;
        case 5:
            PinCol5::output(o);
            break;
        case 6:
            PinCol6::output(o);
            break;
        case 7:
            PinCol7::output(o);
            break;
        }
    }
};

#endif
