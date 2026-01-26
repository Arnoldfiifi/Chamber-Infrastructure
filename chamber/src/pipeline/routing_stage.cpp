#include "routing_stage.h"
#include <pqxx/pqxx>
#include <iostream>

void RoutingStage::process(Context& ctx) {
    // Simple routing logic
    std::string model;
    
    if (ctx.metadata["has_code"] == "true") {
        model = "gpt-4";
    } else {
        int token_count = std::stoi(ctx.metadata["token_count"]);
        model = (token_count < 50) ? "phi-3" : "gpt-4o-mini";
    }
    
    ctx.route_to = model;
    ctx.confidence = 1.0f;
    
    // Log to database
    log_decision(ctx);
}

void RoutingStage::log_decision(const Context& ctx) {
    try {
        pqxx::connection conn("dbname=chamber user=chamber password=chamber_dev host=localhost");
        pqxx::work txn(conn);
        
        std::string decision_json = 
            "{\"trace_id\":\"" + ctx.trace_id + "\","
            "\"model\":\"" + ctx.route_to + "\","
            "\"confidence\":" + std::to_string(ctx.confidence) + "}";
        
        txn.exec_params(
            "INSERT INTO " + ctx.schema + ".audit_log (trace_id, decision) VALUES ($1, $2::jsonb)",
            ctx.trace_id,
            decision_json
        );
        
        txn.commit();
        
    } catch (const std::exception& e) {
        std::cerr << "Audit log error: " << e.what() << std::endl;
    }
}
