#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
//#define PATH_MAX 1024

int	is_elf(char *file) {
	int		ffd;
	char	buffer[1024];

	ffd = open(file, O_RDONLY);
	read(ffd, buffer, 4);
	if (buffer[1] == 'E' && buffer[2] == 'L' && buffer[3] == 'F') {
		close(ffd);
		return 0;
	}
	close(ffd);
	return 1;
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
			//printf("File -> %s\n", dir->d_name);
			if (strcmp(dir->d_name, "freedoom") == 0) {
				continue;
			}
			else if (!is_elf(dir->d_name))
				printf("YAY\n");
		}
		closedir(d_fd);
	}
	return 0;
}