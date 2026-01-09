#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "db.hpp"
#include "student.hpp"

static std::string get_env(const char* key) {
  const char* v = std::getenv(key);
  return (v && *v) ? std::string(v) : std::string{};
}

int main() {
  const std::string conninfo = get_env("PG_CONN");
  if (conninfo.empty()) {
    std::cout << "PG_CONN not set; skipping db smoke test.\n";
    return 0;
  }

  try {
    Database db(conninfo);
    db.ensure_schema();

    Student s{9999, "Smoke", "Test", "QA", "smoke9999@example.com"};
    try { db.delete_student(s.student_id); } catch (...) { /* ignore if not exists */ }

    db.insert_student(s);
    auto students = db.list_students();

    bool found = false;
    for (const auto& x : students) {
      if (x.student_id == s.student_id) found = true;
    }
    if (!found) throw std::runtime_error("Inserted student not found in list.");

    s.department = "QA2";
    db.update_student(s);

    db.delete_student(s.student_id);
    std::cout << "db smoke test OK\n";
    return 0;
  } catch (const std::exception& e) {
    std::cerr << "db smoke test FAILED: " << e.what() << "\n";
    return 1;
  }
}
