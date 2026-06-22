import random

ips = ["192.168.1.1", "10.0.0.45", "172.16.254.1", "192.168.1.99", "8.8.8.8"]
codes = ["200", "200", "200", "404", "500"]

print("Generating 1,000,000 lines of logs... please wait a few seconds...")

with open("sample.log", "w") as f:
    for i in range(1000000):
        ip = random.choice(ips)
        code = random.choice(codes)

        line = f"{ip} - - [21/Jun/2026:12:00:00] \"GET /index.html HTTP/1.1\" {code} 512\n"
        f.write(line)

print("Done! 'sample.log' with 1,000,000 lines generated successfully.")
