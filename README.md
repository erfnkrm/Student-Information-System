# cpp-finalproject-ERS
Final C++ project for the System Programming course, instructed by Osman Selvi.

## Project Objective
The goal of this project is to develop a distributed Student Information System using Ubuntu, Git, GitHub, and Docker/Podman. The system manages student records through a C++ application connected to a PostgreSQL database.

---

## System Components
- **Application Container:** A custom C++ application for saving and managing student records.
- **Database Container:** A PostgreSQL database for persistent data storage.
- **Networking:** Private network communication between containers.

---

## Key Features
- Save student records (ID, Name, Surname, Department, Email)
- **Find** student by ID
- List and display all student information
- Update student entries
- Delete student records
- Stable database transaction management via libpqxx
- Comprehensive input validation

---

## Team Roles
- **Erfan Karimi** (Project Manager): GitHub management, reporting, and documentation.
- **Rasa Darabi Purshiraz** (DevOps): Docker infrastructure, CI/CD, and image management.
- **Sevin Tayfehaliverdi** (C++ Developer): Application logic, database connection, and testing.

---

## Docker Hub Repositories (Mandatory)
- PostgreSQL Image: `[RasaDarabi-stu]/sis-project-postgres:latest`
- Application Image: `[RasaDarabi-stu]/sis-project-app:latest`

---

## Technologies Used
- **Language:** Modern C++ (C++11 or higher)
- **Platform:** Ubuntu Linux (primary), macOS, Windows (via WSL2)
- **Container Runtime:** Docker or Podman
- **Version Control:** Git Flow strategy via GitHub
- **CI/CD:** GitHub Actions for automated testing

---

## System Architecture
This project consists of two main Docker/Podman containers:
1. **Database:** PostgreSQL (Official Image with `:latest` tag)
2. **Application:** Custom C++ Application

---

## Configuration
The system uses the following default credentials in `docker-compose.yml`:
- **Database:** `sis_db`
- **User:** `sis_user`
- **Password:** `sis_pass`
- **Port:** `5432`

---

## Running the Project

### Using Docker
1. Ensure Docker is running.
2. Build and start the system:
   ```bash
   docker-compose up db -d
   docker-compose run --rm app
   ```

### Using Podman
1. **macOS:** Start Podman machine: `podman machine start`
2. Build and start the system:
   ```bash
   podman-compose up db -d
   podman-compose run --rm app
   ```

The application will automatically connect to the database and initialize the tables.

---

## ⚠️ Note on Image Tagging

> **Important for Educational Purposes:**
> 
> While this project uses the `:latest` tag for the PostgreSQL Docker image—as requested for educational purposes—it's important to recognize that relying on `:latest` in production environments is generally discouraged. The `:latest` tag can silently pull unexpected updates, potentially introducing breaking changes or inconsistencies. In real-world deployments, it's considered a best practice to pin images to specific, tested versions (e.g., `postgres:15`) to ensure reproducibility, stability, and data integrity. As the saying goes: **"Using :latest is like playing Russian roulette with your data."**

---

## Documentation
- **[INSTALL.md](INSTALL.md)** - Installation and setup instructions
- **[MANUAL.md](MANUAL.md)** - User manual and usage guide
- **[docs/INSTALL.md](docs/INSTALL.md)** - Detailed installation guide
- **[docs/MANUAL.md](docs/MANUAL.md)** - Comprehensive user manual

---

## Menu Options
```
=== Student Information System ===
1) Add student
2) List students
3) Find student
4) Update student
5) Delete student
0) Exit
```

---

## License
This project is for educational purposes as part of the System Programming course.
