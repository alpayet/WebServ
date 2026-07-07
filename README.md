*This project has been created as part of the 42 curriculum by alpayet, ludebion and mlouis*

# Description
The goal is to make an HTTP server.


# Instructions
To launch the program, use the command line
`./webserv <configuration file>`

Configuration file ressemble the server block of the nginx file:
```
server {
	listen 8081;
	hostname 10.15.2.1;

	root /var/www/html/
	
	location / {
		root /var/www/html/example;
		index index.html index.htm;
	}
	
	location /banana/ {
		return 404;
	}

	location /lalala/ {
		autoindex on;
	}

	location /cgi-bin/ {
		cgi test.py;
	}
	
	error_page 500 /500.html;
	error_page 404 /404.html;
}
```

Some differences exist between the two files such as no redefinition of values, for example, if you already defined an index in a location block, you can't reuse the keyword `index` inside that block.
Also, every location and root has to be a directory, whereas index can't have any directory.

`server`: defines the start of a server setup

`hostname`: name of to identify the server, must be unique in configuration file

`root` (outside location block): path for the server, the location blocks without a root directive will append there path to that route 

`location`: starts of the location block for a specific path

`root` (in location block): use as an alias to replace the path of the location block (the one the user will enter but end up internally where defined by the root directive)

`listen`: defines the port used

`index`: goes with the root, it's the default page if you access a specific directory declare with the root

`cgi`: common gateway interface, this is used to launch script

`error_page`: define where to find the error page file for a specific http error code

`client_max_body_size`: cap the size of the response

`limit_except`: turn all methods to false, then the mentionned ones are the one allowed

`autoindex`: when on, go to directory listing

`return`: directly return the error code mentionned



# Resourses
[Mozilla developer doc on HTTP](https://developer.mozilla.org/en-US/docs/Web/HTTP)

[RFC on HTTP/1.1](https://datatracker.ietf.org/doc/html/rfc9112)

[Code(quoi); article on network programmation](https://www.codequoi.com/programmation-reseau-via-socket-en-c/)

[Nginx server block](https://docs.nginx.com/nginx/admin-guide/web-server/web-server/)

[CGI](https://www.stat.berkeley.edu/~spector/s133/Cgi1a.html)

[Clean Architecture](https://blog.cleancoder.com/uncle-bob/2012/08/13/the-clean-architecture.html)