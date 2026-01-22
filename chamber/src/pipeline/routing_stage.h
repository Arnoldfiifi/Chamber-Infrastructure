#pragma once
#include "stage.h"

class RoutingStage : public Stage {
public:
    void process(Context& ctx) override;
};

