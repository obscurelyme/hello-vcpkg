#ifndef ZERO_UUID_H_
#define ZERO_UUID_H_

#include <string>

namespace boost {
  namespace uuids {
    class uuid;
  }
}  // namespace boost

namespace Zero {
  using UUID = boost::uuids::uuid;

  // Returns a random uuid string
  std::string randomUUID();
}  // namespace Zero

#endif