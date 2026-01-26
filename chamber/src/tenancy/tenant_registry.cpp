#include "tenant_registry.h"
#include <pqxx/pqxx>
#include <iostream>

TenantInfo TenantRegistry::resolve(const std::string& signed_key) {
    try {
        pqxx::connection conn("dbname=chamber user=chamber password=chamber_dev host=localhost");
        pqxx::work txn(conn);
        
        auto result = txn.exec_params(
            "SELECT tenant_id, schema_name FROM public.tenants WHERE public_key_hash = $1",
            signed_key
        );
        
        if (result.empty()) {
            std::cerr << "Tenant not found for key: " << signed_key << std::endl;
            return {"unknown", "tenant_demo"};
        }
        
        return {
            result[0][0].as<std::string>(),
            result[0][1].as<std::string>()
        };
        
    } catch (const std::exception& e) {
        std::cerr << "Database error: " << e.what() << std::endl;
        return {"error", "tenant_demo"};
    }
}
