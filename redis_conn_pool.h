// CopyRight NewStone 2016
// Author: hoddis(hoddisyu@qq.com)
#ifndef REDISMQ_REDIS_CONN_POOL_H
#define REDISMQ_REDIS_CONN_POOL_H

#include <string>

#include "config.h"
#include "redis_wrapper.h"
#include "common/clientpool/client_template.h"

namespace newstone { namespace redismq {
using newstone::common::ClientPool;
// TransactionLogger 对象类名
// LoggerPool 对象池名
// true 启动定时刷新对象状态
// 没重写RefreshClient 默认在五分钟内没有任何的访问
// 删除连接对象,避免连接对象只增不减
class RedisConnPool : public ClientPool<RedisWrapper, RedisConnPool, true> {
public:
  // 重写虚函数 生成你自己的对象
  virtual boost::shared_ptr<RedisWrapper>  NewClientPtr();

protected:
  // 重写自身的标识函数
  virtual std::string ClientStr() {
    return "RedisConnPool";
  }
};

typedef boost::shared_ptr<RedisWrapper> RedisConnPtr;

} // namespace common
} // namespace newstone
#endif // REDISMQ_REDIS_CONN_POOL_H

