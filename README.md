*This project has been created as part of the 42 curriculum by alpayet, ludebion and mlouis*

# Description

The goal is to make an HTTP server.

## Server part (reactor / networking layer)

This part of the project (`src/infrastructure/server/`) implements the core network of the server: a
single-threaded event loop based on the "**Reactor pattern**", which multiplexes all connections
(listening sockets, client connections, CGI pipes) on a single thread, without threads or sockets
blocking.

**Reactor** (`reactor/Reactor.cpp`) controls the main loop: at each iteration it queries
the event demultiplexer to know which descriptors are ready, calculates a timeout
dynamic (`computePollTimeout`) based on the next idle connection to expire, dispatch them
ready events to the correct handler, then cleans up closed connections and expires connections
inactive (`expiresIdleConnections`). Each registered descriptor is associated with a
`IEventHandler` (`onReadable`, `onWritable`, `onTimeout`) — `TcpListenerHandler` for sockets
listener (accepts new connections) and `ConnectionHandler` for client connections
(reads/writes via `ITransport`, advances the application protocol `IProtocol`). The Reactor does not
only knows the `IEventHandler` interface: it is completely protocol agnostic (HTTP, CGI,
etc.) which rotates above.

**Demultiplexer chosen according to the platform.** The Reactor never speaks directly to
`epoll`/`kqueue`: it depends on the `IEventDemultiplexer` interface (`add`/`modify`/`remove`/`wait`

+ reading returned events). The concrete implementation is chosen **at compile time**
  via `reactor/demultiplexer/Demultiplexer.hpp`:

```cpp
#ifdef __linux__
typedef EpollDemultiplexer Demultiplexer;
#elif defined(__APPLE__)
typedef KqueueDemultiplexer Demultiplexer;
#endif
```

- **Linux** → `EpollDemultiplexer`, based on `epoll_wait`/`epoll_ctl` (event-driven,
  level-triggered).
- **macOS / BSD** → `KqueueDemultiplexer`, based on `kqueue`/`kevent`.

Both implementations respect the same contract (`IEventDemultiplexer`), which allows the
Reactor and everything else on the server to remain completely independent of the mechanism
of operating system inputs/outputs — only the typedef `Demultiplexer` changes depending on
of the platform, all the rest of the code is identical on Linux and macOS.

Other key points of this layer:

- All sockets are **non-blocking**, I/O is done in small blocks (`RECV_CHUNK` =
  16 KB), with an accumulated write buffer (`m_write_buf`) to handle partial writes.
- File descriptors are managed in RAII (`fd::Fd`), guaranteeing their closure even when
  exceptional cases.
- Inactive connections are expired after a configurable timeout
  (`IDLE_CONNECTION_TIMEOUT_S`), calculated without active polling thanks to the dynamic timeout of the
  `wait()`.
- The code respects the constraints of subject 42 (no thread, a single call of
  poll/epoll/kqueue by loop, `select`/`poll`/`epoll`/`kqueue` only via this module).

# Instructions

To launch the program, use the command line
`./webserv <configuration file>`

Configuration file ressemble the server block of the nginx file:

```
server {
	listen 8081;
	hostname 127.0.0.1;

	root /var/www/html/

	location / {
		index index.html index.htm;
	}

	location /testing/ {
		return 404;
	}

	location /uploads/ {
		root /var/www/html/uploads/;
		autoindex on;
	}

	location /cgi-bin/ {
		root /var/www/cgi-bin/;
		cgi test.py;
	}

	error_page 500 /500.html;
	error_page 404 /404.html;
}
```

Some differences exist between the two files such as no redefinition of values, for example, if you already defined an
index in a location block, you can't reuse the keyword `index` inside that block.
Also, every location and root has to be a directory, whereas index can't have any directory.

`server`: defines the start of a server setup

`hostname`: name of to identify the server, must be unique in configuration file

`root` (outside location block): path for the server, the location blocks without a root directive will append there
path to that route

`location`: starts of the location block for a specific path

`root` (in location block): use as an alias to replace the path of the location block (the one the user will enter but
end up internally where defined by the root directive)

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

[RFC on CGI](https://datatracker.ietf.org/doc/html/rfc3875)

[Code(quoi); article on network programmation](https://www.codequoi.com/programmation-reseau-via-socket-en-c/)

[Nginx server block](https://docs.nginx.com/nginx/admin-guide/web-server/web-server/)

[CGI](https://www.stat.berkeley.edu/~spector/s133/Cgi1a.html)

[Clean Architecture](https://blog.cleancoder.com/uncle-bob/2012/08/13/the-clean-architecture.html)

### Server resources

[Linux posix manual](https://pubs.opengroup.org/onlinepubs/9699919799/functions/contents.html)

Epoll/Kqueue : man pages

[Sockets/bind()/listen()/accept()...] (https://beej.us/guide/bgnet/pdf/bgnet_usl_c_1.pdf)

Connections timeout handling:

https://stackoverflow.com/questions/10772208/epoll-and-timeouts
https://groups.google.com/g/comp.unix.programmer/c/WqLDeCvBQEo?pli=1

CGI handling:

https://en.wikipedia.org/wiki/Common_Gateway_Interface #Section deployment