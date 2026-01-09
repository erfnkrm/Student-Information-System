# Installation Guide

## System Requirements

### Supported Operating Systems
* **Linux:** Ubuntu 20.04 or higher (recommended)
* **macOS:** 10.15+ with Docker Desktop or Podman Desktop
* **Windows:** Windows 10/11 with WSL2 + Docker Desktop

### Container Runtime (Choose One)

#### Option 1: Docker
* Docker Engine version 20.10+
* Docker Compose version 1.29+ (or Docker Compose V2)

#### Option 2: Podman
* Podman version 4.0+
* podman-compose or use built-in `podman compose` command
* **macOS Only:** Podman Machine must be running

---

## Installation Steps

### 1. Install Container Runtime

#### Docker Installation (Ubuntu)
```bash
# Update package index
sudo apt-get update

# Install Docker
sudo apt-get install docker.io docker-compose -y

# Add your user to docker group (avoid using sudo)
sudo usermod -aG docker $USER

# Log out and back in for group changes to take effect
```

#### Podman Installation (Ubuntu)
```bash
# Update package index
sudo apt-get update

# Install Podman and podman-compose
sudo apt-get install podman podman-compose -y
```

#### macOS Installation
**Docker:**
- Download and install [Docker Desktop for Mac](https://www.docker.com/products/docker-desktop)

**Podman:**
```bash
# Install via Homebrew
brew install podman podman-compose

# Initialize and start Podman machine
podman machine init
podman machine start
```

---

### 2. Clone the Repository
```bash
git clone https://github.com/erfnkrm/cpp-finalproject-ERS
cd cpp-finalproject-ERS
```

---

### 3. Build and Run

#### Using Docker
```bash
# Start database in background
docker-compose up db -d

# Run the application
docker-compose run --rm app
```

#### Using Podman
```bash
# macOS: Ensure Podman machine is running
podman machine start

# Start database in background
podman-compose up db -d

# Run the application
podman-compose run --rm app
```

---

## PostgreSQL Version Note

> **⚠️ Important: Using `:latest` Tag**
> 
> This project uses the `:latest` tag for the PostgreSQL Docker image for educational purposes. However, in production environments, this practice is **strongly discouraged**. The `:latest` tag can silently pull unexpected updates, potentially introducing breaking changes or data incompatibilities.
> 
> **Best Practice:** Always pin database images to specific, tested versions (e.g., `postgres:15.3`) to ensure:
> - Reproducibility across environments
> - Stable and predictable behavior
> - Data integrity and compatibility
> 
> **"Using :latest is like playing Russian roulette with your data."**

---

## Verification

After starting the application, you should see:
```
[INFO] Connected to PostgreSQL.
[INFO] Database schema ensured.

=== Student Information System ===
1) Add student
2) List students
3) Find student
4) Update student
5) Delete student
0) Exit
```

---

## Troubleshooting

### Issue: "Cannot connect to Docker daemon"
**Podman on macOS:** This is expected. Start the Podman machine:
```bash
podman machine start
```

### Issue: Database fails to start (PostgreSQL version mismatch)
If you previously used an older PostgreSQL version, you may need to reset the volume:
```bash
# Docker
docker-compose down -v

# Podman
podman-compose down -v
```

Then start again:
```bash
docker-compose up db -d  # Docker
podman-compose up db -d  # Podman
```

### Issue: Build errors (CMake not found)
The Docker/Podman container handles all dependencies. Ensure:
1. Your Dockerfile is in the project root
2. You're running from the project root directory
3. The build process completes without errors

### Issue: Port 5432 already in use
Another PostgreSQL instance is running. Either:
- Stop the conflicting service
- Change the port mapping in `docker-compose.yml`