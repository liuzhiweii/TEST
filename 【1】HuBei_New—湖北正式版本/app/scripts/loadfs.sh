#! /bin/sh

/opt/bin/recovery_flash
cd /dev
ubi_ctrl_main_num=`cat /sys/devices/virtual/misc/ubi_ctrl/dev | cut -d: -f 1`
ubi_ctrl_min_num=`cat /sys/devices/virtual/misc/ubi_ctrl/dev | cut -d: -f 2`
mknod /dev/ubi_ctrl c $ubi_ctrl_main_num $ubi_ctrl_min_num
ubiattach /dev/ubi_ctrl -m 10
main_num=`cat /sys/class/ubi/ubi0/dev | cut -d: -f 1`
min_num=`cat /sys/class/ubi/ubi0/dev | cut -d: -f 2`
mknod /dev/ubi0 c $main_num $min_num

if [ -s "/sys/class/ubi/ubi0_0/dev" ]
then
    echo "ubi0 volme exist"
else
    ubimkvol /dev/ubi0 -N data -s 26MiB
fi

main_num=`cat /sys/class/ubi/ubi0_0/dev | cut -d: -f 1`
min_num=`cat /sys/class/ubi/ubi0_0/dev | cut -d: -f 2`

mknod /dev/ubi0_0 c $main_num $min_num
mount -t ubifs /dev/ubi0_0 /data

cd /opt/bin
