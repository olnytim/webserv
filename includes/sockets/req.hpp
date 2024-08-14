#pragma once

#include "../Headers.hpp"

enum HttpMethod {
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    UNKNOWN
};

enum ParsingState
{
    Request_Line,
    Request_Line_Post_Put,
    Request_Line_Method,
    Request_Line_First_Space,
    Request_Line_URI_Path_Slash,
    Request_Line_URI_Path,
    Request_Line_URI_Query,
    Request_Line_URI_Fragment,
    Request_Line_Ver,
    Request_Line_HT,
    Request_Line_HTT,
    Request_Line_HTTP,
    Request_Line_HTTP_Slash,
    Request_Line_Major,
    Request_Line_Dot,
    Request_Line_Minor,
    Request_Line_CR,
    Request_Line_LF,
    Field_Name_Start,
    Fields_End,
    Field_Name,
    Field_Value,
    Field_Value_End,
    Chunked_Length_Begin,
    Chunked_Length,
    Chunked_Ignore,
    Chunked_Length_CR,
    Chunked_Length_LF,
    Chunked_Data,
    Chunked_Data_CR,
    Chunked_Data_LF,
    Chunked_End_CR,
    Chunked_End_LF,
    Message_Body,
    Parsing_Done
};

class Request {
public:
    std::string                         _path;
    std::string                         _query;
    std::string                         _fragment;
    std::map<std::string, std::string>  _request_headers;
    std::vector<u_int8_t>               _body;
    std::string                         _boundary;
    HttpMethod                          _method;
    std::map<u_int8_t, std::string>     _method_str;
    size_t                              _max_body_size;
    size_t                              _body_length;
    short                               _error_code;
    size_t                              _chunk_length;
    std::string                         _storage;
    std::string                         _key_storage;
    short                               _method_index;
    u_int8_t                            _ver_major;
    u_int8_t                            _ver_minor;
    std::string                         _server_name;
    std::string                         _body_str;
    /* flags */
    bool                                _fields_done_flag;
    bool                                _body_flag;
    bool                                _body_done_flag;
    bool                                _complete_flag;
    bool                                _chunked_flag;
    bool                                _multiform_flag;

    ParsingState                        _state;

    Request();
    ~Request();

    void feed(char *data, size_t size);
    void clear();
    bool keepAlive();
    void cutReqBody(int bytes);
    void headers();
};