#pragma once
#include <memory>
#include <string>
#include <vector>

#include <pqxx/pqxx>

#include "student.hpp"

class Database {
public:
  explicit Database(std::string conninfo);

  void ensure_schema();

  void insert_student(const Student &s);
  Student find_student(int student_id);
  std::vector<Student> list_students();
  void update_student(const Student &s);
  void delete_student(int student_id);

private:
  std::unique_ptr<pqxx::connection> conn_;
  std::string conninfo_;

  void reconnect_if_needed();
};
