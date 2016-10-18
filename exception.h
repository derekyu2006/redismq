// Copyright (c) 2014 Luca Marturana. All rights reserved.
// Licensed under Apache 2.0, see LICENSE for details
// CopyRight NewStone 2016
// Author: hoddis(yutao_2006@126.com)

#pragma once

#include <exception>
#include <string>

namespace newstone { namespace common {
class RedisException: public std::exception {
 public:
  RedisException(const std::string& what):
    _what(what){}
  virtual ~RedisException() throw() {}

  inline virtual const char* what() {
    return _what.c_str();
  }
 private:
  std::string _what;
};

} // namespace common
} // namespace newstone

#define REDIS_EXCEPTION(name) class name: public newstone::common::RedisException {\
 public: name(const std::string& what=""): RedisException(what){}};

#define REDIS_EXCEPTION_2(name, super) class name: public super {\
 public: name(const std::string& what=""): super(what){}};
