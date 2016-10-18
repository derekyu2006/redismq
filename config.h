// CopyRight NewStone 2016
// Author: hoddis(yutao_2006@126.com)
#ifndef REDISMQ_CONFIG_H_
#define REDISMQ_CONFIG_H_

#include "thirdparty/gflags/gflags.h"

DECLARE_string(redis_server_ip);
DECLARE_int32(redis_server_port);
DECLARE_int32(redis_server_timeout);
DECLARE_int32(redis_retry_times);
DECLARE_int32(redis_db_no);
DECLARE_string(redis_mq_list);

#define FUNC_NAME "[" << __func__ << "] "

#endif

