package.path = package.path..";/opt/lib/?.lua;/opt/www/cgi/?.lua;"
require "pack"
require "scheduler_pb"
require "string"

local _M = {}
function _M.readFpgaReg(sock, reg_addr)
    cmd = string.pack(">III", 1, 2, reg_addr+0x80000)
    sock:send(cmd)
    ack = sock:recv()
    index, status, value = string.unpack(ack, ">IH")
    if(status == 0) then
        return value
    else
        return nil
    end
end

function _M.writeFpgaReg(sock, addr, data)
    cmd = string.pack(">IIIH", 1, 3,  addr + 0x80000, data)
    sock:send(cmd)
    ack = sock:recv()
    index, status = string.unpack(ack, ">I")
    if (status == 0) then
        return true
    else
        return false
    end
end


function _M.queryVersion(sock)
	local result = {}
	msg = string.pack(">II", 2, 0)
	sock:send(msg)
	ack = sock:recv()
              if not ack then
                return nil
              end
	index, id, ret = string.unpack(string.sub(ack, 1, 8), ">II")
	if (ret ~= 0) then
	    return nil
	end
	index, sysRuning, switchStatus = string.unpack(string.sub(ack, 9, 16), ">II")
	index, appVersion0, appVersion1, appVersion2 = string.unpack(string.sub(ack, 17, 20), ">b4")
	index, appDownloadVersion0, appDownloadVersion1, appDownloadVersion2 = string.unpack(string.sub(ack, 21, 24), ">b4")
	index, sys0Version0, sys0Version1, sys0Version2 = string.unpack(string.sub(ack, 25, 28), ">b4")
	index, sys1Version0, sys1Version1, sys1Version2 = string.unpack(string.sub(ack, 29, 32), ">b4")
	result.sysRuning = sysRuning
	result.switchStatus = switchStatus
	result.appVersion = string.format("V%d.%02d.%02d", appVersion0, appVersion1, appVersion2)
	result.appDownloadVersion = string.format("V%d.%02d.%02d", appDownloadVersion0, appDownloadVersion1, appDownloadVersion2)
	result.sysVersion0 = string.format("V%d.%02d.%02d", sys0Version0, sys0Version1, sys0Version2)
	result.sysVersion1 = string.format("V%d.%02d.%02d", sys1Version0, sys1Version1, sys1Version2)
	return result
end

function _M.rebootReader(sock)
	local result = {}
	msg = string.pack(">II", 100, 0)
	sock:send(msg)
	ack = sock:recv()
	return
end

function _M.querySchedulerConfig(sock)
    local result = {}
    local msg = scheduler_pb.sched_request()
    msg.type = scheduler_pb.sched_request.queryConfig
    local msg_data = msg:SerializeToString()
    sock:send(msg_data)
    ack = sock:recv()
    if not ack then
        return nil
    end
    msg = scheduler_pb.sched_response()
    msg:ParseFromString(ack)
	result.baseconfig = {}
	result.psamconfig = {}
	result.rfconfig = {}
	result.baseconfig.routeinfo = string.format("%04x", msg.content.baseConfig.route)
	result.baseconfig.sleeptime = msg.content.baseConfig.sleeptime
	result.baseconfig.beaconid = string.format("%08x", msg.content.baseConfig.beaconId)
	result.baseconfig.parallel_trade = msg.content.baseConfig.parallelTrade

	for k,v in pairs(msg.content.psamconfig) do
		if (type(k) == "number") then
			local psam = {}  
			psam.psamid = v.psamid
			psam.enable = v.enable
			psam.type = v.type
			psam.addr = v.addr			
			result.psamconfig[k] = psam
        end
	end
	
	for k,v in pairs(msg.content.rfconfig) do
		if (type(k) == "number") then
            result.rfconfig[k] ={}
			result.rfconfig[k].rfsn = v.rfsn
			result.rfconfig[k].enable = v.enable
			result.rfconfig[k].power = v.power
			result.rfconfig[k].addr = v.addr
        end
	end
	
    return result
end

function _M.setSchedulerRuningMode(sock, mode)
    local msg = scheduler_pb.sched_request()
    msg.type = scheduler_pb.sched_request.setRuningMode
    msg.runingmode = mode
    local msg_data = msg:SerializeToString()
    sock:send(msg_data)
    ack = sock:recv()
    if not ack then
        return nil
    end
    msg = scheduler_pb.sched_response()
    msg:ParseFromString(ack)
    return msg.currentRuningMode
end

function _M.querySchedulerTradeStat(sock)
    local msg = scheduler_pb.sched_request()
    msg.type = scheduler_pb.sched_request.queryTradeStat
    local msg_data = msg:SerializeToString()
    sock:send(msg_data)
    ack = sock:recv()
    if not ack then
        return nil
    end
    msg = scheduler_pb.sched_response()
    msg:ParseFromString(ack)
    tradestat = {}
    tradestat.runTime = msg.tradeStat.runTime
    tradestat.tradeNum = msg.tradeStat.tradeNum
    tradestat.successNum = msg.tradeStat.successNum
    tradestat.failNum = msg.tradeStat.failNum
    tradestat.timeoutNum = msg.tradeStat.timeoutNum
    tradestat.minTradeTime = msg.tradeStat.minTradeTime
    tradestat.maxTradeTime = msg.tradeStat.maxTradeTime
    tradestat.avgTradeTime = msg.tradeStat.avgTradeTime
    tradestat.successMacs = {}
    for k,v in pairs(msg.tradeStat.successMacs) do
        if(type(k) == "number") then
            tradestat.successMacs[k] = v
        end
    end
    tradestat.failMacs = {}
    for k,v in pairs(msg.tradeStat.failMacs) do
        if(type(k) == "number") then
            tradestat.failMacs[k] = v
        end
    end
    tradestat.timeoutMacs = {}
    for k,v in pairs(msg.tradeStat.timeoutMacs) do
        if(type(k) == "number") then
            tradestat.timeoutMacs[k] = v
        end
    end
    return tradestat
end

function _M.changeSchedulerConfig(sock, config)
	print("changeSchedulerConfigchangeSchedulerConfig")
    local msg = scheduler_pb.sched_request()
    msg.type = scheduler_pb.sched_request.changeConfigByJson
	msg.jsonString = config
    local msg_data = msg:SerializeToString()
	print(string.len(msg_data))
    sock:send(msg_data)
    ack = sock:recv()
    if not ack then
        return nil
    end
	print(string.len(ack))


	
	
    return
end

function _M.querySchedulerRunningMode( sock )
    local msg = scheduler_pb.sched_request()
    msg.type = scheduler_pb.sched_request.queryRuningMode
    local msg_data = msg:SerializeToString()
    sock:send(msg_data)
    ack = sock:recv()
    if not ack then
        return "nil"
    end
    msg = scheduler_pb.sched_response()
    msg:ParseFromString(ack)
    return msg.currentRuningMode
end

function _M.clearSchedulerTradeStat( sock )
    local msg = scheduler_pb.sched_request()
    msg.type = scheduler_pb.sched_request.clearTradeStat
    local msg_data = msg:SerializeToString()
    sock:send(msg_data)
    ack = sock:recv()
    if not ack then
        return nil
    end
    msg = scheduler_pb.sched_response()
    return true
end

return _M
