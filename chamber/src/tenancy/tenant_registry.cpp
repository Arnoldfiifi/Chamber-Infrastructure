#include "tenant_registry.h"

TenantInfo TenantRegistry::resolve(const std::string&) {
    // Normally DB-backed
    return {
        "demo-tenant",
        "tenant_demo"
    };
}

