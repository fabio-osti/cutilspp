#pragma once

#include <string>
#include <stdexcept>

namespace cutilspp
{

struct response {
	std::string header;
	std::string body;
};

response* get(std::string const &url);
response* post(std::string const &url, std::string data);

} // namespace cutilspp