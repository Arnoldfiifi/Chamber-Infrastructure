#pragma once
#include <string>

struct TenantInfo {
    std::string tenant_id;
    std::string schema;
};

class TenantRegistry {
public:
    static TenantInfo resolve(const std::string& signed_key);
};

