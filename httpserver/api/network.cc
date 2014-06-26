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
        string name = req.param.at("if").substr(1);
        interface intf(name);
        Interface f;
        f.set(intf);
        if_data cur_data = { 0 };
        ifnet* ifp = nullptr;
        cout << " number of interfaces " << number_of_interfaces() << endl;
        ifp = get_interface_by_name(name);
        if (ifp == nullptr) {
            throw not_found_exception(string("Interface ") + name + " not found");
        }
        if (!set_interface_info(ifp, cur_data)) {
            throw bad_request_exception("Failed getting interface information");
        }
        cout << cur_data.ifi_type << endl;
        return formatter::to_json(f);
    });
}

}
}
}
