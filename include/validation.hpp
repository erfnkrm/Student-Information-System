#pragma once
#include <string>
#include "student.hpp"

// Returns empty string if valid; otherwise returns an error message.
std::string validate_student(const Student& s);
bool looks_like_email(const std::string& email);
