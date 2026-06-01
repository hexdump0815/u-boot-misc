- from: https://patchwork.ozlabs.org/project/uboot/list/?series=481393

current status:
- x96-x6 does work with hdmi, but will only compile with enabled logo
  - usb kbd not working at least with efi boot
- h96max-v56 does not work with hdmi due to vop etc. missing in dts and maybe defconfig options too
  - but it still boots the kernel fine, just no u-boot output on hdmi

todo and next steps:
- bootdelay, bootmenu, late board info etc. options shoudl be added where missing
- maybe extra usb start if required
- sync defconfig options between x96-x6 and h96max-v56
  - more stuff might be required for hdmi on h96max-v56 and some stuff could go for x96-x6
- use defconfig files instead of patches to create them
- use linux dts files instead of patches to create them
