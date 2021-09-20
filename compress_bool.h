#pragma once

class bool_compress
{
	unsigned char bools;

public:
	bool_compress(bool *bs)
		: bools(bs[0] + bs[1] * 2 + bs[2] * 4 + bs[3] * 8 + bs[4] * 16 + bs[5] * 32 + bs[6] * 64 + bs[7] * 128)
	{
	}
	bool operator[](unsigned char i) const { return (bools >> i) & 1; }
};