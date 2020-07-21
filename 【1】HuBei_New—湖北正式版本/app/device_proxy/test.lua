#! /usr/local/bin/luajit

print("test load dynamic library")

local ffi = require("ffi")

ffi.cdef[[
unsigned int bsp_fpga_init(void);
]]

bsp = ffi.load("bsp")

ret = bsp.bsp_fpga_init()
print(ret)

ret = bsp_fpga_read_reg()
