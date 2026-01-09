#include "db.hpp"

#include "logger.hpp"

void Database::ensure_schema() {
  reconnect_if_needed();
  pqxx::work tx{*conn_};
  tx.exec(R"SQL(
    CREATE TABLE IF NOT EXISTS students (
      student_id  INTEGER PRIMARY KEY,
      first_name  TEXT NOT NULL,
      last_name   TEXT NOT NULL,
      department  TEXT NOT NULL,
      email       TEXT NOT NULL UNIQUE,
      created_at  TIMESTAMPTZ NOT NULL DEFAULT NOW(),
      updated_at  TIMESTAMPTZ NOT NULL DEFAULT NOW()
    );
  )SQL");
  tx.exec(R"SQL(
    CREATE OR REPLACE FUNCTION set_updated_at()
    RETURNS TRIGGER AS $$
    BEGIN
      NEW.updated_at = NOW();
      RETURN NEW;
    END;
    $$ LANGUAGE plpgsql;
  )SQL");
  tx.exec(R"SQL(
    DO $$
    BEGIN
      IF NOT EXISTS (
        SELECT 1 FROM pg_trigger WHERE tgname = 'trg_students_updated_at'
      ) THEN
        CREATE TRIGGER trg_students_updated_at
        BEFORE UPDATE ON students
        FOR EACH ROW
        EXECUTE FUNCTION set_updated_at();
      END IF;
    END $$;
  )SQL");
  tx.commit();
  logging::info("Database schema ensured.");
}
