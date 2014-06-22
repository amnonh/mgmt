/*
 * Copyright (C) 2014 Cloudius Systems, Ltd.
 *
 * This work is open source software, licensed under the terms of the
 * BSD license as described in the LICENSE file in the top-level directory.
 */
#include "network.hh"
#include "autogen/network.json.hh"
#include "osv/network_interface.hh"
#include "exception.hh"
namespace httpserver {

namespace api {

namespace network {
using namespace json;
using namespace std;
using namespace osv::network;

/**
 * Initialize the routes object with specific routes mapping
 * @param routes - the routes object to fill
 */
void init(routes& routes)
{
    network_json_init_path();
    network_json::getIfconfig.set_handler([](const_req req) {
        interface intf(req.param.at("if").substr(1));
        Interface f;
        f.set(intf);
        return formatter::to_json(f);
    });
}

}
}
}
