#!/bin/bash

# In Bash, environment variables set by execve are natively accessible.
# ${VAR:-} to prevent errors if the variable is empty/unset.
METHOD="${REQUEST_METHOD:-}"
TARGET_FILE="www/uploads/test.txt"

if [ "$METHOD" = "DELETE" ]; then
	rm "$TARGET_FILE"
    # The CGI could delete a resource in a database or a file here
    printf "Status: 200 OK\r\n"
    printf "Content-Type: text/plain\r\n\r\n"
    printf "The Bash CGI script successfully received and processed your DELETE request."
else
    printf "Status: 405 Method Not Allowed\r\n"
    printf "Content-Type: text/plain\r\n\r\n"
    printf "Method %s is not allowed on this endpoint (Handled by Bash)." "$METHOD"
fi