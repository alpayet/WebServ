#!/usr/bin/env python3
import os
import sys

query = os.environ.get("QUERY_STRING", "")

if "type=local" in query:
    # Local Redirect Response
    sys.stdout.write("Location: /index.html\r\n\r\n")

elif "type=clientdoc" in query:
    # Client Redirect with Document
    sys.stdout.write("Status: 302 Found\r\n")
    sys.stdout.write("Location: http://wikipedia.org\r\n")
    sys.stdout.write("Content-Type: text/html\r\n\r\n")
    sys.stdout.write("<html><body><p>Redirecting...</p></body></html>")

elif "type=client" in query:
    # Client Redirect Response
    sys.stdout.write("Location: http://toilettes.fr\r\n\r\n")

else:
    # 4. Document Response (Default)
    sys.stdout.write("Content-Type: text/html\r\n\r\n")
    sys.stdout.write("<html><body><h1>Standard Document</h1><a href='/'>Go back</a></body></html>")