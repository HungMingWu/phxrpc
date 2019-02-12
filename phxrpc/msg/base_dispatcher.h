/*
Tencent is pleased to support the open source community by making
PhxRPC available.
Copyright (C) 2016 THL A29 Limited, a Tencent company.
All rights reserved.

Licensed under the BSD 3-Clause License (the "License"); you may
not use this file except in compliance with the License. You may
obtain a copy of the License at

https://opensource.org/licenses/BSD-3-Clause

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
implied. See the License for the specific language governing
permissions and limitations under the License.

See the AUTHORS file for names of contributors.
*/

#pragma once

#include <map>
#include <string>

#include "phxrpc/msg/base_msg.h"


namespace phxrpc {


class BaseDispatcher {
  public:
    typedef std::function<int(const BaseRequest &req, BaseResponse *const resp)> URIFunc_t;

    typedef std::map<std::string, URIFunc_t> URIFuncMap;

    BaseDispatcher(const URIFuncMap &uri_func_map)
            : uri_func_map_(uri_func_map) {
    }

    virtual ~BaseDispatcher() = default;

    bool Dispatch(const BaseRequest &req, BaseResponse *const resp) {
        int ret{-1};
        auto iter = uri_func_map_.find(req.uri());

        if (uri_func_map_.end() != iter) {
            ret = (iter->second)(req, resp);
        }

        resp->set_result(ret);

        return uri_func_map_.end() != iter;
    }

  private:
    const URIFuncMap &uri_func_map_;
};


}  // namespace phxrpc

