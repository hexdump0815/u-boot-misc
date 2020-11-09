this is a script to get the running device tree on android by dumping it from /proc/device-tree in some android terminal app - it so far worked for me for all android tv boxes i tried it with and it does not require root access

just put the script onto some usb-stick, plug it into the box, start a terminal app (for instance https://play.google.com/store/apps/details?id=jackpal.androidterm), do a df to see where the usb-stick is mounted (usually something like /mnt/media_rw/some-hex-hash), run the script via:

  sh device-tree-copy.sh

that should create a directory device-tree-copy and a tar file device-tree-copy.tar.gz - if that does not work, try

  sh device-tree-copy-busybox.sh

afterwards you can copy the tar.gz file (for later extraction) or directory to some linux machine and create a dts or dtb file from it via the dtc command

  dtc -I fs -O dts device-tree-copy > some-box-android.dts

or

  dtc -I fs -O dtb device-tree-copy > some-box-android.dtb
