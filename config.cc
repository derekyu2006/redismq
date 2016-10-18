// CopyRight NewStone 2016
// Author: hoddis(yutao_2006@126.com)
#include "redismq/config.h"

DEFINE_string(redis_server_ip, "", "redissvr ip");
DEFINE_int32(redis_server_port, 0, "redissvr port");
DEFINE_int32(redis_server_timeout, 0, "redissvr conn timeout");
DEFINE_int32(redis_retry_times, 0, "redissvr retry times");
DEFINE_int32(redis_db_no, 0, "redis data number");
DEFINE_string(redis_mq_list, "", "redis list for mq");

