// CopyRight NewStone 2016
// Author: hoddis(hoddisyu@qq.com)
#include <time.h>

#include "redismq/redis_wrapper.h"
#include "redismq/reply.h"

#include "thirdparty/gflags/gflags.h"
#include "thirdparty/glog/logging.h"

namespace newstone { namespace redismq {
RedisWrapper::RedisWrapper(const std::string& server_ip,
    const int32_t server_port, const int32_t timeout,
    const int32_t retry_times) : m_server_ip(server_ip),
    m_server_port(server_port), m_timeout(timeout),
    m_redis_retry_times(retry_times) {
  m_is_inited = false;
  InitClient();
}

RedisWrapper::~RedisWrapper() {
  redisFree(m_conn);
  m_conn = NULL;
}

bool RedisWrapper::InitClient() {
  if (m_is_inited) {
    return true;
  }
  // conn redis
  struct timeval conn_tv;
  conn_tv.tv_sec = m_timeout / 1000000;
  conn_tv.tv_usec = m_timeout % 1000000;
  m_conn = redisConnectWithTimeout(m_server_ip.c_str(), m_server_port,
    conn_tv);
  if (m_conn == NULL || m_conn->err) {
    if (m_conn) {
      LOG(ERROR) << "redis connection error:" << m_conn->errstr << ", conn: "
        << m_server_ip << ":" << m_server_port;
      redisFree(m_conn);
      m_conn = NULL;
    } else {
      LOG(ERROR) << "redis connection error:can't allocate redis context";
    }
    return false;
  }

  m_is_inited = true;
  LOG(INFO) << "Connection Redis Inited, ip: " << m_server_ip
    << " port: " << m_server_port << " db: " << m_server_dbno;
  return true;
}

bool RedisWrapper::Command(const std::string& command,
  MyRedisReply *reply) {
  if (command.empty()) {
    LOG(ERROR) << "RedisWrapper::Command receive empty command";
    return false;
  }
  int32_t  retry_time = m_redis_retry_times;
  while (retry_time--) {
    if (!InitClient()) {
      continue;
    }
    try {
      return ExecuteCommand(command, reply);
    } catch (...) {
      // 超时等网络异常
      LOG(ERROR) << "RedisWrapper::ExecuteCommand exception. commands:"
        << command;
      m_is_inited = false;
      continue;
    }
  }
  return false;
}

// return false:indict a bad connection get a NULL reply
bool RedisWrapper::ExecuteCommand(const std::string& command,
    MyRedisReply *reply) {
  void *redis_ret_ptr = redisCommand(m_conn, command.c_str());
  if (NULL == redis_ret_ptr) {
    LOG(WARNING) << "redisCommand return null";
    return false;
  }
  redisReply *r = reinterpret_cast<redisReply*>(redis_ret_ptr);
  *reply = r;
  freeReplyObject(r);

  if (reply->type() == reply_type_t::ERROR &&
    (reply->str().find("READONLY") == 0)) {
    throw slave_read_only();
  }
  return true;
}
} // namespace redismq
} // namespace newstone

