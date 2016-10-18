// CopyRight NewStone 2016
// Author: hoddis(yutao_2006@126.com)
#ifndef REDISMQ_WRAPPER_H_
#define REDISMQ_WRAPPER_H

#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <hiredis/hiredis.h>
#include <map>
#include <string>
#include <vector>

#include "redismq/exception.h"
#include "redismq/reply.h"

namespace newstone { namespace redismq {
REDIS_EXCEPTION(connection_error)
REDIS_EXCEPTION_2(unable_to_connect, connection_error)
REDIS_EXCEPTION_2(transport_failure, connection_error)
REDIS_EXCEPTION_2(slave_read_only, connection_error)

class RedisWrapper : private boost::noncopyable {
public:
  RedisWrapper(const std::string& server_ip, const int32_t server_port,
    const int32_t timeout, const int32_t retry_times);

  ~RedisWrapper();

  bool Command(const std::string& command, MyRedisReply *reply);

private:
  bool InitClient();
  bool ExecuteCommand(const std::string& command, MyRedisReply *reply);
  void Append(const std::vector<std::string> &commands);
  void Get_reply(MyRedisReply *reply);

private:
  const std::string   m_server_ip;
  const int32_t       m_server_port;
  int32_t             m_server_dbno;
  const int32_t       m_timeout;
  const int32_t       m_redis_retry_times;
  redisContext*       m_conn;
  bool                m_is_inited;
};

} // namespace redismq
} // namespace newstone
#endif // REDISMQ_REDIS_WRAPPER_H_

