# Installation Guide

## Requirements
- Ubuntu (recommended), macOS, or Windows
- Docker + Docker Compose **OR** Podman + podman-compose
- (Optional local build) `cmake`, `g++`, `libpqxx-dev`

## Prerequisites

Choose one of the following container runtimes:

### Option 1: Docker (Recommended)
* **Docker Engine** (Latest version)
* **Docker Compose**
* **Git**

### Option 2: Podman (Docker alternative)
* **Podman** (Latest version)
* **podman-compose** or use `podman compose` subcommand
* **Git**
* **Note for macOS users:** You'll need to start the Podman machine first: `podman machine start`

---

## Setup Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/erfnkrm/Student-Information-System/
   cd Student-Information-System
   ```

2. **Start the database:**
   
   **Docker Compose V2 (recommended):**
   ```bash
   docker compose up db -d
   ```
   
   **Docker Compose V1 (legacy):**
   ```bash
   docker-compose up db -d
   ```
   
   **Podman:**
   ```bash
   podman-compose up db -d
   # OR
   podman compose up db -d
   ```

3. **Run the application:**
   
   **Docker Compose V2:**
   ```bash
   docker compose run --rm app
   ```
   
   **Docker Compose V1:**
   ```bash
   docker-compose run --rm app
   ```
   
   **Podman:**
   ```bash
   podman-compose run --rm app
   # OR
   podman compose run --rm app
   ```

---

## Stop / Remove

**Using Docker:**
```bash
docker-compose down
```

**Using Podman:**
```bash
podman-compose down
# OR
podman compose down
```

### Reset the Database Volume

If you want to reset the DB volume:

**Using Docker:**
```bash
docker-compose down -v
```

**Using Podman:**
```bash
podman-compose down -v
# OR
podman compose down -v
```

---

## PostgreSQL Version Note

> **⚠️ Note on Image Tagging:**
> 
> While this project uses the `:latest` tag for the PostgreSQL Docker image—as requested for educational purposes—it's important to recognize that relying on `:latest` in production environments is generally discouraged. The `:latest` tag can silently pull unexpected updates, potentially introducing breaking changes or inconsistencies. In real-world deployments, it's considered a best practice to pin images to specific, tested versions (e.g., `postgres:15`) to ensure reproducibility, stability, and data integrity. As the saying goes: **"Using :latest is like playing Russian roulette with your data."**

---

## Troubleshooting

### Podman: "Cannot connect to Docker daemon"
This is expected on macOS. Start the Podman machine:
```bash
podman machine start
```

### Database Compatibility Error
If you see errors about PostgreSQL data directory incompatibility when upgrading, remove the volume:
```bash
docker-compose down -v  # Docker
podman-compose down -v  # Podman
```
Then restart the services.
