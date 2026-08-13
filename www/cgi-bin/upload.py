#!/usr/bin/env python3
import os
import sys
import email
from email.policy import default
from urllib.parse import quote

# 1. Résolution absolue du dossier d'upload (relatif à ce script)
UPLOAD_DIR = "../uploads"
os.makedirs(UPLOAD_DIR, exist_ok=True)

# 2. En-tête HTTP
sys.stdout.write("Content-Type: text/html\r\n\r\n")
sys.stdout.write("<html><body>")

content_type = os.environ.get("CONTENT_TYPE", "")
content_length = int(os.environ.get("CONTENT_LENGTH", 0))

if "multipart/form-data" in content_type and content_length > 0:
    # Lecture exacte du body transmis par le serveur C++ sur stdin
    raw_body = sys.stdin.buffer.read(content_length)

    # Reconstitution d'un message MIME pour le parser 'email'
    mime_headers = f"Content-Type: {content_type}\r\n\r\n".encode("utf-8")
    msg = email.message_from_bytes(mime_headers + raw_body, policy=default)

    uploaded = False
    for part in msg.iter_parts():
        filename = part.get_filename()
        if filename:
            # Sécurité anti-path-traversal
            clean_filename = os.path.basename(filename)
            save_path = os.path.join(UPLOAD_DIR, clean_filename)

            # Récupération des données brutes
            payload = part.get_payload(decode=True)
            if payload is None:
                payload = part.as_bytes()

            with open(save_path, "wb") as f:
                f.write(payload)

            mime_type = part.get_content_type()
            sys.stdout.write(f"<h2>File '{clean_filename}' received successfully!</h2>")

            encoded_filename = quote(clean_filename).replace("'", "%27")

            if mime_type.startswith("image/"):
                sys.stdout.write(
                    f'<img src="/uploads/{encoded_filename}" style="max-width: 600px;'
                    ' border: 2px solid black;" />')
            else:
                sys.stdout.write(f"<p>File type: {mime_type}</p>")
                sys.stdout.write(f'<a href="/uploads/{encoded_filename}">Download / View static file</a>')

            uploaded = True
            break

    if not uploaded:
        sys.stdout.write("<p>Error: No file selected or invalid multipart payload.</p>")
else:
    sys.stdout.write("<p>Error: Invalid request or missing Content-Length/Content-Type.</p>")

sys.stdout.write("<br><br><a href='/'>Go back</a>")
sys.stdout.write("</body></html>")