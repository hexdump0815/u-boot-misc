mkdir device-tree-copy
cd device-tree-copy
for i in `busybox find /proc/device-tree/ -type d | busybox sed 's,/proc/device-tree/,,g'` ; do echo $i; mkdir -p $i ; done
for i in `busybox find /proc/device-tree/ -type f | busybox sed 's,/proc/device-tree/,,g'` ; do echo $i; cat /proc/device-tree/$i > $i ; done
cd ..
busybox tar czf device-tree-copy.busybox tar.gz device-tree-copy
