
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

#define NUM_PROCESSES 4
#define BUFFER_SIZE 1024

void read_file_chunk(const char* filename, long start_pos, long chunk_size, int process_id) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Process %d: Error opening file\n", process_id);
        return;
    }

    // Seek to the starting position for this process
    fseek(file, start_pos, SEEK_SET);

    char buffer[BUFFER_SIZE];
    long bytes_read = 0;
    
    printf("Process %d: Reading from position %ld\n", process_id, start_pos);
    
    while (bytes_read < chunk_size && !feof(file)) {
        size_t read_size = fread(buffer, 1, 
            (chunk_size - bytes_read) < BUFFER_SIZE ? (chunk_size - bytes_read) : BUFFER_SIZE, 
            file);
        
        if (read_size > 0) {
            buffer[read_size] = '\0';
            printf("Process %d: Read chunk: %s\n", process_id, buffer);
            bytes_read += read_size;
        }
    }

    fclose(file);
}

int main() {
    const char* filename = "sample.txt";
    
    // Create a sample file for testing
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error creating sample file\n");
        return 1;
    }
    
    // Write some sample text
    fprintf(file, "This is a sample text file.\n");
    fprintf(file, "It contains multiple lines of text.\n");
    fprintf(file, "Each process will read a portion of this file.\n");
    fprintf(file, "This demonstrates parallel file reading using multiple processes.\n");
    fclose(file);
    
    // Get file size
    struct stat st;
    stat(filename, &st);
    long file_size = st.st_size;
    long chunk_size = file_size / NUM_PROCESSES;
    
    printf("File size: %ld bytes\n", file_size);
    printf("Each process will read approximately %ld bytes\n", chunk_size);
    
    pid_t pids[NUM_PROCESSES];
    
    // Create multiple processes
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pids[i] = fork();
        
        if (pids[i] < 0) {
            printf("Error creating process\n");
            return 1;
        }
        
        if (pids[i] == 0) {  // Child process
            long start_pos = i * chunk_size;
            // Last process reads any remaining bytes
            long process_chunk_size = (i == NUM_PROCESSES - 1) ? 
                (file_size - start_pos) : chunk_size;
                
            read_file_chunk(filename, start_pos, process_chunk_size, i + 1);
            exit(0);
        }
    }
    
    // Parent process waits for all children to complete
    for (int i = 0; i < NUM_PROCESSES; i++) {
        waitpid(pids[i], NULL, 0);
    }
    
    printf("All processes completed\n");
    return 0;
}
