#include "../../includes/parsing/cluster.hpp"

Config::Config() {
    printf("ConfigFile was created\n");
}

Config::~Config() {
}

void Config::reportError(const ParseException &ex) const {
    throw ex;
}

// opening config file
int Config::getTypePath(const std::string &path) {
    struct stat sb = {};
    if (stat(path.c_str(), &sb) == 0) {
        if (S_ISREG(sb.st_mode))
            return 1;
        else if (S_ISDIR(sb.st_mode))
            return 2;
        else
            return 3;
    }
    return 0;
}

std::string Config::getContent(const std::string &path) {
    if (path.empty())
        return "";
    std::ifstream file(path.c_str());
    if (!file.is_open() || !file)
        return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool Config::isFileExistAndReadable(const std::string &path, const std::string &index) {
    if (getTypePath(index) == 1 && access(index.c_str(), R_OK) == 0)
        return true;
    if (getTypePath(path + index) == 1 && access((path + index).c_str(), R_OK) == 0)
        return true;
    return false;
}

std::string Config::getFile() {
    return conf_file;
}

// creating cluster of servers
// проверить правильно ли работает удаление комментариев
// проверить правильно ли работает удаление пробелов
void Config::parseConfig(std::string &content) {
    // remove comments
    size_t start_pos = 0;
    while ((start_pos = content.find('#', start_pos)) != std::string::npos) {
        size_t end_pos = content.find('\n', start_pos);
        if (end_pos == std::string::npos)
            content.erase(start_pos);
        else
            content.erase(start_pos, end_pos - start_pos);
    }
    // remove whitespaces
    start_pos = content.find_first_not_of(" \t\n\r\f\v");
    if (start_pos == std::string::npos) {
        content.clear();
        return;
    }
    size_t end_pos = content.find_last_not_of(" \t\n\r\f\v");
    content = content.substr(start_pos, end_pos - start_pos + 1);
}

// здесь нужен хороший парсинг всего конфига, чтобы разделить его на сервера.
// разделение на сервера начинается с 'server {' и заканчивается '}'
// сейчас код не корректно работает, так как не учитывает вложенные блоки
// и заканчивает парсить сервера на первой встреченной закрывающей скобке
// нужно сделать так, чтобы парсер учитывал вложенные блоки и заканчивал парсить
// сервер на закрывающей скобке, которая соответствует открывающей
// при отсутствии закрывающей скобки нужно выкидывать исключение
// этот метод - полный костыль
void Config::splitServers(const std::string &content) {
//    size_t start_pos = 0;
//    size_t end_pos = 0;
//    while ((start_pos = content.find("server {", start_pos)) != std::string::npos) {
//        end_pos = content.find("}", start_pos);
//        if (end_pos == std::string::npos)
//            reportError(ParseException("Can't find closing bracket"));
//        server_config.push_back(content.substr(start_pos, end_pos - start_pos + 1));
//        start_pos = end_pos + 1;
//    }
//    amount_of_servers = server_config.size();
    size_t start = 0;
    size_t end = 0;
    size_t scope = 0;
    bool foundServer = false;

    if (content.find("server") == std::string::npos)
        reportError(ParseException("No server block found"));

    while (start < content.length())
    {
        // Поиск начала блока сервера
        while (start < content.length() && !foundServer)
        {
            if (content[start] == 's')
            {
                if (content.compare(start, 6, "server") == 0)
                {
                    start += 6;
                    while (start < content.length() && isspace(content[start]))
                        start++;
                    if (content[start] == '{')
                    {
                        foundServer = true;
                        start++; // Пропустить '{'
                    }
                    else
                        reportError(ParseException("Problem with server block start"));
                }
            }
            else
            {
                if (!isspace(content[start]))
                    reportError(ParseException("Problem with server block start"));
                start++;
            }
        }

        if (!foundServer)
            reportError(ParseException("No server block found"));

        // Поиск конца блока сервера
        scope = 1;
        end = start;
        while (end < content.length() && scope > 0)
        {
            if (content[end] == '{')
                scope++;
            else if (content[end] == '}')
                scope--;
            end++;
        }

        if (scope != 0)
            reportError(ParseException("Problem with server block end"));

        // Добавление найденного блока в конфигурацию
        this->server_config.push_back(content.substr(start - 1, end - start + 1));

        // Сброс флага и установка следующего поиска
        foundServer = false;
        start = end;
    }
    amount_of_servers = server_config.size();
}

std::vector<std::string> Config::splitParams(const std::string &content, const std::string &delim) {
//    std::vector<std::string> params;
//    size_t start_pos = 0;
//    size_t end_pos = 0;
//    while ((start_pos = content.find(delim, start_pos)) != std::string::npos) {
//        end_pos = content.find(delim, start_pos + 1);
//        if (end_pos == std::string::npos)
//            end_pos = content.size();
//        params.push_back(content.substr(start_pos, end_pos - start_pos));
//        start_pos = end_pos + 1;
//    }
//    return params;
    std::vector<std::string>	str;
    std::string::size_type		start, end;

    start = end = 0;
    while (1)
    {
        end = content.find_first_of(delim, start);
        if (end == std::string::npos)
            break;
        std::string tmp = content.substr(start, end - start);
        str.push_back(tmp);
        start = content.find_first_not_of(delim, end);
        if (start == std::string::npos)
            break;
    }
    return (str);
}

// этот метод - полный костыль
// нужно будет переделать, чтобы он правильно парсил параметры сервера
void Config::createServer(std::string &config, ServerBlock &server) {
    std::vector<std::string> params;
    std::vector<std::string> error_codes;
    bool loca_flag = false;
    bool size_flag = false;
    bool index_flag = false;

    printf("'%s'\n", config.c_str());
    params = splitParams(config, std::string(" \n\t"));
    for (size_t i = 0; i < params.size(); ++i) {
        printf("Param %lu: '%s'\n", i, params[i].c_str());
    }
    if (params.size() < 3)
        reportError(ParseException("Server block is empty"));
    for (size_t i = 0; i < params.size(); ++i) {
        if (params[i] == "listen" && (i + 1) < params.size() && !loca_flag) {
            if (server.getPort()) {
                reportError(ParseException("Port is already set"));
            }
            server.setPort(params[++i]);
        }
        else if (params[i] == "host" && (i + 1) < params.size() && !loca_flag) {
            if (server.getHost())
                reportError(ParseException("Host is already set"));
            server.setHost(params[++i]);
        }
        else if (params[i] == "root" && (i + 1) < params.size() && !loca_flag) {
            if (!server.getRoot().empty())
                reportError(ParseException("Root is already set"));
            server.setRoot(params[++i]);
        }
        else if (params[i] == "server_name" && (i + 1) < params.size() && !loca_flag) {
            if (!server.getServerName().empty())
                reportError(ParseException("Server name is already set"));
            server.setServerName(params[++i]);
        }
        else if (params[i] == "index" && (i + 1) < params.size() && !loca_flag) {
            if (!server.getIndex().empty())
                reportError(ParseException("Index is already set"));
            server.setIndex(params[++i]);
        }
        else if (params[i] == "client_max_body_size" && (i + 1) < params.size() && !loca_flag) {
            if (size_flag)
                reportError(ParseException("Client max body size is already set"));
            server.setClientMaxBodySize(params[i + 1]);
            size_flag = true;
        }
        else if (params[i] == "autoindex" && (i + 1) < params.size() && !loca_flag) {
            if (index_flag)
                reportError(ParseException("Autoindex is already set"));
            server.setAutoindex(params[++i]);
            index_flag = true;
        }
        else if (params[i] == "error_page" && (i + 1) < params.size() && !loca_flag) {
            ; // тут прописать логику для создания вектора error_pages
        }
        else if (params[i] == "location" && (i + 1) < params.size()) {
            ; // тут прописать логику для создания поля location
            loca_flag = true;
        }
//        else if (params[i] != "}" && params[i] != "{") {
//            if (loca_flag)
//                reportError(ParseException("Location block is not closed or param after location"));
//            reportError(ParseException("'" + params[i] + "' invalid parameter"));
//        }
    }
    if (server.getRoot().empty())
        server.setRoot("/;");
    if (server.getHost() == 0)
        server.setHost("localhost;");
    if (server.getIndex().empty())
        server.setIndex("index.html;");
    // check if index file exists and readable
    // check if location is not duplicated
    // check if errorpages are reachable and readable
}

void Config::createCluster(const std::string &config_file) {
    // проверка корректности файла
    conf_file = config_file;
    std::string content = getContent(config_file);
    if (content.empty())
        reportError(ParseException(config_file + " is empty"));
    if (access(config_file.c_str(), R_OK) != 0)
        reportError(ParseException("Can't read file " + config_file));
    if (getTypePath(config_file) != 1)
        reportError(ParseException("File " + config_file + " is not a regular file"));

    // парсинг конфига
    parseConfig(content);
    splitServers(content);

    // создание серверов и готово кластера
    for (size_t i = 0; i < amount_of_servers; ++i) {
        ServerBlock server;
        createServer(server_config[i], server);
        servers.push_back(server);
    }
    printf("Cluster was created\n");
}