# rockchip soc specific boot and u-boot information

some information relevant for rockchip socs and u-boot in general. see
readme.rk3328 and readme.rk3328-no-sd-boot for soc specific info.

## misc rockchip boot info

- rockchip devices always boot in a certain order and sd-cards are booted later
  in that order, so to boot them while emmc or spi are present those either
have to be empty or the bootloader in there has to be able to boot from sd-card
- rockchip devices have two special modes: loader mode and maskrom mode - more
  info about them below
- there is a tool available (including source code) to interact with a rockchip
  device in those special modes: rkdevelopertool (see below)

## loader mode

this mode often can be reached via some button (sometimes at the end of the
audio jack) by pressing it while the device is connected to the usb port of
another computer via the corresponding usb port (it will usually only work with
one of the usb ports in case there are multiple on the device). for this mode
no power should be connected to the device as power will be supplied via the
usb connection from the other computer (which sometimes requires a non-standard
usb-a to usb-a cable in some cases). in loader mode it is possible to interact
with the device via the rkdevelopertool (see below) and on the computer it is
connected to, a rockchip device should be visible via lsusb command. the
availability of the loader mode via some button etc. is often provided by the
installed u-boot bootloader and can disappear if another u-boot version is
installed, which does not support this feature - to make sure to not end up
with a bricked device it is always a good idea to switch to maskrom mode via
rkdevelopertool at least once and check if some useable miniloader for the
device can be found - if that is the case it should always be possible to
escape a device brick situation via maskrom mode.

## maskrom mode

this is the lowest level connection possible to the device and it can usually
be reached via some button, jumper or by connecting the clk pin of the emmc to
gnd to ignore the bootloader on emmc (this should always be possible as long as
one can find the clk pin of the emmc). it will also be entered automatically if
no useable boot blocks are found anywhere, so erasing the emmc completely
(after doing a backup of it before maybe) is an option as well to get there. in
maskrom mode there is not much interaction possible via the rkdevelopertool
except one can load a so called (mini)loader, which is a small programm to
initialize the dram controller and enable a connection via the usb port for
further interaction with the rkdevelopertool. with the (mini)loader loadeded
the functionality availability via rkdevelopertool is similar to the one in
loader mode.

## rkdevelopertool

this tool can be used to interact with a rockchip device in loader or maskrom
mode. it is essentially available in two ways:

- as linux x86_64 binary in
  https://github.com/rockchip-linux/rkbin/tree/master/tools which is very old,
not really working well in some situations and thus not recommended
- as a source code repo at https://github.com/rockchip-linux/rkdeveloptool
  which is not that well maintained and might require some fixes to get it
compiled nowadays (see github issues and pull request in the repo for hints)
and luckily most linux distributions ship a working compiled binary built from
this repo as a packaged version - it is highly recommended to use this version

using the "rkdevelopertool ld" (list devices) option it can easily be checked
if a rockchip device is detected on a usb port and if yes in which of the two
modes it is. besides that the tool can be used to read and write the partition
table or the content of the flash of a rockchip device. some more options to
get more information or to erase the flash etc. are available as well - see
"rkdevelopertool --help".

in maskrom mode only the "rkdevelopertool db miniloader.bin" option is
available to load the miniloader and if that was successful the other options
are available afterwards. the miniloader has to match the soc and sometimes
also the used ram type - some can be found at
https://github.com/rockchip-linux/rkbin/tree/master/bin and sometimes device
vendors also provide them or a search on the net is required to find a working
one.

in loader mode it is possible to switch to maskrom mode via the
"rkdevelopertool rd 3" command. it is a good idea to at least test this once to
make sure it is working and one can find a proper miniloader for maskrom mode
in case it is no longer possible to enter loader mode directly due to a changed
u-boot (and as a result maybe no longer working loader mode button) for
instance.

some things are a bit special while using the "rl" command to read content from
the device flash:
- the first 4mb of the flash cannot be read properly this way, so it is not
  possible to read the loader itself from flash, as it is usually located
there, it should be possible to dump it via the dd command from a running
system if root permissions are available
- after a certain point it is not possible to read the content of the flash via
  this command properly anymore as it will only return fake 0xcc data instead
of the real one. there seems to be information that this applies to all reads
beyond 0x1000 and maybe this is not the case for older loaders. as a result the
"rl" command can often not be used to dump the complete flash contents and one
should always check the dumped data to be proper and not only hex 0xcc.
