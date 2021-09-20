#pragma once

#include <string>
#include <vector>

namespace cutilspp
{

typedef std::vector<std::byte> bytes;

std::string gen_salt(size_t s_salt = 16);
std::vector<std::string> gen_salt_vec(int salt_count, size_t salt_size = 16);
bytes PBKDF2(std::string to_encrypt, std::string salt, int iterations = 2048, size_t s_out = 32);

} // namespace cutilspp