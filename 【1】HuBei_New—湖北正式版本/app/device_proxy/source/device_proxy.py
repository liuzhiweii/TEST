#!  /usr/bin/python

import zmq
import struct


class Enum(tuple):
    __getattr__ = tuple.index

device_type = Enum(["default", "FPGA", "EEPROM"])
fpga_action = Enum(["default", "INIT", "READ_REG", "WRITE_REG"])


class DeviceProxyException(Exception):

    def __init__(self, msg):
        self.msg = str(msg)

    def __str__(self):
        if self.msg:
            return self.msg


class DeviceProxy(object):

    def __init__(self):
        self.ctx = zmq.Context()
        self.req_socket = self.ctx.socket(zmq.REQ)
        self.req_socket.connect("tcp://127.0.0.1:5100")
        self.req_socket.setsockopt(zmq.LINGER, 0)

    def fpga_init(self):
        init_cmd = struct.pack("!II", device_type.FPGA, fpga_action.INIT)
        self.req_socket.send(init_cmd, zmq.NOBLOCK, copy=False)
        rep = self.req_socket.recv()
        status = struct.unpack("!I", rep)
        print status[0]
        return status[0]

    def fpga_read_reg(self, offset):
        read_cmd = struct.pack(
            "!IIH", device_type.FPGA, fpga_action.READ_REG, offset)
        self.req_socket.send(read_cmd, zmq.NOBLOCK, copy=False)
        rep = self.req_socket.recv()
        status, value = struct.unpack("!IH", rep)
        print status, value
        return (status, value)

    def fpga_write_reg(self, offset):
        pass

    def fpga_write_frame(self, frame):
        pass

    def fpga_read_frame(self):
        pass


class Eeprom(object):

    def write(offset, data):
        pass

    def read():
        pass


class TxPll(object):

    def config_value(high, low):
        pass

    def is_ready():
        return False

    def is_lock():
        return False


class RxPll(object):

    def config_value(high, value):
        pass

    def is_ready():
        return False

    def is_lcok():
        return False


class F_Dac(object):

    def set_f_dac_sleep(flag):
        pass

    def set_one_voltage(voltage):
        pass

    def set_zero_voltage(voltage):
        pass

    def set_carrier_voltage(voltage):
        pass


class MiscReg(object):

    def set_forward_filter(filter_type):
        ''' enable forward filter'''
        pass

    def adujst_forward_pa(value):
        pass

    def set_backward_decoder(decoder_type):
        pass

    def force_send(flag):
        pass

    def get_mac_frame_cnt():
        pass

    def get_7e_cnt():
        pass

    def send_pn9_rect():
        pass

    def select_pn8_rect():
        pass

    def get_ant_status():
        pass

    def get_fpga_nco():
        pass

    def fpga_pll_islock():
        pass

    def read_rssi():
        pass


class B_Adc(object):
    def is_ready():
        pass

    def select_clk():
        pass

    def trig_training():
        pass

    def config(vlaue):
        pass


class Datt(object):
    def set_attenuation():
        pass


class Shifter(object):
    def set_degree():
        pass

class Vga(object):
    def config():
        pass

class Detector(object):
    def read_temp():
        pass

    def read_vol():
        pass

proxy = DeviceProxy()
eeprom = Eeprom()
tx_pll = TxPll()
rx_pll = RxPll()
fdac = F_Dac()
misc_reg = MiscReg()
badc = B_Adc()
datt = Datt()
shifter = Shifter()
vga = Vga()
detector = Detector()

def calibrate_forward_power(power):
    for vol in range(100, 3001, 100):
        fdac.set_carrier_voltage(vol)
        misc_reg.force_send()
        detector.read_vol()

def send_single(power):
    pass






if __name__ == '__main__':
    proxy = DeviceProxy()
    proxy.fpga_init()
    proxy.fpga_read_reg(0x0001)

    # raw_input()
