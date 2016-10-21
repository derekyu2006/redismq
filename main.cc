// CopyRight NewStone 2016
// Author: hoddis(hoddisyu@qq.com)
#include <iostream>
#include <string>

#include "thirdparty/gflags/gflags.h"

#include "redis_mq.h"

using newstone::redismq::RedisMq;

int main(int argc, char** args) {
  // init flags redis info
  FLAGS_redis_server_ip = "127.0.0.1";
  FLAGS_redis_server_port = 6379;
  FLAGS_redis_server_timeout = 10;
  FLAGS_redis_retry_times = 3;
  FLAGS_redis_db_no = 0;
  FLAGS_redis_mq_list = "redismq";

  // push data
  const std::string msg = "helloworld";
  // RedisMq::GetInstance()->PushMsg(msg);

  std::string popmsg = RedisMq::GetInstance()->PopMsg();
  std::cout << popmsg << std::endl;

  return 0;
}
