#include <fcntl.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE 1024
char buffer[BUFSIZE];
ssize_t bytes_read;
char *token, *bufp, *delim = " \n";

typedef struct { // defintion for object
	char word[42]; // character array of 42 characters under the name word (stack allocated array)  
	unsigned count; // unsigned integer under the name count (stack allocated integer)
} WORD_T;

WORD_T *words = NULL; 
/* pointer to WORD_T object (heap allocated object) (A heap is a region of memory that is not managed automatically for you, and is 
*not as tightly managed by the CPU. It is a more free-floating region of memory (and is larger). To allocate memory on the heap, you must use malloc() 
*or calloc(), which are built-in C functions. Once you have allocated memory on the heap, your pointer to that memory can be passed around and used by 
*any function that has access to it. When you are done with it, you use free() to deallocate that chunk of memory.)
*size_t total_words = 0;  size_t is an unsigned integer type of at least 16 bit used to represent the size of any object in bytes. (stack allocated integer)
*/



void print_and_free(WORD_T*, size_t, char*); // (stack allocated function) function prototype
int comparator(const void *a, const void *b) { // comparator function (stack allocated function)
	char *a_word = (char *)a; // casting a to a char pointer and assigning it to a_word (stack allocated pointer)
	WORD_T *b_word = (WORD_T *)b; //  casting b to a WORD_T pointer and assigning it to b_word (stack allocated pointer)
	return strcmp(a_word, b_word->word); // comparing a_word string to b_word string (stack allocated string)


}

int main(int argc, char **argv) { // wc [filename] syntax program calling
	/*if (argc != 2) { // if no filename is given
		printf("Usage: %s [filename]\n", argv[0]); // print usage
		return -1; // return error
	}
	char *buf = malloc(1024); // allocating 1024 bytes of memory to buf (heap allocated array) 
	char *bufp = buf; // assigning buf to bufp (stack allocated pointer). bufp is a pointer to buf (heap allocated array)
	char *token = strsep(&bufp, " ");
	while (bufp != NULL) {
		lfind(token, words, &total_words, sizeof(WORD_T), comparator);
		words = realloc(words, sizeof(WORD_T) * (total_words + 1));
		WORD_T *wordp = &words[total_words];
		(*wordp).count = 1;
		strcpy((*wordp).word, token);
		words[total_words].count = 2;
		total_words++;
		printf("%s\n", token);
		token = strsep(&bufp, " \n");
	}
	*/

	
	if (argc != 2) return -1; // if no filename is given, return error

	char *infile = argv[1]; // assigning argv[1] to infile (stack allocated pointer)
	int fd = open(infile, O_RDONLY); // open file for reading only
	if (fd == -1) return -2; // if file cannot be opened, return error

	// TODO: repeatedly call `read()` into a buffer of
	//       size BUFSIZE. Split the text in the buffer
	//       on newlines and spaces. For each token:
	//       search the `words` array to see if that
	//       word has already been added and if so
	//       increment the count. Otherwise add a new
	//       WORD_T struct to the end of the array of
	//       structs `words` and set the fields accordingly.
	
	// Do a linear search (lsearch) to see if the word is already in the array and update the count
    
	char buffer[BUFSIZE];
	ssize_t bytes_read;
	while ((bytes_read = read(fd, buffer, BUFSIZE - 1)) > 0) { // read from file into buffer until end of file
		buffer[bytes_read] = '\0';  // Null-terminate the string
		// Tokenize and process the buffer here
		while ((token = strsep(&buffer, delim)) != NULL)
		{
   		 if (*token == '\0') continue; // Skip empty tokens
			// Check if token exists in words array and update count
			// If not, add it to the array

		}
		// Handle potential incomplete word at end of buffer here
		

		
	}
	if (bytes_read == -1) {
		perror("Error reading file");
		// Handle error
	}
	// TODO: its possible that a word is split between
	//       one fill of the buffer and the next. You must
	//       move the last word at the end of the buffer to
	//       the beginning of the buffer and then fill
	//       the buffer from that point!

	char *token, *delim = " \n";
	while ((token = strsep(&buffer, delim)) != NULL)
		{
   		 if (*token == '\0') continue; // Skip empty tokens
			// Check if token exists in words array and update count
			// If not, add it to the array
		}
	

		print_and_free(words, total_words, infile);
		// TODO: close the file
		// Also possibly free the buffer that was allocated by `read()`

		return 0;
	}

// **Implementing Comparator Function:**
//```c
int comparator(const void *a, const void *b) {
	const WORD_T *word_a = (const WORD_T *)a;
	const WORD_T *word_b = (const WORD_T *)b;
	return strcmp(word_a->word, word_b->word);
}


void print_and_free(WORD_T *words, size_t total_words, char *infile) {
	int sum = 0;
	for (int i = 0; i < total_words; ++i) {
		if (words[i].count > 1)
			printf("%s: %u\n", words[i].word, words[i].count);
		sum += words[i].count;
	}
	printf("\n%d %s\n", sum, infile);
	printf("\n");
	free(words);
}
