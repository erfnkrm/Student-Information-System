
FROM ubuntu:22.04 AS build

ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake pkg-config \
    libpq-dev libpqxx-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTS=OFF \
 && cmake --build build -j

# ---- runtime stage ----
FROM ubuntu:22.04 AS runtime
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    libpq-dev libpqxx-dev ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /app/build/sis /app/sis

# Optional: allow overriding connection info via env var PG_CONN
ENV PG_CONN="host=db port=5432 dbname=sis_db user=sis_user password=sis_pass"

ENTRYPOINT ["/app/sis"]