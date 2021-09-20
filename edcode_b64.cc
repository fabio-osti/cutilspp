#include "edcode_b64.h"

#define BIN(X) (std::byte)0b##X
static char const e64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
								"abcdefghijklmnopqrstuvwxyz"
								"0123456789-_";

char find_e64(char c)
{
	if (c > 64 && c < 91)
		return c - 65;
	if (c > 96 && c < 123)
		return c - 71;
	if (c > 47 && c < 58)
		return c + 4;
	if (c == '-')
		return 62;
	if (c == '_')
		return 63;
	return 61;
}

namespace cutilspp
{

std::string encode(bytes &in)
{
	size_t tes = in.size();
	int pad = 3 - (tes % 3);
	if (pad != 3)
		in.push_back((std::byte)0);
	else
		pad = 0;

	std::string out;
	for (int i = 0; i < tes; i++) {
		switch (i % 3) {
		case 0:
			out.push_back(e64_table[(int)(in[i] >> 2)]);
			out.push_back(e64_table[(int)(((in[i] & BIN(00000011)) << 4) | (in[i + 1] >> 4))]);
			break;
		case 1:
			out.push_back(e64_table[(int)(((in[i] & BIN(00001111)) << 2) | (in[i + 1] >> 6))]);
			break;
		case 2:
			out.push_back(e64_table[(int)((in[i] & BIN(00111111)))]);
			break;
		}
	}

	for (int i = 0; i < pad; i++)
		out.push_back('=');
	return out;
}

bytes decode(std::string &in)
{
#define fnd(x) find_e64(in[x])
	bytes out;
	for (int i = 0; (i < in.size() && in[i + 1] != '='); i++) {
		switch (i % 4) {
		case 0:
			out.push_back((std::byte)((fnd(i) << 2) | (fnd(i + 1) >> 4)));
			break;
		case 1:
			out.push_back((std::byte)((fnd(i) << 4) | (fnd(i + 1) >> 2)));
			break;
		case 2:
			out.push_back((std::byte)((fnd(i) << 6) | (fnd(i + 1))));
			break;
		default:
			break;
		}
	}
	return out;
}

} // namespace cutilspp