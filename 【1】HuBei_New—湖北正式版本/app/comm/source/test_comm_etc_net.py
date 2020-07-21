import unittest
import zmq
import socket
from codec_cq import *

class TestCommEtcNetSuites(unittest.TestCase):
	def setUp(self):
		self.codec = EtcCodec()
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.sock.connect(("192.168.1.116",3009))
		self.sock.settimeout(1)
		self.context = zmq.Context()
		self.push_socket = self.context.socket(zmq.PUSH)
		self.push_socket.connect("tcp://192.168.1.116:5011")
		self.pull_socket = self.context.socket(zmq.PULL)
		self.pull_socket.connect("tcp://192.168.1.116:5010")

	def test_comm_send_func(self):
		self.push_socket.send("\xf1\x11\x22\x33\x44\x55\x66\x77\x88\x99\x00")
		recv_data = self.sock.recv(1024)
		print repc(recv_data)
		
	

	def test_comm_encode_func(self):
		source = "\xf1\x11\x22\x33\x44\x55\x66\x77\x88\x99\x00"
		self.push_socket.send(source)
		encoded = self.sock.recv(1024)
		print encoded
		decoded = self.codec.decode(encoded)
		print decoded
		
	def tearDown(self):
		pass

if __name__ == '__main__':
    unittest.main()


