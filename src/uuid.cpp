#include "uuid/uuid.h"

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

std::string Zero::randomUUID() {
  Zero::UUID uuid = boost::uuids::random_generator()();
  return boost::uuids::to_string(uuid);
}