#!/usr/bin/env python3
import os
import sys
import email
from email.policy import default
from urllib.parse import quote

# 1. Résolution absolue du dossier d'upload (relatif à ce script)
UPLOAD_DIR = "../uploads"
os.makedirs(UPLOAD_DIR, exist_ok=True)


def emit_head():
    # En-tête HTTP + fenêtre terminal (réutilise la feuille de style du site)
    sys.stdout.write("Content-Type: text/html\r\n\r\n")
    sys.stdout.write("""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>upload &mdash; response</title>
<link rel="icon" href="/favicon.svg" type="image/svg+xml">
<link rel="stylesheet" href="/style.css">
</head>
<body>
<div class="wrap">
  <div class="term">
    <div class="term-bar">
      <div class="tl"><span class="r"></span><span class="y"></span><span class="g"></span></div>
      <div class="term-title"><b>upload.py</b> &mdash; response</div>
    </div>
    <div class="term-body">
      <div class="boot">
        <div class="line"><span class="prompt"></span><span class="verb post">POST</span> <span class="path">/cgi-bin/upload.py</span></div>
""")


def emit_status(ok, msg):
    # Ligne de statut puis ouverture du bloc de contenu
    tag = '<span class="ok">[ 200 ]</span>' if ok else '<span style="color:var(--red)">[ 400 ]</span>'
    sys.stdout.write('        <div class="line">%s <span class="muted">%s</span></div>\n' % (tag, msg))
    sys.stdout.write("      </div>\n")  # close .boot
    sys.stdout.write('      <div class="cmd" style="border-top:none;padding-top:0.4rem">\n')


def emit_foot():
    sys.stdout.write("""        <a class="go" href="/" style="display:inline-block;margin-top:0.4rem">&larr; back to suite</a>
      </div>
    </div>
  </div>
</div>
</body>
</html>""")


emit_head()

content_type = os.environ.get("CONTENT_TYPE", "")
try:
    content_length = int(os.environ.get("CONTENT_LENGTH") or 0)
except ValueError:
    content_length = 0

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
            size = len(payload)
            encoded_filename = quote(clean_filename)

            emit_status(True, f"{size} bytes written to /uploads/{clean_filename}")
            sys.stdout.write(f'<div class="cmd-head"><span class="cmd-title">File received &mdash; {clean_filename}</span></div>')
            sys.stdout.write(f'<p class="cmd-desc">type <code>{mime_type}</code> &middot; {size} bytes &middot; saved to <code>/uploads/{clean_filename}</code></p>')

            if mime_type.startswith("image/"):
                sys.stdout.write(
                    f'<img src="/uploads/{encoded_filename}" alt="{clean_filename}"'
                    ' style="max-width:100%;border:1px solid var(--border);border-radius:10px;display:block;margin:0.2rem 0 0.9rem" />')
            else:
                sys.stdout.write(
                    f'<a class="go" href="/uploads/{encoded_filename}"'
                    ' style="display:inline-block;margin:0.2rem 0 0.9rem">open static file &rarr;</a>')

            uploaded = True
            break

    if not uploaded:
        emit_status(False, "no file selected or invalid multipart payload")
        sys.stdout.write('<p class="cmd-desc">The request was multipart but carried no file part.</p>')
else:
    emit_status(False, "missing or invalid Content-Type / Content-Length")
    sys.stdout.write('<p class="cmd-desc">Expected <code>multipart/form-data</code> with a non-zero body.</p>')

emit_foot()
