setenv loglevel "10"
setenv rootdev "/dev/mmcblk2"
setenv datadev "/dev/mmcblk2p4"
setenv initrd_addr_r "0x41080000"
setenv load_addr "0x44000000"
setenv overlay_error "false"
setenv device "1:2"
setenv fdt_prefix "boot/allwinner/"
setenv prefix "boot/"
setenv fdtfile "sun8i-h3-emlid-neutis-n5h3-reach-rs2.dtb"

setenv rootdev "${rootdev}p2"

if test -e mmc ${device} ${prefix}Env.txt; then
    load mmc ${device} ${load_addr} ${prefix}Env.txt
    env import -t ${load_addr} ${filesize}
fi

setenv bootargs "console=${console} earlyprintk data=${datadev} root=${rootdev} rw rootwait fsck.root=yes fsck.data=yes panic=10 loglevel=${loglevel}"

# Load DT file
load mmc ${device} ${fdt_addr_r} ${prefix}${fdtfile}
fdt addr ${fdt_addr_r}
fdt resize 65536

load mmc ${device} ${kernel_addr_r} ${prefix}uImage

if load mmc ${device} ${initrd_addr_r} ${prefix}uInitrd; then
    bootm ${kernel_addr_r} ${initrd_addr_r} ${fdt_addr_r}
else
    bootm ${kernel_addr_r} - ${fdt_addr_r}
fi

