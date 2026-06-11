#ifndef ITRANSFER_HPP
#define ITRANSFER_HPP

class ITransfer {
 public:
  virtual ~ITransfer() {}

  virtual void init() = 0;
};

#endif  // ITRANSFER_HPP
