#pragma once

#include <vector>
#include <string>
#include <functional>

std::vector<std::string> *split(std::string source, std::string const &delimiter)
{
	auto r = new std::vector<std::string>;
	size_t pos = 0;
	std::string token;
	while ((pos = source.find(delimiter)) != std::string::npos) {
		token = source.substr(0, pos);
		r->push_back(token);
		source.erase(0, pos + delimiter.length());
	}
	return r;
}

void parse_json_array(std::string const &jsons, std::function<void(std::string)> parser)
{
	auto response = split(jsons, "{");
	response->erase(response->begin());
	for (int i = 0; i < response->size(); i++) {
		(*response)[i].pop_back();
		(*response)[i].insert((*response)[i].begin(), '{');
		parser((*response)[i]);
	}
}