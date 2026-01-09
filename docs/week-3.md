# Week 3 Activity Report (26/12/2025 - 02/01/2026)

## Weekly Summary
Our primary focus was "C++ Application Development". We successfully bridged the gap between the application and the database using `libpqxx`. The system can now connect to the PostgreSQL container, create the necessary tables automatically, and perform basic operations.

## Individual Contributions

### Student 1: Erfan Karimi (Project Manager)
* **Documentation:** Created `docs/MANUAL.md` and added the "Troubleshooting" section for database connection errors.
* **Project Management:** Managed the GitHub Project Board, moving Week 3 tasks to completion.
* **Code Review:** Reviewed and merged Pull Requests for the `libpqxx` integration.
* **Wiki:** Published Week 3 meeting notes and status report.

### Student 2: Sevin Tayfehaliverdi (DevOps Engineer)
* **Docker Orchestration:** Updated `docker-compose.yml` to successfully link the `app` and `db` services on the `ers-network`.
* **Build Fixes:** Resolved the `CMakeLists.txt not found` error by restructuring the root directory.
* **Docker Hub:** Tagged and pushed the latest version (`v0.2-alpha`) to Docker Hub.

### Student 3: Rasa Darabi Purshiraz (C++ Developer)
* **Database Connection:** Implemented the `libpqxx` connection string using the correct environment variables (`ers_db`).
* **Feature Development:** Wrote the C++ logic to automatically create the `students` table upon startup.
* **Refactoring:** Updated `CMakeLists.txt` to properly link dependencies and renamed the executable to `SIS_Project`.

## Project Status
* [x] Database Connection (`libpqxx`) established.
* [x] Table creation logic implemented.
* [x] Docker network communication verified.