package.path = package.path..";/opt/www/cgi/?.lua;/opt/lib/?.lua;"
package.path = package.path.."/vagrant/SHC1808-GS50-C/app/www/cgi/?.lua;"

local string = require("string")
local json = require("dkjson")
local zmq = require("lzmq")
local miscFunc = require("misc_func")
local json = require"dkjson"

local ctx = zmq.context()
local sock = ctx:socket{zmq.REQ, linger=0, rcvtimo=1000,
                     connect="tcp://192.168.2.200:6500"}


if cgilua.servervariable("REQUEST_METHOD") == "GET" then
	cgilua.contentheader("application", "json")
	tradestat = miscFunc.querySchedulerTradeStat(sock)
	cgilua.put(json.encode(tradestat))
end

if cgilua.servervariable("REQUEST_METHOD") == "POST" then
	cgilua.contentheader("application", "json")
	action = json.decode(cgilua.POST.action)
	result = {}
	result.result = "success"
	miscFunc.clearSchedulerTradeStat(sock)
	cgilua.put(json.encode(result))

end

sock:close()
ctx:destroy()


