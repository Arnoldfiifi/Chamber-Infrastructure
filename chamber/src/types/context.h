#pragma once
#include <string>
#include <unordered_map>

struct Context {
    std::string tenant_id;
    std::string schema;
    std::string request_payload;
    std::unordered_map<std::string, std::string> metadata;
    std::string decision;
};

