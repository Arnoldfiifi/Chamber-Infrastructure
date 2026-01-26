#include "intake_stage.h"
#include <sstream>
#include <random>
#include <iomanip>

std::string generate_trace_id() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    
    const char* hex = "0123456789abcdef";
    std::stringstream ss;
    
    for (int i = 0; i < 32; i++) {
        if (i == 8 || i == 12 || i == 16 || i == 20) ss << "-";
        ss << hex[dis(gen)];
    }
    
    return ss.str();
}

void IntakeStage::process(Context& ctx) {
    ctx.trace_id = generate_trace_id();
    ctx.query = ctx.request_payload;
    
    // Basic metadata extraction
    ctx.metadata["token_count"] = std::to_string(ctx.query.length() / 4);
    ctx.metadata["has_code"] = (ctx.query.find("```") != std::string::npos) ? "true" : "false";
    ctx.metadata["intake"] = "complete";
}
