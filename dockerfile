FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y gcc make curl libcurl4-openssl-dev libjansson-dev git && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN make

EXPOSE 8000

CMD ["./main", "8000"]
