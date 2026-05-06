* This project has been created as part of the 42 curriculum by alpayet, ludebion and mlouis *

# Description
The goal is to make an HTTP server.

![Class diagram of the parsing](diagrams/parsing.svg)


![Class diagram of the server](diagrams/server.svg)

# Instructions
To launch the program, use the command line
`./webserv [configuration file]`
Configuration file ressemble the server block of the nginx file:
```
server {
	listen 80;
	location / {
		root "lalala";
	}
}
```
Some differences exist between the two files such as no redefinition of values, for example, if you already defined an index in a location block, you can't reuse the keyword `index` inside that block.


server:
location:
listen:
server_name:
root:
index:
cgi:
error_page:



# Resourses
[Mozilla developer doc on HTTP](https://developer.mozilla.org/en-US/docs/Web/HTTP)

[RFC on HTTP/1.1](https://datatracker.ietf.org/doc/html/rfc9112)

[Code(quoi); article on network programmation](https://www.codequoi.com/programmation-reseau-via-socket-en-c/)

[Nginx server block](https://docs.nginx.com/nginx/admin-guide/web-server/web-server/)