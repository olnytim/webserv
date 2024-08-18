#include "../../includes/sockets/req.hpp"

Request::Request() {
    _path = "";
    _query = "";
    _fragment = "";
    _boundary = "";
    _method = UNKNOWN;
    _method_str[GET] = "GET";
    _method_str[HEAD] = "HEAD";
    _method_str[POST] = "POST";
    _method_str[PUT] = "PUT";
    _method_str[DELETE] = "DELETE";
    _body_length = 0;
    _error_code = 0;
    _chunk_length = 0;
    _storage = "";
    _key_storage = "";
    _method_index = 1;
    _body_str = "";
    _fields_done_flag = false;
    _body_flag = false;
    _body_done_flag = false;
    _chunked_flag = false;
    _multiform_flag = false;
}

Request::~Request() {}

void    Request::clear()
{
    _path.clear();
    _error_code = 0;
    _query.clear();
    _fragment.clear();
    _method = UNKNOWN;
    _method_index = 1;
    _state = Request_Line;
    _body_length = 0;
    _chunk_length = 0x0;
    _storage.clear();
    _body_str = "";
    _key_storage.clear();
    _request_headers.clear();
    _server_name.clear();
    _body.clear();
    _boundary.clear();
    _fields_done_flag = false;
    _body_flag = false;
    _body_done_flag = false;
    _complete_flag = false;
    _chunked_flag = false;
    _multiform_flag = false;
}

bool Request::keepAlive() {
    if (_request_headers.find("Connection") != _request_headers.end()) {
        if (_request_headers["Connection"] == "close")
            return false;
    }
    return true;
}