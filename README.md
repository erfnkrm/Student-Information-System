# Student-Information-System
Final C++ project for the System Programming course.

## Project Objective
The goal of this project is to develop a distributed Student Information System using Ubuntu, Git, GitHub, and Docker/Podman. The system manages student records through a C++ application connected to a PostgreSQL database.

---

## System Components
- **Application Container:** A custom C++ application utilizing strict memory management and pointer arithmetic for saving and managing student records.
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
- Continuous version control and project documentation via GitHub

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
For public use and security best practices, sensitive credentials are not hardcoded. The system uses a `.env` file to manage environment variables for the containers securely.

1. Create a `.env` file in the root directory of the project.
2. Add your configuration variables as shown below:

```env
# Database Configuration
POSTGRES_DB=sis_db
POSTGRES_USER=sis_user
POSTGRES_PASSWORD=your_secure_password_here
POSTGRES_PORT=5432
```

> **Note:** Ensure your `.env` file is added to your `.gitignore` file so your credentials are never accidentally pushed to a public repository.

---

## Running the Project

### Using Docker

**Option 1: Docker Compose V2 (recommended)**
```bash
docker compose up db -d
docker compose run --rm app
```

**Option 2: Docker Compose V1 (legacy)**
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
```text
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