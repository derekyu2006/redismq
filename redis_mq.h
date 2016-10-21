// CopyRight NewStone 2016
// Author: hoddis(hoddisyu@qq.com)
#ifndef REDISMQ_REDIS_MQ_H_
#define REDISMQ_REDIS_MQ_H_

#include <string>

#include "thirdparty/boost/shared_ptr.hpp"

#include "config.h"
#include "redis_conn_pool.h"
#include "reply.h"

namespace newstone { namespace redismq {
class RedisMq {
public:
  static RedisMq* GetInstance() {
    return &RedisMq::m_s_this_instance;
  }

  ~RedisMq();

public:
  void PushMsg(const std::string& msg);

  std::string PopMsg();

private:
  RedisMq();

  bool SelectDb(boost::shared_ptr<RedisWrapper>& conn);

private:
  static RedisMq      m_s_this_instance;
};
} // namespace redismq
} // namespace newstone
#endif // REDISMQ_REDIS_MQ_H_

