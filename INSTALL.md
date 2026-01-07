# Installation Guide

## Requirements
- Ubuntu (recommended)
- Docker + Docker Compose
- (Optional local build) `cmake`, `g++`, `libpqxx-dev`

## Prerequisites
* **Docker Engine** (Latest version)
* **Docker Compose**
* **Git**

## Setup Instructions
1. Clone the repository:
git clone https://github.com/erfnkrm/cpp-finalproject-ERS
2. Navigate to project directory:
cd cpp-finalproject-ERS

3. Run Docker Compose:
docker-compose up --build

## Stop / remove
```bash
docker compose down
```

If you want to reset the DB volume:
```bash
docker compose down -v
```
