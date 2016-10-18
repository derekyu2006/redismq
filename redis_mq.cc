// CopyRight NewStone 2016
// Author: hoddis(yutao_2006@126.com)
#include "redis_mq.h"

namespace newstone { namespace redismq {
RedisMq RedisMq::m_s_this_instance;
RedisMq::RedisMq() {
}

RedisMq::~RedisMq() {
}

bool RedisMq::SelectDb(boost::shared_ptr<RedisWrapper>& conn) {
  std::stringstream ss;
  ss << "select " << FLAGS_redis_db_no;
  const std::string cmd = ss.str();

  MyRedisReply reply;
  bool ret = conn->Command(cmd, &reply);
  if (!ret) {
    LOG(ERROR) << FUNC_NAME << "execute cmd[" << cmd << "] fail.";
    return false;
  }

  LOG(INFO) << FUNC_NAME << "replytype: " << reply.type() << ", replystr: "
    << reply.str().c_str();
  if (reply.type() != STATUS || strcasecmp(reply.str().c_str(), "OK") != 0) {
    LOG(ERROR) << FUNC_NAME << "execute cmd[" << cmd << "] success, "
      << "but res fail with restype: " << reply.type() << ", resstr:"
      << reply.str();
    return false;
  }

  return true;
}

void RedisMq::PushMsg(const std::string& msg) {
  std::stringstream ss;
  bool              ret = false;

  // 0@ get redis conn from client pool
  boost::shared_ptr<RedisWrapper> redis_conn =
    RedisConnPool::Instance()->GetClientPtr();

  // 1@ select db for caching msg
  ret = SelectDb(redis_conn);
  if (!ret) {
    RedisConnPool::Instance()->FreeClientPtr(redis_conn, false);
    return;
  }

  // 2@ build redis command
  ss << "RPUSH " << FLAGS_redis_mq_list << " " << msg;
  const std::string cmd = ss.str();

  // 3@ send redis cmd
  MyRedisReply reply;
  ret = redis_conn->Command(cmd, &reply);
  if (!ret || reply.type() != INTEGER || reply.integer() != 1) {
    RedisConnPool::Instance()->FreeClientPtr(redis_conn, false);

    LOG(ERROR) << FUNC_NAME << "execute cmd[" << cmd << "] fail.";
    return;
  }

  // 4@ releas redis conn
  RedisConnPool::Instance()->FreeClientPtr(redis_conn, true);
}

std::string RedisMq::PopMsg() {
  std::stringstream ss;
  bool              ret = false;

  // 0@ get redis conn from client pool
  boost::shared_ptr<RedisWrapper> redis_conn =
    RedisConnPool::Instance()->GetClientPtr();

  // 1@ select db for caching msg
  ret = SelectDb(redis_conn);
  if (!ret) {
    RedisConnPool::Instance()->FreeClientPtr(redis_conn, false);
    return "";
  }

  // 2@ build redis command
  ss << "BLPOP " << FLAGS_redis_mq_list << " 0";
  const std::string cmd = ss.str();

  // 3@ get redis cmd
  MyRedisReply reply;
  ret = redis_conn->Command(cmd, &reply);
  if (!ret || reply.type() != ARRAY) {
    RedisConnPool::Instance()->FreeClientPtr(redis_conn, false);

    LOG(ERROR) << FUNC_NAME << "execute cmd[" << cmd << "] fail.";
    return "";
  }

  const std::vector<MyRedisReply>& messages = reply.elements();
  std::string message = messages[1].str();

  // 4@ releas redis conn
  RedisConnPool::Instance()->FreeClientPtr(redis_conn, true);

  return message;
}


} // redismq
} // newstone

