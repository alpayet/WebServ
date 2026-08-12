#!/usr/bin/env python3
import os
import sys
import cgi

# Mandatory to prevent crashes if the directory does not exist
UPLOAD_DIR = "../uploads/"
if not os.path.exists(UPLOAD_DIR):
    os.makedirs(UPLOAD_DIR)

# cgi.FieldStorage handles multipart using the environment and stdin
form = cgi.FieldStorage(fp=sys.stdin.buffer, environ=os.environ)

sys.stdout.write("Content-Type: text/html\r\n\r\n")
sys.stdout.write("<html><body>")

if "file_to_upload" in form:
    fileitem = form["file_to_upload"]
    if fileitem.filename:
        filename = os.path.basename(fileitem.filename)
        save_path = os.path.join(UPLOAD_DIR, filename)

        # Binary save of the file
        with open(save_path, 'wb') as f:
            f.write(fileitem.file.read())

        sys.stdout.write(f"<h2>File '{filename}' received successfully!</h2>")

        # Conditional display (Image vs Other)
        if fileitem.type.startswith("image/"):
            sys.stdout.write(f"<img src='/uploads/{filename}' style='max-width: 600px; border: 2px solid black;' />")
        else:
            sys.stdout.write(f"<p>File type: {fileitem.type}</p>")
            sys.stdout.write(f"<a href='/uploads/{filename}'>Download / View static file</a>")
    else:
        sys.stdout.write("<p>Error: No file selected.</p>")
else:
    sys.stdout.write("<p>Error: Invalid request or missing data.</p>")

sys.stdout.write("<br><br><a href='/'>Go back</a>")
sys.stdout.write("</body></html>")