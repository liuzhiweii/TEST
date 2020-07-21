package.path = package.path..";/opt/www/cgi/?.lua;/opt/lib/?.lua;"
package.path = package.path.."/vagrant/SHC1808-GS50-C/app/www/cgi/?.lua;"

local string = require("string")
local json = require("dkjson")
local zmq = require("lzmq")
local miscFunc = require("misc_func")
local json = require"dkjson"

local ctx = zmq.context()
local sock = ctx:socket{zmq.REQ, linger=0, rcvtimo=1000,
                     connect="tcp://127.0.0.1:10012"}


if cgilua.servervariable("REQUEST_METHOD") == "GET" then
	cgilua.contentheader("application", "json")
	version = miscFunc.queryVersion(sock)
	cgilua.put(json.encode(version))
end

if cgilua.servervariable("REQUEST_METHOD") == "POST" then
	cgilua.contentheader("application", "json")
	if(cgilua.POST.action == "reboot") then
		miscFunc.rebootReader(sock)
	end
	result = {}
	result.result = "success"
	cgilua.put(json.encode(result))
end

sock:close()
ctx:destroy()
