#include <random>
#include <stdexcept>
#include <openssl/evp.h>
#include "PSH.h"

namespace cutilspp
{

char const salt_table[] = "!#$%&*+,-.0123456789:;<=>?@"
						  "ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^`"
						  "abcdefghijklmnopqrstuvwxyz{}~";

std::string gen_salt(size_t s_salt = 16)
{
	char salt[s_salt];
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 85);

	for (int i = 0; i < s_salt; i++)
		salt[i] = salt_table[distrib(gen)];

	return std::string(salt, s_salt);
}

std::vector<std::string> gen_salt_vec(int salt_count, size_t salt_size = 16)
{
	auto salts = std::vector<std::string>();
	for (int i = 0; i < salt_count; i++)
		salts.push_back(gen_salt(salt_size));
	return salts;
}

bytes PBKDF2(std::string to_encrypt, std::string salt, int iterations = 2048, size_t s_out = 32)
{
	unsigned char out[s_out];
	if (!PKCS5_PBKDF2_HMAC(
			to_encrypt.c_str(), to_encrypt.size(), (unsigned char *)salt.c_str(), salt.size(), 2048, EVP_sha3_256(),
			s_out, out))
		throw std::runtime_error("Error encryptographing string");
	return bytes((std::byte *)out, (std::byte *)out + s_out);
}

} // namespace PSH