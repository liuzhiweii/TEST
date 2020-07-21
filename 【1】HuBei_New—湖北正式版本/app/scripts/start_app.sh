#! /bin/sh

insmod /opt/drv/drv_epld.ko 
/opt/bin/load_fpga /opt/rbf/RSDB0_FPGA.rbf 
insmod /opt/drv/drv_fpga.ko
insmod /opt/drv/drv_parallel_psam.ko
insmod /opt/drv/drv_timer.ko
insmod /opt/drv/drv_key.ko

syslogd -O "/opt/log.txt"
ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
#lighttpd -f /opt/www/lighttpd.conf
mkdir -p /data
/opt/bin/loadfs.sh
/opt/bin/utimer &
/opt/bin/cmm &
/opt/bin/cfg &
/opt/bin/comm_multipath &
stty -F /dev/ttyS1 speed 115200 -icanon -echo -icrnl -ixon -isig -onlcr
/opt/bin/comm_multipath_uart &
#/opt/bin/comm_client &
/opt/bin/psamserver &
/opt/bin/device_proxy &
/opt/bin/scheduler &
/opt/bin/systime_update &
/opt/bin/instep &
/opt/bin/webmast &


echo "start success"

