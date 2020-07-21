
import socket
from struct import *
import time


class TimerProxy(object):
	'''
	struct set_timer_t
	{
		unsigned int action;  //1:set 0: del
		unsigned int flag;    //1: persist, 0:one short
		unsigned int timer_id;
		unsigned int secs;
		unsigned int u_secs;	
	};
	'''
	def __init__(self):
		self.port = 9876

	def open(self):
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.sock.connect(("127.0.0.1", self.port))
		return self.sock

	def close(self):
		self.sock.close()

	def set_timer(self, timer_id, ms, flag):
		send_msg = pack("IIIII", 1, flag, timer_id, 0, ms*1000) 
		self.sock.send(send_msg)
		
	def del_timer(self, timer_id):
		send_msg = pack("IIII", 0, 0, timer_id, 0) 
		self.sock.send(send_msg)


if __name__ == '__main__':
	my_timer = TimerProxy()
	s = my_timer.open()
	my_timer.set_timer(1, 1, 0)
	id = s.recv(100)
	print "timer_id is ", ord(id[0])
	my_timer.set_timer(2, 500, 1) 
	for i in range(10):
		id = s.recv(100)
		print "timer id is ", ord(id[0])
	time.sleep(2)
	my_timer.del_timer(2)
	time.sleep(2)
	start = time.time()
	my_timer.set_timer(1, 1, 0)
	id = s.recv(100)
	end = time.time()
	print start, end
	s.close()



