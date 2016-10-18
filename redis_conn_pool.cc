// CopyRigth NewStone 2016
// Author: Hoddis
#include "redis_conn_pool.h"

namespace newstone { namespace redismq {
boost::shared_ptr<RedisWrapper> RedisConnPool::NewClientPtr() {
  boost::shared_ptr<RedisWrapper> client_ptr =
    boost::shared_ptr<RedisWrapper>(new RedisWrapper(
      FLAGS_redis_server_ip, FLAGS_redis_server_port,
      FLAGS_redis_server_timeout, FLAGS_redis_retry_times));
  return client_ptr;
}
} // namespace redismq
} // namespace newstone
