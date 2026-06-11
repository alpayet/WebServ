#ifndef FAKETRANSFER_HPP
#define FAKETRANSFER_HPP

#include "ITransfer.hpp"

class FakeTransfer : public ITransfer {
 public:
  explicit FakeTransfer(char* s);
  ~FakeTransfer();

  void init();

 private:
  FakeTransfer();
  FakeTransfer(const FakeTransfer&);
  FakeTransfer& operator=(const FakeTransfer&);

  char* m_buf;
};

#endif  // FAKETRANSFERT_HPP
