
local zmq = require("lzmq")

ctx = zmq.context()

pull_socket, err = ctx:socket{zmq.PULL, bind="tcp://*:5555"}
print(pull_socket)
print(err)

buffer = pull_socket:recv()
print(buffer)
print(buffer[0])




