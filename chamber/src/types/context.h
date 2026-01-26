#pragma once
#include <string>
#include <unordered_map>

struct Context {
    // Identity
    std::string tenant_id;
    std::string schema;
    std::string trace_id;
    
    // Request
    std::string query;
    std::string request_payload;
    
    // Metadata
    std::unordered_map<std::string, std::string> metadata;
    
    // Decision
    std::string decision;
    std::string route_to;
    float confidence = 0.0f;
};
