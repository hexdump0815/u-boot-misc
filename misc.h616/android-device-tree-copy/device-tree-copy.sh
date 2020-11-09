mkdir device-tree-copy
cd device-tree-copy
for i in `find /proc/device-tree/ -type d | sed 's,/proc/device-tree/,,g'` ; do echo $i; mkdir -p $i ; done
for i in `find /proc/device-tree/ -type f | sed 's,/proc/device-tree/,,g'` ; do echo $i; cat /proc/device-tree/$i > $i ; done
cd ..
tar czf device-tree-copy.tar.gz device-tree-copy
