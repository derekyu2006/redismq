cc_library(
  name = 'lib_rediswrapperpool',
  srcs = [
    'redis_conn_pool.cc',
    'redis_mq.cc',
    'redis_wrapper.cc',
    'reply.cc',
    'config.cc',
  ],
  deps = [
    '//common/time_cost:time_cost',
    '//thirdparty/gflags:gflags',
    '//thirdparty/glog:glog',
    '//thirdparty/hiredis:hiredis',
    '//thirdparty/boost:boost_filesystem',
    '//thirdparty/boost:boost_system',
    '//thirdparty/boost:boost_thread',
    '#pthread',
    '#rt',
  ],

  warning = 'no'
)

cc_binary(
  name = 'redismq',
  srcs = 'main.cc',
  deps = [
    ':lib_rediswrapperpool',
  ],

  warning = 'no'
)
