#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>

/*
	Usage: run webm2mp4 in a directory with webms
/*

// Check that filename ends with a .webm
int webm_check(char* fn) {
	for(int i=0;i<strlen(fn);i++) {
		if(fn[i] == '.' && strcmp(&fn[i], ".webm\0") == 0) {
			return 0;
		} 
	}
	return -1;
}

// Take the input of example.webm -> output as example.mp4
void add_mp4_extension(char* input, char* output) {
	strcpy(output, input);
	for(int i=0;i<strlen(output);i++) {
		if(output[i] == '.' && strcmp(&output[i], ".webm\0") == 0) {
			strcpy(&output[i+1], "mp4");
		}
	}
}

int main(void) {
	DIR* directory = opendir("./");
	struct dirent* entry;

	if(directory == NULL) {
		fprintf(stderr, "Could not open directory\n");
		return 0;
	}

	char command[256];
	char filename_mp4[256];
	while((entry = readdir(directory))) {
		if(webm_check(entry->d_name) == 0) {
			
			add_mp4_extension(entry->d_name, filename_mp4);
			sprintf(command, "ffmpeg -loglevel panic -i \"%s\" \"%s\"", entry->d_name, filename_mp4);
			printf("Running: %s\n", command);
			system(command);
		}
	}
	printf("All webms converted\n");
}
