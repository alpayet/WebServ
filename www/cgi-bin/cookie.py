#!/usr/bin/env python3
import os
import sys

raw_cookie = os.environ.get("HTTP_COOKIE", "")
visits = 1

# Basic cookie parsing (looking for 'visits=X')
if "visits=" in raw_cookie:
    try:
        parts = raw_cookie.split(";")
        for part in parts:
            if "visits=" in part:
                visits = int(part.split("=")[1]) + 1
    except ValueError:
        pass

sys.stdout.write(f"Set-Cookie: visits={visits}; Path=/\r\n")
sys.stdout.write("Content-Type: text/html\r\n\r\n")

# Body (Document Response)
sys.stdout.write(f"<html><body>")
sys.stdout.write(f"<h1>Session Management</h1>")
sys.stdout.write(f"<p>You have visited this page <b>{visits}</b> times during this session.</p>")
sys.stdout.write(f"<a href='/cgi-bin/cookie.py'>Reload (Increment)</a><br>")
sys.stdout.write(f"<a href='/'>Back to Home</a>")
sys.stdout.write(f"</body></html>")