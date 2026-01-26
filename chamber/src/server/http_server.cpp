#include "http_server.h"
#include "../external/httplib.h"
#include "../security/key_validator.h"
#include "../tenancy/tenant_registry.h"
#include "../policy/policy_engine.h"
#include "../pipeline/intake_stage.h"
#include "../pipeline/routing_stage.h"
#include <iostream>

void HttpServer::start(int port) {
    httplib::Server server;
    
    // Health check
    server.Get("/health", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("OK", "text/plain");
    });
    
    // Main endpoint
    server.Post("/classify", [](const httplib::Request& req, httplib::Response& res) {
        try {
            // Get API key
            auto api_key = req.get_header_value("X-API-Key");
            if (api_key.empty()) {
                res.status = 401;
                res.set_content("{\"error\":\"Missing API key\"}", "application/json");
                return;
            }
            
            // Validate key
            if (!KeyValidator::validate(api_key)) {
                res.status = 401;
                res.set_content("{\"error\":\"Invalid API key\"}", "application/json");
                return;
            }
            
            // Resolve tenant
            auto tenant = TenantRegistry::resolve(api_key);
            
            // Build context
            Context ctx;
            ctx.tenant_id = tenant.tenant_id;
            ctx.schema = tenant.schema;
            ctx.request_payload = req.body;
            
            // Execute pipeline
            IntakeStage().process(ctx);
            PolicyEngine::evaluate(ctx);
            RoutingStage().process(ctx);
            
            // Return response
            std::string response = 
                "{\"model\":\"" + ctx.route_to + "\","
                "\"confidence\":" + std::to_string(ctx.confidence) + ","
                "\"trace_id\":\"" + ctx.trace_id + "\"}";
            
            res.set_content(response, "application/json");
            
        } catch (const std::exception& e) {
            res.status = 500;
            res.set_content(
                "{\"error\":\"" + std::string(e.what()) + "\"}", 
                "application/json"
            );
        }
    });
    
    std::cout << "Chamber starting on port " << port << "..." << std::endl;
    server.listen("0.0.0.0", port);
}
