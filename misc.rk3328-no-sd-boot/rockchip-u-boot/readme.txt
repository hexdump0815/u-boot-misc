note: these are my notes from back when i got my h96max to boot via boot.scr or extlinux from the sd card
      all this is against 95f61521344326fa296e8c1e6298f3ac14f99d51 of https://github.com/ayufan-rock64/linux-u-boot.git

goal: change u-boot (installed later in emmc via rkdeveloptool) to boot mmc and usb as well - this
      is needed for tv boxes, which do not boot mmc on their own due to strange mmc setup (sd card
      not configured where it should be to be booted by the rk3328 soc)

patches used: z28pro + my working h96max-rk3328 linux kernel dts (sdmmc parts adapted for u-boot)

result we are interested in: u-boot-dtb.bin

u-boot to write to emmc: uboot.img
from: loaderimage --pack --uboot ./u-boot-dtb.bin uboot.img 0x200000 # loaderimage on x86

write to emmc via rkdeveloptool in loader mode:
rkdeveloptool wl 0x2000 uboot.img

important:
* rkdeveloptool soetimes gives error: ..., creating comm object failed!
  - next time it might work, maybe cable problems sometimes?
* own-u-boot-rockchip-rk3328-no-sd-boot-u-boot.img:
  - ./rkbin/tools/loaderimage --pack --uboot .../u-boot-dtb.bin own-u-boot-rockchip-rk3328-no-sd-boot-u-boot.img 0x200000
  - u-boot-dtb.bin come from u-boot-rockchip-rk3328-no-sd-boot build out of make rock64-rk3328_defconfig with
    resulting-patch/patch.diff applied

advantage of rockchip u-boot: still being able to enter rockusb mode via button
                              - not sure if this really works properly

original source and idea for my patch:

z28pro-patches: https://github.com/armbian/build/tree/master/patch/u-boot/u-boot-rockchip64/board_z28pro

a5xmax-patches:

via: https://forum.armbian.com/topic/8082-armbian-for-tv-box-rk3328/?do=findComment&comment=81095

from: https://github.com/armbian/build/pull/1415
      https://github.com/armbian/build/pull/1415.patch

also read the following gergely posts:
https://forum.armbian.com/topic/8082-armbian-for-tv-box-rk3328/?do=findComment&comment=81283
https://forum.armbian.com/topic/8082-armbian-for-tv-box-rk3328/?do=findComment&comment=81596
https://forum.armbian.com/topic/8082-armbian-for-tv-box-rk3328/?do=findComment&comment=81808
https://forum.armbian.com/topic/8082-armbian-for-tv-box-rk3328/?do=findComment&comment=81823

relevant is here i think only the u-boot patches at the end to use the external sd card (looks like this is the port the sd card is connected to on those boxes)
