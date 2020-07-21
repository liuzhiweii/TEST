package.path = package.path..";/opt/www/cgi/?.lua;/opt/lib/?.lua;"


local string = require("string")
local json = require("dkjson")
local zmq = require("lzmq")
local miscFunc = require("misc_func")

ctx = zmq.context()
versionSock = ctx:socket{zmq.REQ, linger=0, rcvtimo=1000, connect="tcp://192.168.2.200:6500"}

configstr = [[{"baseconfig":{"beaconid":"a60000a0","parallel_trade":2,"routeinfo":"0404","sleeptime":1},"psamconfig":[{"addr":"192.168.2.200","enable":true,"psamid":1,"type":1},{"addr":"192.168.2.200","enable":true,"psamid":2,"type":1},{"addr":"192.168.2.200","enable":false,"psamid":3,"type":1},{"addr":"192.168.2.200","enable":false,"psamid":4,"type":1}],"rfconfig":[{"addr":"192.168.2.201","enable":true,"power":25,"rfsn":1},{"addr":"192.168.2.202","enable":false,"power":26,"rfsn":2},{"addr":"192.168.2.203","enable":false,"power":27,"rfsn":3},{"addr":"192.168.2.204","enable":false,"power":28,"rfsn":4}]}]]
config = json.decode(configstr)
print(config)
ret = miscFunc.changeSchedulerConfig(versionSock, config)

versionSock:close()
ctx:destroy()

