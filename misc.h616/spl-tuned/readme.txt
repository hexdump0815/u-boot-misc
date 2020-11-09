those are spl replacements i created from the extracted bootblocks of an h313 x96q and an h616 x96q-max tv box and the spl of the above orange pi zero 2 boot blocks - in them the memory training routines were replaced with the ones from the corresponding tv boxes, so that they can boot on them and do not fail already in the memory training stage like the original orange pi zero 2 spl did. the h616 version seems to work for both boxes for me.

first write the orange pi zero 2 boot block to an sd card (the seek/skip will preserve the mbr partition table)

  dd if=boot-opi-zero-2.dd of=/dev/sdcard bs=512 seek=1 skip=1 status=progress

then write the adjusted spl over the spl in it

  dd if=h616-tv-box-dram-spl.dd of=/dev/sdcard bs=512 seek=16

afterwards make sure that the first mbr partition on the sd card does not start before sector 40960 in order to not overwrite parts of the boot blocks.


note: if booting this way still the dtb in the boot blocks is being used and not the one supplied in the /boot dir
