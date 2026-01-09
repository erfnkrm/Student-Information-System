#include "validation.hpp"

#include <cctype>

static bool is_nonempty_trimmed(const std::string& s) {
  for (unsigned char ch : s) {
    if (!std::isspace(ch)) return true;
  }
  return false;
}

// Intentionally simple email check (good enough for CLI validation):
// - contains exactly one '@'
// - has at least one '.' after '@'
// - no spaces
bool looks_like_email(const std::string& email) {
  if (email.empty()) return false;
  for (unsigned char ch : email) {
    if (std::isspace(ch)) return false;
  }
  const auto at = email.find('@');
  if (at == std::string::npos || at == 0 || at == email.size() - 1) return false;
  if (email.find('@', at + 1) != std::string::npos) return false;
  const auto dot = email.find('.', at + 1);
  if (dot == std::string::npos || dot == at + 1 || dot == email.size() - 1) return false;
  return true;
}

std::string validate_student(const Student& s) {
  if (s.student_id <= 0) return "Student ID must be a positive integer.";
  if (!is_nonempty_trimmed(s.first_name)) return "First name cannot be empty.";
  if (!is_nonempty_trimmed(s.last_name)) return "Last name cannot be empty.";
  if (!is_nonempty_trimmed(s.department)) return "Department cannot be empty.";
  if (!looks_like_email(s.email)) return "Email looks invalid.";
  return {};
}
