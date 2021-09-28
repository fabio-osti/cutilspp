#pragma once

enum B_FLAGS : unsigned char {

	BL_0 = 1,
	BL_1 = 2,
	BL_2 = 4,
	BL_3 = 8,
	BL_4 = 16,
	BL_5 = 32,
	BL_6 = 64,
	BL_7 = 128,

};

class bool_compress
{
	unsigned char bools;

public:
	bool_compress(
		bool _0 = false,
		bool _1 = false,
		bool _2 = false,
		bool _3 = false,
		bool _4 = false,
		bool _5 = false,
		bool _6 = false,
		bool _7 = false)
		: bools(_0 + _1 * 2 + _2 * 4 + _3 * 8 + _4 * 16 + _5 * 32 + _6 * 64 + _7 * 128)
	{
	}
	bool_compress(unsigned char flags) : bools(flags) {}
	bool operator[](unsigned char i) const { return (bools >> i) & 1; }
};