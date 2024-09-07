#include "../includes/Mime.hpp"

Mime::Mime() {
    mime_types[".aac"] = "audio/aac";
    mime_types[".abw"] = "application/x-abiword";
    mime_types[".arc"] = "application/x-freearc";
    mime_types[".avi"] = "video/x-msvideo";
    mime_types[".azw"] = "application/vnd.amazon.ebook";
    mime_types[".bin"] = "application/octet-stream";
    mime_types[".bmp"] = "image/bmp";
    mime_types[".bz"] = "application/x-bzip";
    mime_types[".bz2"] = "application/x-bzip2";
    mime_types[".csh"] = "application/x-csh";
    mime_types[".css"] = "text/css";
    mime_types[".csv"] = "text/csv";
    mime_types[".doc"] = "application/msword";
    mime_types[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    mime_types[".eot"] = "application/vnd.ms-fontobject";
    mime_types[".epub"] = "application/epub+zip";
    mime_types[".gz"] = "application/gzip";
    mime_types[".gif"] = "image/gif";
    mime_types[".htm"] = "text/html";
    mime_types[".html"] = "text/html";
    mime_types[".ico"] = "image/vnd.microsoft.icon";
    mime_types[".ics"] = "text/calendar";
    mime_types[".jar"] = "application/java-archive";
    mime_types[".jpeg"] = "image/jpeg";
    mime_types[".jpg"] = "image/jpeg";
    mime_types[".js"] = "text/javascript";
    mime_types[".json"] = "application/json";
    mime_types[".jsonld"] = "application/ld+json";
    mime_types[".mid"] = "audio/midi";
    mime_types[".midi"] = "audio/midi";
    mime_types[".mjs"] = "text/javascript";
    mime_types[".mp3"] = "audio/mpeg";
    mime_types[".mpeg"] = "video/mpeg";
    mime_types[".mpkg"] = "application/vnd.apple.installer+xml";
    mime_types[".odp"] = "application/vnd.oasis.opendocument.presentation";
}