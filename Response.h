#ifndef HIGHLOAD_DZ1_RESPONSE_H
#define HIGHLOAD_DZ1_RESPONSE_H


#include <string>
#include <iostream>
#include <unordered_map>


class Response
{
public:
    //Response();
    Response(std::string, std::string, std::unordered_map<std::string, std::string>);
    std::string Get_Response();
    std::string Head_Response();

    std::string Bad_Request();
    std::string Forbidden();
    std::string Not_Found();
    std::string Not_Alloved();

public:
    const std::string OK = std::string("HTTP/1.1 200 OK\r\n");
    const std::string BAD_REQUEST = std::string("HTTP/1.1 400 Bad Request\r\n");
    const std::string FORBIDDEN = std::string("HTTP/1.1 403 Forbidden\r\n");
    const std::string NOT_FOUND = std::string("HTTP/1.1 404 Not Found\r\n");
    const std::string NOT_ALLOWED = std::string("HTTP/1.1 405 Method Not Allowed\r\n");

    const std::string DATE = std::string("Date: ");
    const std::string SERVER = std::string("Server: Highload Static Server\r\n");
    const std::string CONNECTION = std::string("Connection: Closed\r\n");
    const std::string CONTENT_LENGTH = std::string("Content-Length: ");
    const std::string CONTENT_TYPE_HTML = std::string("Content-Type: text/html\r\n");
    const std::string CONTENT_TYPE_CSS = std::string("Content-Type: text/css\r\n");
    const std::string CONTENT_TYPE_JS = std::string("Content-Type: application/javascript\r\n");
    const std::string CONTENT_TYPE_GIF = std::string("Content-Type: image/gif\r\n");
    const std::string CONTENT_TYPE_JPEG = std::string("Content-Type: image/jpeg\r\n");
    const std::string CONTENT_TYPE_PNG = std::string("Content-Type: image/png\r\n");
    const std::string CONTENT_TYPE_SWF = std::string("Content-Type: application/x-shockwave-flash\r\n");
private:
    std::string current_time();
    std::string ok_headers(const std::string, int, const std::string);
    std::string not_ok_headers(const std::string);
    std::string get_file_type();
    std::string url_decode(std::string);
    bool is_dir(std::string);

    std::string url;
    std::string path;// = R"(/var/www/html)";

    std::unordered_map<std::string, std::string> map;

    void handle_last_character(std::string &str);
};



#endif //HIGHLOAD_DZ1_RESPONSE_H
