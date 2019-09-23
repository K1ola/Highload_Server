#include <fstream>
#include <ctime>
#include <sstream>
#include "Response.h"

Response::Response(std::string _url): url(_url)
{
}

std::string Response::Get_Response()
{
    std::string path = root + url;
    std::string root_directory;
    if (!url_decode(path, root_directory)) {
        return Bad_Request();
    }

    this -> path = root_directory;

    if (url.find('?') != std::string::npos)
    {
        this->path = root_directory.substr(0, root_directory.find('?'));
    }

    if (url.find("etc") != std::string::npos)
    {
        return Forbidden();
    }

    if (!get_file())
    {
        return Not_Found();
    }

    if (url == "/")
    {
        url = "/index.html";
    }

    if (this->path.find('.') == std::string::npos)
    {
        this->path += "index.html";
    }


    if (!get_file())
    {
        return Forbidden();
    }

    auto file_data = send_file();

    return ok_headers(OK, get_file_length(), get_file_type()) + file_data;
}

std::string Response::Head_Response()
{
    if (!get_file())
    {
        return Not_Found();
    }
    this->path += url;
    if (this->path.find('.') == std::string::npos)
    {
        this->path += "index.html";
    }

    return ok_headers(OK, get_file_length(), get_file_type());
 }

std::string Response::Bad_Request()
{
    return not_ok_headers(BAD_REQUEST);
}

std::string Response::Forbidden()
{
    return not_ok_headers(FORBIDDEN);
}

std::string Response::Not_Found()
{
    return not_ok_headers(NOT_FOUND);
}

std::string Response::Not_Alloved()
{
    return not_ok_headers(NOT_ALLOWED);
}

std::string Response::current_time()
{
    std::time_t result = std::time(nullptr);
    std::string str_format = std::asctime(std::localtime(&result));
    auto time = str_format.substr(0, str_format.find('\n'));
    return time;
}

std::string Response::ok_headers(const std::string status, int length, const std::string type)
{
    std::string response;
    response = status +
               DATE + current_time() + "\r\n" +
               SERVER +
               CONTENT_LENGTH + std::to_string(length)+ "\r\n" +
               type +
               CONNECTION + "\r\n";
    return response;
}

std::string Response::not_ok_headers(const std::string status)
{
    std::string response;
    response = status +
               DATE + current_time() + "\r\n" +
               SERVER +
               CONNECTION + "\r\n";
    return response;
}

std::string Response::get_file_type()
{
    std::string type = url.substr(url.find_last_of('.') + 1);

    const std::string html = std::string("html");
    const std::string txt = std::string("txt");
    const std::string css = std::string("css");
    const std::string gif = std::string("gif");
    const std::string jpeg = std::string("jpeg");
    const std::string jpg = std::string("jpg");
    const std::string js = std::string("js");
    const std::string png = std::string("png");
    const std::string swf = std::string("swf");

    if (type == html) return CONTENT_TYPE_HTML;
    if (type == css) return CONTENT_TYPE_CSS;
    if (type == gif) return CONTENT_TYPE_GIF;
    if (type == jpeg) return CONTENT_TYPE_JPEG;
    if (type == jpg) return CONTENT_TYPE_JPEG;
    if (type == js) return CONTENT_TYPE_JS;
    if (type == png) return CONTENT_TYPE_PNG;
    if (type == swf) return CONTENT_TYPE_SWF;

    return CONTENT_TYPE_HTML;
}

int Response::get_file_length()
{
    //auto path = root + url;
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    int len = file.tellg();
    return len;
}

bool Response::get_file()
{
    //auto path = root + url;
    std::ifstream file(path);
    if (file.fail())
    {
        return false;
    }
    return true;
}

bool Response::url_decode(std::string& input, std::string& result)
{
    result.clear();
    result.reserve(input.size());
    for (std::size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '%') {
            if (i + 3 <= input.size()) {
                int val = 0;
                std::istringstream is(input.substr(i + 1, 2));
                if (is >> std::hex >> val) {
                    result += static_cast<char>(val);
                    i += 2;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else if (input[i] == '+') {
            result += ' ';
        }
        else {
            result += input[i];
        }
    }
    return true;
}

std::string Response::send_file()
{
    //auto path = root + url;
    std::ifstream file(path, std::ios::binary);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

