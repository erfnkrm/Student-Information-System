#include "db.hpp"

#include <stdexcept>

#include "logger.hpp"
#include "validation.hpp"

Database::Database(std::string conninfo) : conninfo_(std::move(conninfo)) {
  reconnect_if_needed();
}

void Database::reconnect_if_needed() {
  if (conn_ && conn_->is_open()) return;

  conn_ = std::make_unique<pqxx::connection>(conninfo_);
  if (!conn_->is_open()) {
    throw std::runtime_error("Failed to open PostgreSQL connection.");
  }
  log::info("Connected to PostgreSQL.");
}

void Database::insert_student(const Student& s) {
  const auto err = validate_student(s);
  if (!err.empty()) throw std::invalid_argument(err);

  reconnect_if_needed();
  pqxx::work tx{*conn_};

  tx.exec_params(
      "INSERT INTO students (student_id, first_name, last_name, department, email) "
      "VALUES ($1, $2, $3, $4, $5)",
      s.student_id, s.first_name, s.last_name, s.department, s.email);

  tx.commit();
}

std::vector<Student> Database::list_students() {
  reconnect_if_needed();
  pqxx::read_transaction tx{*conn_};

  pqxx::result r =
      tx.exec("SELECT student_id, first_name, last_name, department, email "
              "FROM students ORDER BY student_id");

  std::vector<Student> out;
  out.reserve(static_cast<size_t>(r.size()));

  for (const auto& row : r) {
    Student s;
    s.student_id = row["student_id"].as<int>();
    s.first_name = row["first_name"].c_str();
    s.last_name = row["last_name"].c_str();
    s.department = row["department"].c_str();
    s.email = row["email"].c_str();
    out.push_back(std::move(s));
  }
  return out;
}

void Database::update_student(const Student& s) {
  const auto err = validate_student(s);
  if (!err.empty()) throw std::invalid_argument(err);

  reconnect_if_needed();
  pqxx::work tx{*conn_};

  pqxx::result r = tx.exec_params(
      "UPDATE students "
      "SET first_name=$2, last_name=$3, department=$4, email=$5 "
      "WHERE student_id=$1",
      s.student_id, s.first_name, s.last_name, s.department, s.email);

  if (r.affected_rows() == 0) {
    tx.abort();
    throw std::runtime_error("No student found with that ID.");
  }

  tx.commit();
}

void Database::delete_student(int student_id) {
  if (student_id <= 0) throw std::invalid_argument("Student ID must be positive.");

  reconnect_if_needed();
  pqxx::work tx{*conn_};

  pqxx::result r =
      tx.exec_params("DELETE FROM students WHERE student_id=$1", student_id);

  if (r.affected_rows() == 0) {
    tx.abort();
    throw std::runtime_error("No student found with that ID.");
  }

  tx.commit();
}

