#include "key_validator.h"

bool KeyValidator::validate(const std::string& signed_key) {
    // For now: accept any non-empty key
    // TODO: Implement proper signature verification
    return !signed_key.empty();
}
