#! /usr/bin/python

import zmq

c = zmq.Context()

front_end = c.socket(zmq.XREP)
front_end.bind("tcp://192.168.1.230:6090")

back_end = c.socket(zmq.XREQ)
back_end.connect("tcp://10.86.20.220:6060")

d = zmq.device(zmq.QUEUE, front_end, back_end)

front_end.close()
back_end.close()

c.term()
