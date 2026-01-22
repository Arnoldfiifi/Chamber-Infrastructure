#include "routing_stage.h"

void RoutingStage::process(Context& ctx) {
    ctx.metadata["route"] = "model_A";
}

