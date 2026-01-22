#pragma once
#include <string>

class KeyValidator {
public:
    static bool validate(const std::string& signed_key);
};

