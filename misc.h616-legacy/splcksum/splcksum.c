#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define CKSUM_OFFSET 0x0c
#define SPL_FILENAME "spl.dd"

u_int32_t magic_checksum=0x5F0A6C39;

int main() {
	
	u_int32_t checksum;
	u_int32_t word;
	int fd;

	checksum = 0;
	fd = open(SPL_FILENAME, O_RDWR);

	if ( fd < 0 ) {
		perror("error: ");
		exit(1);
	}

	lseek(fd, CKSUM_OFFSET, SEEK_SET);
	write(fd, &magic_checksum, 4);
	lseek(fd, 0, SEEK_SET);

	while(read(fd, &word, 4))
		checksum += word;

	lseek(fd, CKSUM_OFFSET, SEEK_SET);
	write(fd, &checksum, 4);

	close(fd);

}
