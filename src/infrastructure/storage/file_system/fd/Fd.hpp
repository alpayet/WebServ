#ifndef FD_HPP
#define FD_HPP

namespace webserv {
namespace fd {

class Fd {
public:
  Fd();
  explicit Fd(int fd);
  ~Fd();

  int get() const;
  bool valid() const;

  int release();

  void reset(int fd = -1);

  bool setNonBlocking() const;

private:
  Fd(const Fd &);
  Fd &operator=(const Fd &);

  int m_fd;
};

} // namespace fd
} // namespace webserv

#endif
