#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <nbavr.hpp>

template <class Nbavr>
struct Display : Task<Nbavr> {
    // Positive. Switches between High and Low.
    typedef PinB2 PinRow0;
    typedef PinB4 PinRow1;
    typedef PinD5 PinRow2;
    typedef PinB3 PinRow3;
    typedef PinB1 PinRow4;
    typedef PinD6 PinRow5;
    typedef PinB0 PinRow6;
    typedef PinD7 PinRow7;

    // Negative. Switches between Output and Input.
    typedef PinC2 PinCol0;
    typedef PinC4 PinCol1;
    typedef PinC3 PinCol2;
    typedef PinD4 PinCol3;
    typedef PinC5 PinCol4;
    typedef PinC1 PinCol5;
    typedef PinD3 PinCol6;
    typedef PinC0 PinCol7;

    Stream<char>& mStream;
    int8_t mCurrentCol = 7;
    uint8_t m[8] = {};

    Display(Stream<char>& stream) : mStream(stream) {
        block {
            for(int8_t i = 0; i < 8; i++) {
                directionRow(i, Direction::Output);
                directionCol(i, Direction::Input);
                outputRow(i, Value::Low);
                outputCol(i, Value::Low);
            }
        }
    }

    void loop() override {
        // Turn off previous column.
        block {
            directionCol(mCurrentCol, Direction::Input);
        }

        // Go to next column.
        mCurrentCol = (mCurrentCol + 1) % 8;

        // If at start of draw, check if the stream has a new character.
        if(mCurrentCol == 0) {
            char c;

            if(mStream.pop(&c)) {
                setChar(c);
            }
        }

        // Set next row.
        block {
            for(int8_t i = 0; i < 8; i++) {
                outputRow(i, (m[i] & bv(7 - mCurrentCol)) ? Value::High : Value::Low);
            }
        }

        // Turn on next column.
        block {
            directionCol(mCurrentCol, Direction::Output);
        }

        this->sleep(Nbavr::millisToTicks(1));
    }

private:

    void setChar(char c) {
        if((c >= 'a') && (c <= 'z')) {
            for(int8_t i = 0; i < 8; i++) {
                m[i] = alphabet[c - 'a'][i];
            }
        } else {
            for(int8_t i = 0; i < 8; i++) {
                m[i] = 0;
            }
        }
    }

    force_inline void directionRow(int8_t r, Direction d) {
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

    force_inline void directionCol(int8_t c, Direction d) {
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

    force_inline void outputRow(int8_t r, Value o) {
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

    force_inline void outputCol(int8_t c, Value o) {
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

    const uint8_t alphabet[26][8] = {
        { // A
            0b01111110,
            0b11111111,
            0b11100111,
            0b11100111,
            0b11111111,
            0b11111111,
            0b11100111,
            0b11100111,
        },
        { // B
            0b11111110,
            0b11111111,
            0b11100111,
            0b11111110,
            0b11111110,
            0b11100111,
            0b11111111,
            0b11111110,
        },
        { // C
            0b01111110,
            0b11111111,
            0b11100111,
            0b11100000,
            0b11100000,
            0b11100111,
            0b11111111,
            0b01111110,
        },
        { // D
            0b11111110,
            0b11111111,
            0b11100111,
            0b11100111,
            0b11100111,
            0b11100111,
            0b11111111,
            0b11111110,
        },
        { // E
            0b11111111,
            0b11111111,
            0b11100000,
            0b11111100,
            0b11111100,
            0b11100000,
            0b11111111,
            0b11111111,
        },
        { // F
            0b11111111,
            0b11111111,
            0b11100000,
            0b11111100,
            0b11111100,
            0b11100000,
            0b11100000,
            0b11100000,
        },
        { // G
            0b01111110,
            0b11111111,
            0b11100111,
            0b11100000,
            0b11101111,
            0b11100111,
            0b11111111,
            0b01111110,
        },
        { // H
            0b11100111,
            0b11100111,
            0b11100111,
            0b11111111,
            0b11111111,
            0b11100111,
            0b11100111,
            0b11100111,
        },
        { // I
            0b01111110,
            0b01111110,
            0b00011000,
            0b00011000,
            0b00011000,
            0b00011000,
            0b01111110,
            0b01111110,
        },
        { // J
            0b00001110,
            0b00001110,
            0b00001110,
            0b00001110,
            0b00001110,
            0b00001110,
            0b01111110,
            0b01111100,
        },
        { // K
            0b11100011,
            0b11100111,
            0b11101110,
            0b11111100,
            0b11111100,
            0b11101110,
            0b11100111,
            0b11100011,
        },
        { // L
            0b01110000,
            0b01110000,
            0b01110000,
            0b01110000,
            0b01110000,
            0b01110000,
            0b01111110,
            0b01111110,
        },
        { // M
            0b11000011,
            0b11100111,
            0b11111111,
            0b11111111,
            0b11011011,
            0b11000011,
            0b11000011,
            0b11000011,
        },
    	{ // N
        	0b11100111,
        	0b11110111,
        	0b11110111,
        	0b11111111,
        	0b11111111,
        	0b11111111,
        	0b11101111,
        	0b11100111
    	},
    	{ // O
    		0b01111110,
    		0b11111111,
    		0b11100111,
    		0b11100111,
    		0b11100111,
    		0b11100111,
    		0b11111111,
    		0b01111110
    	},
    	{ // P
    		0b11111110,
    		0b11111111,
    		0b11100111,
    		0b11111111,
    		0b11111110,
    		0b11100000,
    		0b11100000,
    		0b11100000,
    	},
    	{ // Q
    		0b01111110,
    		0b11111111,
    		0b11100111,
    		0b11100111,
    		0b11100011,
    		0b11101101,
    		0b11110110,
    		0b01111011
    	},
    	{ // R
    		0b11111110,
    		0b11111111,
    		0b11100111,
    		0b11111111,
    		0b11111110,
    		0b11100111,
    		0b11100111,
    		0b11100111
    	},
    	{ // S
    		0b01111110,
    		0b11111111,
    		0b11100000,
    		0b11111110,
    		0b01111111,
    		0b00000111,
    		0b11111111,
    		0b01111110
    	},
    	{ // T
    		0b11111111,
    		0b11111111,
    		0b00011000,
    		0b00011000,
    		0b00011000,
    		0b00011000,
    		0b00011000,
    		0b00011000,
    	},
    	{ // U
    		0b11100111,
    		0b11100111,
    		0b11100111,
    		0b11100111,
    		0b11100111,
    		0b11100111,
    		0b11111111,
    		0b01111110
    	},
    	{ // V
    		0b11100111,
    		0b11100111,
    		0b11100111,
    		0b11100111,
    		0b11100111,
    		0b11100111,
    		0b01111110,
    		0b00111100
    	},
    	{ // W
    		0b11000011,
    		0b11000011,
    		0b11000011,
    		0b11000011,
    		0b11011011,
    		0b11111111,
    		0b11100111,
    		0b11000011
    	},
    	{ // X
    		0b11100111,
    		0b11100111,
    		0b01111110,
    		0b00111100,
    		0b00111100,
    		0b01111110,
    		0b11100111,
    		0b11100111

    	},
    	{ // Y
    		0b11000011,
    		0b11000011,
    		0b11100111,
    		0b01111110,
    		0b00111100,
    		0b00011000,
    		0b00011000,
    		0b00011000
    	},
    	{ // Z
    		0b11111111,
    		0b11111111,
    		0b00001111,
    		0b00011110,
    		0b00111000,
    		0b01110000,
    		0b11111111,
    		0b11111111,
    	}
    };
};

#endif
