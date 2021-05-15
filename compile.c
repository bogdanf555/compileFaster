#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXNAME 1000
#define MAXPROGRAMNAME 32
#define MAXNROFSOURCEFILES 10
#define MAXFLAGS 680

int main(int argc, char** argv) {

	if(argc == 1) {
		printf("USAGE: compile [ -gcc_flags ] program_names.c\n");
		exit(1);
	}

	int nr_of_source_files = 0;
	int flags_string_len = 0;
	int command_len = 0;

	char command[MAXNAME];
	char source_files_name[MAXNROFSOURCEFILES][MAXPROGRAMNAME];
	char flags[MAXFLAGS];

	for(int i = 1; i < argc; i++) {

		if(strstr(argv[i], ".c")) {
			
			if(argv[i][0] == '-') {
				printf("ERROR: only gcc flags should begin with a dash character.\n");
				exit(2);
			}

			if(strlen(argv[i]) > MAXPROGRAMNAME) {
				printf("ERROR: %s has exceeds the name length (maximum %d characters)\n", argv[i], MAXPROGRAMNAME - 2);
				exit(3);
			}

			strcpy(source_files_name[nr_of_source_files], argv[i]);

			nr_of_source_files++;

			if(nr_of_source_files > MAXNROFSOURCEFILES) {
				printf("ERROR: the maximum number of source files that can be provided is %d\n", MAXNROFSOURCEFILES);
				exit(4);
			}
		}

		if(argv[i][0] == '-') {
			strcpy(flags + flags_string_len, " ");
			flags_string_len++;
			strcpy(flags + flags_string_len, argv[i]);
			flags_string_len += strlen(argv[i]);
		}
	}

	flags[flags_string_len] = '\0';

	if(nr_of_source_files == 0) {
		printf("ERROR: at least one source code file should be provided.\n");
		exit(5);
	}

	char binary_file_name[MAXPROGRAMNAME];

	strcpy(binary_file_name, source_files_name[0]);
	char *dot_occurrence = strrchr(binary_file_name, '.');

	if(dot_occurrence) {
		*dot_occurrence = '\0';
	}

	sprintf(command, "gcc -Wall -Werror");
	command_len = strlen(command);

	for(int i = 0; i < nr_of_source_files; i++) {
		if(command_len >= MAXNAME - 2) {
			printf("ERROR: command exceeding the max length.\n");
			exit(6);
		}
		strcpy(command + command_len, " ");
		command_len++;

		if(command_len + strlen(source_files_name[i]) >= MAXNAME - 2) {
			printf("ERROR: command exceeding the max length (%d).\n", MAXNAME);
			exit(6);
		}

		strcpy(command + command_len, source_files_name[i]);
		command_len += strlen(source_files_name[i]);
	}

	if(command_len + flags_string_len + 1 >= MAXNAME) {
		printf("ERROR: command exceeding the max length (%d).\n", MAXNAME);
		exit(6);
	}

	strcpy(command + command_len, " ");
	command_len++;
	strcpy(command + command_len, flags);
	command_len += flags_string_len;

	if(command_len + strlen(binary_file_name) + 4 > MAXNAME) {
		printf("ERROR: command exceeding the max length (%d).\n", MAXNAME);
		exit(6);
	}

	strcpy(command + command_len, " -o ");
	command_len += 4;
	strcpy(command + command_len, binary_file_name);
	command_len += strlen(binary_file_name);

	fflush(NULL);

	if(system(command)) {
		printf("ERROR: could not compile, please make sure you use valid gcc flags.\n");
		exit(7);
	}

	return 0;
}
