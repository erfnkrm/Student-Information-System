#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <thread>

#include "db.hpp"
#include "logger.hpp"
#include "student.hpp"
#include "validation.hpp"

namespace {

std::string get_env(const char *key, const std::string &fallback) {
  const char *v = std::getenv(key);
  return (v && *v) ? std::string(v) : fallback;
}

int read_int(const std::string &prompt) {
  while (true) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line))
      return 0;
    try {
      size_t idx = 0;
      int v = std::stoi(line, &idx);
      if (idx != line.size())
        throw std::invalid_argument("extra");
      return v;
    } catch (...) {
      std::cout << "Please enter a valid integer.\n";
    }
  }
}

std::string read_string(const std::string &prompt) {
  std::cout << prompt;
  std::string s;
  std::getline(std::cin, s);
  return s;
}

Student read_student_from_user(bool include_id) {
  Student s;
  if (include_id)
    s.student_id = read_int("Student ID: ");
  s.first_name = read_string("First name: ");
  s.last_name = read_string("Last name: ");
  s.department = read_string("Department: ");
  s.email = read_string("Email: ");
  return s;
}

// Very small retry loop to help with "DB not ready yet" situations.
Database connect_with_retries(const std::string &conninfo) {
  constexpr int kRetries = 25;
  for (int i = 1; i <= kRetries; ++i) {
    try {
      return Database(conninfo);
    } catch (const std::exception &e) {
      logging::warn(std::string("DB connection attempt ") + std::to_string(i) +
                    " failed: " + e.what());
      std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }
  }
  throw std::runtime_error("Could not connect to DB after retries.");
}

void print_students(const std::vector<Student> &ss) {
  if (ss.empty()) {
    std::cout << "No students found.\n";
    return;
  }
  std::cout << "\n--- Students ---\n";
  for (const auto &s : ss) {
    std::cout << "ID: " << s.student_id << "\n"
              << "  Name: " << s.first_name << " " << s.last_name << "\n"
              << "  Department: " << s.department << "\n"
              << "  Email: " << s.email << "\n\n";
  }
}

} // namespace

int main() {
  const std::string conninfo = get_env(
      "PG_CONN",
      "host=db port=5432 dbname=sis_db user=sis_user password=sis_pass");

  try {
    auto db = connect_with_retries(conninfo);
    db.ensure_schema();

    while (true) {
      std::cout << "\n=== Student Information System ===\n"
                   "1) Add student\n"
                   "2) List students\n"
                   "3) Update student\n"
                   "4) Delete student\n"
                   "0) Exit\n";

      const int choice = read_int("Select: ");
      try {
        if (choice == 0) {
          std::cout << "Bye.\n";
          break;
        } else if (choice == 1) {
          Student s = read_student_from_user(true);
          const auto err = validate_student(s);
          if (!err.empty()) {
            std::cout << "Validation error: " << err << "\n";
            continue;
          }
          db.insert_student(s);
          std::cout << "Inserted.\n";
        } else if (choice == 2) {
          print_students(db.list_students());
        } else if (choice == 3) {
          Student s = read_student_from_user(true);
          const auto err = validate_student(s);
          if (!err.empty()) {
            std::cout << "Validation error: " << err << "\n";
            continue;
          }
          db.update_student(s);
          std::cout << "Updated.\n";
        } else if (choice == 4) {
          const int id = read_int("Student ID to delete: ");
          db.delete_student(id);
          std::cout << "Deleted.\n";
        } else {
          std::cout << "Unknown option.\n";
        }
      } catch (const std::exception &e) {
        logging::error(e.what());
        std::cout << "Error: " << e.what() << "\n";
      }
    }
  } catch (const std::exception &e) {
    logging::error(std::string("Fatal: ") + e.what());
    std::cerr << "Fatal error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
