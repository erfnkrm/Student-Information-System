# User Manual - Student Information System (SIS)

## 1. Introduction
The Student Information System (SIS) is a command-line application designed to manage student records. It runs inside a Docker or Podman container and persists data to a PostgreSQL database.

---

## 2. Prerequisites
Before running the system, ensure you have:
* **Container Runtime:** Docker Engine **OR** Podman installed and running
* **Git** installed

---

## 3. How to Run the System

### 3.1 Clone the Repository
```bash
git clone https://github.com/erfnkrm/cpp-finalproject-ERS.git
cd cpp-finalproject-ERS
```

### 3.2 Start the Application

#### Using Docker
```bash
# Start database
docker-compose up db -d

# Run application
docker-compose run --rm app
```

#### Using Podman
**macOS users:** Start Podman machine first:
```bash
podman machine start
```

Then run:
```bash
# Start database
podman-compose up db -d

# Run application
podman-compose run --rm app
```

### 3.3 Verify Connection
Check the terminal logs. You should see:
```
[INFO] Connected to PostgreSQL.
[INFO] Database schema ensured.

=== Student Information System ===
```

---

## 4. Using the System

### 4.1 Main Menu
```
=== Student Information System ===
1) Add student
2) List students
3) Find student
4) Update student
5) Delete student
0) Exit
Select:
```

### 4.2 Operations

#### Add Student (Option 1)
Adds a new student record to the database.

**Steps:**
1. Select `1`
2. Enter Student ID (must be unique, positive integer)
3. Enter First Name
4. Enter Last Name
5. Enter Department
6. Enter Email (must be unique)

**Example:**
```
Select: 1
Student ID: 101
First name: John
Last name: Doe
Department: Computer Science
Email: john.doe@example.com
Inserted.
```

#### List All Students (Option 2)
Displays all student records in the database.

**Steps:**
1. Select `2`

**Example Output:**
```
--- Students ---
ID: 101
  Name: John Doe
  Department: Computer Science
  Email: john.doe@example.com
```

#### Find Student (Option 3)
Searches for a specific student by ID.

**Steps:**
1. Select `3`
2. Enter Student ID to find

**Example:**
```
Select: 3
Student ID to find: 101

--- Found Student ---
ID: 101
  Name: John Doe
  Department: Computer Science
  Email: john.doe@example.com
```

#### Update Student (Option 4)
Updates all information for an existing student (except ID).

**Steps:**
1. Select `4`
2. Enter Student ID to update
3. Enter all new information (first name, last name, department, email)

#### Delete Student (Option 5)
Permanently removes a student record.

**Steps:**
1. Select `5`
2. Enter Student ID to delete

**Example:**
```
Select: 5
Student ID to delete: 101
Deleted.
```

#### Exit (Option 0)
Exits the application.

---

## 5. Data Validation

The system validates input data:
- **Student ID:** Must be a positive integer
- **Email:** Must be unique across all students
- **All fields:** Cannot be empty

Invalid data will trigger an error message.

---

## 6. Troubleshooting

### Database Connection Failed
If the application says "Could not connect to DB after retries":

1. **Check if database container is running:**
   ```bash
   docker ps      # Docker
   podman ps      # Podman
   ```

2. **Check database logs:**
   ```bash
   docker-compose logs db      # Docker
   podman-compose logs db      # Podman
   ```

3. **Verify connection string:**
   The application uses environment variable `PG_CONN` with default:
   ```
   host=db port=5432 dbname=sis_db user=sis_user password=sis_pass
   ```
   (Note: uses `host=db`, not `localhost`)

### Podman: Cannot Connect to Daemon (macOS)
Start the Podman machine:
```bash
podman machine start
```

### Database Version Compatibility
If upgrading PostgreSQL versions, you may need to reset the database:
```bash
docker-compose down -v      # Docker
podman-compose down -v      # Podman
```

### Build Errors
If build fails:
1. Ensure you're in the project root directory
2. Check that `Dockerfile` and `CMakeLists.txt` exist
3. Rebuild from scratch:
   ```bash
   docker-compose build --no-cache app      # Docker
   podman-compose build --no-cache app      # Podman
   ```

---

## 7. Stopping the System

### Stop Containers
```bash
docker-compose down      # Docker
podman-compose down      # Podman
```

### Stop and Remove All Data
```bash
docker-compose down -v      # Docker (removes volumes)
podman-compose down -v      # Podman (removes volumes)
```

---

## 8. Database Credentials

**Default Configuration:**
- Database Name: `sis_db`
- Username: `sis_user`
- Password: `sis_pass`
- Port: `5432`

These can be modified in `docker-compose.yml`.

---

## 9. Support

For issues or questions:
- Check `INSTALL.md` for installation help
- Review `README.md` for project overview
- Check GitHub Issues: https://github.com/erfnkrm/cpp-finalproject-ERS/issues