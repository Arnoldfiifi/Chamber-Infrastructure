#pragma once
#include "../types/context.h"

class Stage {
public:
    virtual void process(Context& ctx) = 0;
    virtual ~Stage() = default;
};

