// CopyRight NewStone 2016
// Author: hoddis(yutao_2006@126.com)
#include "reply.h"

namespace newstone { namespace redismq {
MyRedisReply::MyRedisReply() : _type(reply_type_t::ERROR), _integer(0) {
}

MyRedisReply::~MyRedisReply() {
}

MyRedisReply::MyRedisReply(redisReply *c_reply) : _type(reply_type_t::ERROR), _integer(0) {
  CHECK_NOTNULL(c_reply);
  _type = static_cast<reply_type_t>(c_reply->type);
  switch (_type) {
    case reply_type_t::ERROR:
    case reply_type_t::STRING:
    case reply_type_t::STATUS:
      _str = std::string(c_reply->str, c_reply->len);
      break;
    case reply_type_t::INTEGER:
      _integer = c_reply->integer;
      break;
    case reply_type_t::ARRAY:
      for (size_t i=0; i < c_reply->elements; ++i) {
        _elements.push_back(MyRedisReply(c_reply->element[i]));
      }
      break;
    default:
      break;
  }
}

MyRedisReply& MyRedisReply::operator=(const redisReply *c_reply) {
  CHECK_NOTNULL(c_reply);
  _type = static_cast<reply_type_t>(c_reply->type);
  switch (_type) {
    case reply_type_t::ERROR:
    case reply_type_t::STRING:
    case reply_type_t::STATUS:
      _str = std::string(c_reply->str, c_reply->len);
      break;
    case reply_type_t::INTEGER:
      _integer = c_reply->integer;
      break;
    case reply_type_t::ARRAY:
      for (size_t i=0; i < c_reply->elements; ++i) {
        _elements.push_back(MyRedisReply(c_reply->element[i]));
      }
      break;
    default:
      break;
  }
  return *this;
}
} // namespace common
} // namespace newstone
