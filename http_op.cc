#include "http_op.h"
#include "split.h"
#include <x86_64-linux-gnu/curl/curl.h>

std::size_t wrt_callback(const char *in, std::size_t size, std::size_t num, std::string *out)
{
	const std::size_t totalBytes(size * num);
	out->append(in, totalBytes);
	return totalBytes;
}

std::size_t rd_callback(char *dest, std::size_t size, std::size_t num, std::string *in)
{
	const std::size_t total_bytes(std::min(in->size(), size * num));
	in->copy(dest, total_bytes);
	in->erase(in->begin(), in->begin() + total_bytes);
	return total_bytes;
}

CURL *commom_opt(const char *url)
{
	CURL *curl = curl_easy_init();
	// Set remote URL.
	curl_easy_setopt(curl, CURLOPT_URL, url);
	// Set IPV4
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
	// Time out is 10 seconds.
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
	// Follow HTTP redirects if necessary.
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
	// curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
	return curl;
}

cutilspp::response *execute(CURL *curl)
{
	auto r = new cutilspp::response;
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, wrt_callback);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, &(r->header));
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wrt_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(r->body));

	auto code = curl_easy_perform(curl);
	if (code != CURLE_OK)
		throw std::runtime_error(curl_easy_strerror(code));
	curl_easy_cleanup(curl);

	return r;
}

namespace cutilspp
{

response *get(std::string const &url)
{
	auto curl = commom_opt(url.c_str());
	return execute(curl);
}

response *post(std::string const &url, std::string data)
{
	auto curl = commom_opt(url.c_str());
	curl_easy_setopt(curl, CURLOPT_POST, true);

	auto list = curl_slist_append(NULL, "Content-Type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

	curl_easy_setopt(curl, CURLOPT_READFUNCTION, rd_callback);
	curl_easy_setopt(curl, CURLOPT_READDATA, &data);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)data.size());

	return execute(curl);
}

} // namespace cutilspp
