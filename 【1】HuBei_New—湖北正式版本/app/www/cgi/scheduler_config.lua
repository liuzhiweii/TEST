package.path = package.path..";/opt/www/cgi/?.lua;/opt/lib/?.lua;"
package.path = package.path.."/vagrant/SHC1808-GS50-C/app/www/cgi/?.lua;"

local string = require("string")
local miscFunc = require("misc_func")
local json = require"dkjson"
local io = require"io"


if cgilua.servervariable("REQUEST_METHOD") == "GET" then
	cgilua.contentheader("application", "json")
	f = io.open("/opt/bin/scheduler.json", "r")
	if f then
	    config = f:read("*a")
	    io.close()
	end
	cgilua.put(config)
end

if cgilua.servervariable("REQUEST_METHOD") == "POST" then
	cgilua.contentheader("application", "json")
	config = {}
	config.baseconfig = cgilua.POST.baseconfig
	config.psamconfig = cgilua.POST.psamconfig
	config.rfconfig = cgilua.POST.rfconfig
	config.extendconfig = cgilua.POST.extendconfig
	configstr = json.encode(config)
	f = io.open("/opt/bin/scheduler.json", "w")
	if f then
	    f:write(configstr)
		io.close(f)
	end
	result = {}
	result.result = "success"
	cgilua.put(json.encode(result))

end



