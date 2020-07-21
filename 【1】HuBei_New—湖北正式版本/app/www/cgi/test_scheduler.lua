package.path = package.path..";/opt/www/cgi/?.lua;/opt/lib/?.lua;"


local string = require("string")
local json = require("dkjson")
local zmq = require("lzmq")
local miscFunc = require("misc_func")

ctx = zmq.context()
schedulerSock = ctx:socket{zmq.REQ, linger=0, rcvtimo=1000, connect="tcp://192.168.2.200:6500"}



--query config
ret = miscFunc.querySchedulerConfig(schedulerSock)
local str = json.encode (ret)
print(str)







schedulerSock:close()
ctx:destroy()

