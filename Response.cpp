#include <fstream>
#include <ctime>
#include <sstream>
#include "Response.h"

Response::Response(std::string _path, std::string _url,  std::unordered_map<std::string, std::string> _map)
    : path(_path), url(_url), map(_map)
{
}
//
//Response::Response(std::string _path, std::string _url)
//        : path(_path), url(_url)
//{
//}

std::string Response::Get_Response()
{
    std::string full_path = url_decode(path + url);

    if (full_path.empty())
    {
        std::cout << "Bad_Request:" << full_path << std::endl;
        return Bad_Request();
    }

    if (url.find('?') != std::string::npos)
    {
        full_path = full_path.substr(0, full_path.find('?'));
    }

    if (url.find("etc") != std::string::npos)
    {
        std::cout << "Forbidden:" << full_path << std::endl;
        return Forbidden();
    }
    std::ifstream file;

    if (is_dir(full_path))
    {
        handle_last_character(full_path);
        full_path += "index.html";

        if (map.find(full_path) == map.end())
        {
            std::cout << "Forbidden:" << full_path << std::endl;
            return Forbidden();
        }
    }
    else
    {
        if (map.find(full_path) == map.end())
        {
            std::cout << "Not_Found:"  << full_path << std::endl;
            return Not_Found();
        }
    }

    std::string content = map[full_path];

    auto res = ok_headers(OK, content.size(), get_file_type()) + content;
    response_len = res.size();
    return res;
}

std::string Response::Head_Response()
{
    std::ifstream file;
    std::string full_path = url_decode(path + url);
    if (is_dir(full_path))
    {
        handle_last_character(full_path);
        full_path += "index.html";
        file.open(full_path);

        if (file.fail())
        {
            return Forbidden();
        }
    }
    else
    {
        file.open(full_path);

        if (file.fail())
        {
            return Not_Found();
        }
    }
//    this->path += url;
//    if (this->path.find('.') == std::string::npos)
//    {
//        this->path += "index.html";
//    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return ok_headers(OK, content.size(), get_file_type());
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
               DATE + current_time()  + "\r\n" +
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

std::string Response::url_decode(std::string input)
{
    std::string result;
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
                    return "";
                }
            }
            else {
                return "";
            }
        }
        else if (input[i] == '+') {
            result += ' ';
        }
        else {
            result += input[i];
        }
    }
    return result;
}


bool Response::is_dir(std::string path)
{
    for (int i=path.size()-1; i>=0; i--)
    {
        if (path[i] == '/') break;
        if (path[i] == '.') return false;
    }
    return true;
}

void Response::handle_last_character(std::string& str)
{
    if (str.back() == '/') return;;
    str += '/';
}