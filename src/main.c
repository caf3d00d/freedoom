#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>

const unsigned char	elf_magic[4] = {0x7f, 0x45, 0x4c, 0x46};

void	infect(char *file) {
	printf("YAY %s\n", file);
}

int	is_elf(char *file) {
	int		ffd;
	char	buffer[4];

	ffd = open(file, O_RDONLY);
	read(ffd, buffer, 4);
	if (memcmp(buffer, elf_magic, sizeof(buffer)) == 0) {
		close(ffd);
		return 1;
	}
	close(ffd);
	return 0;
}

int main(void) {
	char	current_dir[PATH_MAX];
	DIR		*d_fd;
	struct	dirent *dir;

	if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
		perror("getcwd() error");
		return 1;
	}
	d_fd = opendir(current_dir);
	if (d_fd) {
		while ((dir = readdir(d_fd)) != NULL) {
			if (strcmp(dir->d_name, "freedoom") == 0)
				continue;
			else if (is_elf(dir->d_name))
				infect(dir->d_name);
		}
		closedir(d_fd);
	}
	return 0;
}