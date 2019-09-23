#ifndef HIGHLOAD_DZ1_REQUEST_H
#define HIGHLOAD_DZ1_REQUEST_H


#include <string>
#include <functional>

class Request
{
private:
    const std::string GET = "GET";
    const std::string HEAD = "HEAD";

    void is_get_or_head();
public:
    std::string method;
    std::string url;
    std::string version;
    std::string encoding;
    std::string content_length;
public:
    Request() {};

    void Parse(std::string);
    bool correct_request = false;
};


#endif //HIGHLOAD_DZ1_REQUEST_H
