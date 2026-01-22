#include "http_server.h"
#include "../security/key_validator.h"
#include "../tenancy/tenant_registry.h"
#include "../policy/policy_engine.h"
#include "../pipeline/intake_stage.h"
#include "../pipeline/routing_stage.h"

void HttpServer::start(int) {
    Context ctx;
    ctx.request_payload = "example";

    if (!KeyValidator::validate("signed-key")) return;

    auto tenant = TenantRegistry::resolve("signed-key");
    ctx.tenant_id = tenant.tenant_id;
    ctx.schema = tenant.schema;

    IntakeStage intake;
    RoutingStage routing;

    intake.process(ctx);
    PolicyEngine::evaluate(ctx);
    routing.process(ctx);
}

