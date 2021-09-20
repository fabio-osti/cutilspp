#pragma once

#include <string>
#include <vector>
#include <cstddef>

namespace cutilspp
{

typedef std::vector<std::byte> bytes;
std::string encode(bytes &to_encode);
bytes decode(std::string &to_decode);

} // namespace cutilspp