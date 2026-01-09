# MANUAL (User Manual)

## Start the Application

### Using Docker
Run the database first, then the application:

**Docker Compose V2 (recommended):**
```bash
docker compose up db -d
docker compose run --rm app
```

**Docker Compose V1 (legacy):**
```bash
docker-compose up db -d
docker-compose run --rm app
```

### Using Podman
**macOS users:** Start the Podman machine first:
```bash
podman machine start
```

Then run:
```bash
podman-compose up db -d
podman-compose run --rm app
# OR
podman compose up db -d
podman compose run --rm app
```

The app will open an interactive CLI menu.

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

## Student Fields
- **ID** (integer) - Unique student identifier
- **First name** (text)
- **Last name** (text)
- **Department** (text)
- **Email** (text) - Must be unique

---

## Usage Examples

### Adding a Student
1. Select option `1`
2. Enter student ID (e.g., `101`)
3. Enter first name (e.g., `John`)
4. Enter last name (e.g., `Doe`)
5. Enter department (e.g., `Computer Science`)
6. Enter email (e.g., `john.doe@example.com`)

### Finding a Student
1. Select option `3`
2. Enter the student ID you want to find
3. The system will display the complete student record

### Listing All Students
1. Select option `2`
2. The system displays all students in the database

### Updating a Student
1. Select option `4`
2. Enter the student ID to update
3. Enter all new information (ID cannot be changed, you're updating the student with this ID)

### Deleting a Student
1. Select option `5`
2. Enter the student ID to delete
3. The student record will be permanently removed

---

## Stopping the Application

To stop the database and clean up:

**Docker Compose V2:**
```bash
docker compose down
```

**Docker Compose V1:**
```bash
docker-compose down
```

**Podman:**
```bash
podman-compose down
```

To also remove all data:
```bash
docker compose down -v      # Docker V2
docker-compose down -v      # Docker V1
podman-compose down -v      # Podman
```
