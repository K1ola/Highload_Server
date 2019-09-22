#include "Request.h"

#include <sstream>

Request::Request()
{
}

void Request::Parse(std::string request_str)
{
	//std::string request_str((std::istreambuf_iterator<char>(&buffer)), std::istreambuf_iterator<char>());
	
	std::istringstream request_string(request_str);
	request_string >> method;

	is_get_or_head();

	if (!correct_request) {
		//response.not_allowed(headers_sender);
		return;
	}

	request_string >> url >> version;
	request_string.ignore(100, '\n'); // \n after HTTP/1.1
	request_string.ignore(100, '\n'); // Host: localhost:8000
	request_string.ignore(100, ':');  // Accept-Encoding:
	request_string >> encoding;
	request_string.ignore(100, '\n'); // \n after identity
	request_string.ignore(100, ':');  // Content-Length:
	request_string >> content_length;
}


void Request::is_get_or_head()
{
	correct_request = method == GET || method == HEAD;
}
