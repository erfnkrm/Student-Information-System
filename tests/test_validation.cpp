#include <cassert>
#include <iostream>

#include "student.hpp"
#include "validation.hpp"

static void test_email() {
  assert(looks_like_email("a@b.com"));
  assert(looks_like_email("john.doe@itu.edu.tr"));
  assert(!looks_like_email(""));
  assert(!looks_like_email("no-at-symbol.com"));
  assert(!looks_like_email("@missing-local.com"));
  assert(!looks_like_email("missing-domain@"));
  assert(!looks_like_email("has space@x.com"));
  assert(!looks_like_email("double@@x.com"));
  assert(!looks_like_email("a@b"));
}

static void test_student_validation() {
  Student s{1, "Ada", "Lovelace", "CS", "ada@itu.edu.tr"};
  assert(validate_student(s).empty());

  s.student_id = 0;
  assert(!validate_student(s).empty());
  s.student_id = 1;

  s.email = "bad";
  assert(!validate_student(s).empty());
}

int main() {
  test_email();
  test_student_validation();
  std::cout << "validation tests OK\n";
  return 0;
}
