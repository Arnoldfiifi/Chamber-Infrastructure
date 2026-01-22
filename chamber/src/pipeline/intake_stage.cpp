#include "intake_stage.h"

void IntakeStage::process(Context& ctx) {
    ctx.metadata["intake"] = "ok";
}

