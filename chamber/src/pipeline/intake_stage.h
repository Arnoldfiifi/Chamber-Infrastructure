#pragma once
#include "stage.h"

class IntakeStage : public Stage {
public:
    void process(Context& ctx) override;
};

