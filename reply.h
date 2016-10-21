// CopyRight NewStone 2016
// Author: hoddis(hoddisyu@qq.com)
#ifndef REDISMQ_REPLY_H_
#define REDISMQ_REPLY_H_

#include <string>
#include <vector>

#include "thirdparty/hiredis/hiredis.h"
#include "thirdparty/glog/logging.h"

struct redisReply;

namespace newstone { namespace redismq {

/**
 * @brief Define reply type
 */
enum reply_type_t {
  STRING = 1,
  ARRAY = 2,
  INTEGER = 3,
  NIL = 4,
  STATUS = 5,
  ERROR = 6
};
/**
 * @brief Represent a reply received from redis server
 */
class MyRedisReply {
 public:
  MyRedisReply();
  ~MyRedisReply();
  MyRedisReply(redisReply *reply);
  /**
   * @brief Type of reply, other field values are dependent of this
   * @return
   */
  inline reply_type_t type() const { return _type; }
  /**
   * @brief Returns string value if present, otherwise an empty string
   * @return
   */
  inline const std::string& str() const { return _str; }
  /**
   * @brief Returns integer value if present, otherwise 0
   * @return
   */
  inline long long integer() const { return _integer; }
  /**
   * @brief Returns a vector of sub-replies if present, otherwise an empty one
   * @return
   */
  inline const std::vector<MyRedisReply>& elements() const { return _elements; }

  inline operator const std::string&() const { return _str; }

  inline operator long long() const { return _integer; }

  inline bool operator==(const std::string& rvalue) const {
    if (_type == reply_type_t::STRING || _type == reply_type_t::ERROR || _type == reply_type_t::STATUS) {
      return _str == rvalue;
    }
    else {
      return false;
    }
  }

  inline bool operator==(const long long rvalue) const {
    if (_type == reply_type_t::INTEGER) {
      return _integer == rvalue;
    }
    else {
      return false;
    }
  }

  inline std::string GetReplyStr() const {
    return _str;
  }
  // 重载赋值，MyRedisReply=redisReply
  MyRedisReply& operator=(const redisReply *rreply);

  reply_type_t _type;
  std::string _str;
  long long _integer;
  std::vector<MyRedisReply> _elements;
};


} // namespace redismq
} // namespace newstone

#endif // REDISMQ_REPLY_H_
