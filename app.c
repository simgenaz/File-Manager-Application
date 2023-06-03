#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_TEXT_LENGTH 1000

void createFile(char* filename) { //takes the filename

    FILE* file = fopen(filename, "w"); //The function opens the filename using 'w' mode

    if (file == NULL) {

        fclose(file);

        printf("File created successfully.\n");

    } else {

        printf("Error creating file.\n");

    }
}

void deleteFile(char* filename) { //takes the filename

    if (remove(filename) == 0) { //It takes remove method and delete the file

        printf("File deleted successfully.\n");

    } else {

        printf("Error deleting file.\n");

    }
}

void renameFile(char* oldFilename, char* newFilename) { //takes oldFilename and newFilename

    if (rename(oldFilename, newFilename) == 0) { //It takes the rename method and change them

        printf("File renamed successfully.\n");

    } else {

        printf("Error renaming file.\n");

    }
}

void copyFile(char* sourceFilename, char* destinationFilename) { // takes sourceFilename and destinationFilename

    FILE* source = fopen(sourceFilename, "r");  // It opens the sourceFilename and using 'r' mode

    if (source == NULL) {

        printf("Error opening source file.\n");

        return;

    }

    FILE* destination = fopen(destinationFilename, "w"); // It opens the destinationFilename and using 'w' mode

    if (destination == NULL) {

        printf("Error creating destination file.\n");

        fclose(source);

        return;
    }

    int ch; //that will be used to store the characters read from the source.

    while ((ch = fgetc(source)) != EOF) { // That reads chars from the source file using fgetc. function reads the next
//char from the file and returns it as an integer value. The loop continues as long as the returned chat is not the
//end of file.

        fputc(ch, destination); // this line writes the chars stored in ch to the destination file using fputc.
    }

    fclose(source);

    fclose(destination);

    printf("File copied successfully.\n");
}

void moveFile(char* sourceFilename, char* destinationFolder) { // takes sourceFilename and destinationFolder

    char destinationPath[MAX_FILENAME_LENGTH + 1];

    snprintf(destinationPath, sizeof(destinationPath), "%s/%s", destinationFolder, sourceFilename);

//It uses the function to write a formatted string composed of destinationFolder and sourceFilename into the destinationPath array.


    if (rename(sourceFilename, destinationPath) == 0) {

        printf("File moved successfully.\n");

    } else {

        printf("Error moving file.\n");
    }
}

void appendText(char* filename, char* text) { //takes filename and text

    FILE* file = fopen(filename, "a"); //It opens filename using 'a' mode

    if (file != NULL) {

        fprintf(file, "%s", text);

        fclose(file);

        printf("Text appended successfully.\n"); //if file exist it appends the text

    } else {

        printf("Error appending text.\n"); //If file doesnt exist it returns error message

    }
}

void insertText(char* filename, char* text, int position) {  //takes filename, text and position

    FILE* file = fopen(filename, "r+"); //It opens filename using 'r+' mode and insert the text to that file

    if (file != NULL) {

        fseek(file, position, SEEK_SET); // It sets to file position to a specified position.

        char* remainingText = malloc(MAX_TEXT_LENGTH); // Its allocates memory for a char array of size

        fgets(remainingText, MAX_TEXT_LENGTH, file); //It reads a line of text from the file and stores it in the remainingText

        fseek(file, position, SEEK_SET); // It sets to file position to a specified position.

        fprintf(file, "%s%s", text, remainingText); //It writes a fotmatted string to the file.

        free(remainingText); //It releases the memory.

        fclose(file);

        printf("Text inserted successfully.\n");

    } else {

        printf("Error inserting text.\n");

    }
}

void removeAllText(char* filename) { //takes filename

    FILE* file = fopen(filename, "w");  // It opens the file using 'w' mode and remove all texts in that file

    if (file != NULL) {

        fclose(file);

        printf("All text removed successfully.\n");

    } else {

        printf("Error removing text.\n");

    }
}

void showContent(char* filename, int linesPerPage) {  //Takes the filename and line number

    FILE* file = fopen(filename, "r"); // It opens the file and using 'r' mode

    if (file != NULL) {

        char line[256];

        int lineCount = 0;

        int pageCount = 0;

        while (fgets(line, sizeof(line), file) != NULL) {

            printf("%s", line);

            lineCount++;

            if (lineCount % linesPerPage == 0) {

                pageCount++;

                printf("-- Page %d --\n", pageCount);

                printf("Press Enter to continue...");

                getchar();

            }
        }

        fclose(file);

        printf("End of file.\n");

    } else {

        printf("Error opening file.\n");

    }
}

int main() {

    char command[100];

    char filename[MAX_FILENAME_LENGTH + 1];

    char newFilename[MAX_FILENAME_LENGTH + 1];

    char text[MAX_TEXT_LENGTH + 1];

    char destinationFolder[MAX_FILENAME_LENGTH + 1];

    int position, linesPerPage;


    printf("Welcome to isik_filemanager!\n");

    while (1) {

        printf("\nEnter a command (or type '/help' for a list of commands): ");

        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = '\0'; // Remove trailing newline character

        if (strcmp(command, "/help") == 0) { //explaining command names
            printf("Available commands:\n");
            printf("/create <filename>\n");
            printf("/delete <filename>\n");
            printf("/rename <old_filename> <new_filename>\n");
            printf("/copy <source_filename> <destination_filename>\n");
            printf("/move <source_filename> <destination_folder>\n");
            printf("/append <filename> <text_to_append>\n");
            printf("/insert <filename> <text_to_insert> <position>\n");
            printf("/remove <filename>\n");
            printf("/show <filename> <lines_per_page>\n");

        } else if (strncmp(command, "/create", 7) == 0) { //it checks if the command starts with /create or not

	    sscanf(command, "/create %s", filename);  // The sscanf function is used to extract the filename from the command. It reads the string stored in command and looks for the pattern "/create %s", where "%s" indicates a string.

	    createFile(filename); // create the filename

        } else if (strncmp(command, "/delete", 7) == 0) { // it checks if the command starts with /delete or not

            sscanf(command, "/delete %s", filename); // takes the filename

            deleteFile(filename); // deletes the filename

        } else if (strncmp(command, "/rename", 7) == 0) { //it checks if the command starts with /rename or not

            sscanf(command, "/rename %s %s", filename, newFilename); // First %s takes the parameter of filename and second %s is takes the newFilename

            renameFile(filename, newFilename); // Takes two parameter and change with renameFile

        } else if (strncmp(command, "/copy", 5) == 0) { //it checks if the command starts with /copy or not

            sscanf(command, "/copy %s %s", filename, newFilename); // First %s takes the parameter of filename and second %s is takes the newFilename

            copyFile(filename, newFilename); //Makes the newFilename same as filename

        } else if (strncmp(command, "/move", 5) == 0) { //it checks if the command starts with /move or not

            sscanf(command, "/move %s %s", filename, destinationFolder); // First %s takes the parameter of filename and second %s is takes the newFilename

            moveFile(filename, destinationFolder); // Change the destination with the parameters

        } else if (strncmp(command, "/append", 7) == 0) { //it checks if the command starts with /append or not

            sscanf(command, "/append %s %[^\n]", filename, text);  // It takes filename and text.

            appendText(filename, text); // To add that text in to the file

        } else if (strncmp(command, "/insert", 7) == 0) { //it checks if the command starts with /insert or not

            sscanf(command, "/insert %s %[^\n] %d", filename, text, &position);  // Takes the filename, text and position

            insertText(filename, text, position); //insert them

        } else if (strncmp(command, "/remove", 7) == 0) { //it checks if the command starts with /remove or not

            sscanf(command, "/remove %s", filename); //takes the filename which one is going to removed

            removeAllText(filename); //makes the remove in that file

        } else if (strncmp(command, "/show", 5) == 0) { //it checks if the command starts with /show or not

            sscanf(command, "/show %s %d", filename, &linesPerPage); // It takes filename and lines

            showContent(filename, linesPerPage); //shows line in that file

        } else {

            printf("Invalid command. Type '/help' for a list of commands.\n");

        }
    }

    return 0;
}
