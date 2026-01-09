# Week 4 Activity Report (02/01/2026 - 09/01/2026)

## Weekly Summary
This was the final week of the System Programming Term Project. Our focus was on "Testing, Documentation, and Final Submission". We performed full integrated system testing to ensure the C++ application correctly communicates with the PostgreSQL database. We finalized all documentation, tagged our Docker images for release, and prepared the repository for submission.

## Individual Contributions

### Student 1: Erfan Karimi (Project Manager)
* **Release Management:** Merged `develop` branch into `main` and created the official **v1.0 Release** tag.
* **Documentation:** Finalized `README.md`, `MANUAL.md`, and `INSTALL.md` with final instructions and links.
* **Presentation:** Prepared the slide outline and demo script.
* **Wiki:** Completed the final Wiki documentation.

### Student 2: Sevin Tayfehaliverdi (DevOps Engineer)
* **Final Deployment:** Built production images and pushed them to Docker Hub with the `:v1.0` tag.
* **Infrastructure Polish:** Added `healthcheck` to `docker-compose.yml` for stability.
* **Security:** Verified credentials and environment variables.

### Student 3: Rasa Darabi Purshiraz (C++ Developer)
* **System Testing:** Conducted full CRUD testing (Insert, List, Update, Delete) inside the container.
* **Code Quality:** Refactored `main.cpp` for error handling and added comments.
* **Bug Fixes:** Resolved final connection stability issues.

## Project Status (Final)
* [x] **Docker:** Containers running perfectly.
* [x] **Database:** Persistence verified.
* [x] **Submission:** Ready for evaluation.