#include <stdio.h>
#include <stdbool.h>

#define WORD_LENGTH 5
#define MAX_GUESSES 6

void to_lower(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A');
        }
        i++;
    }
}

bool is_alpha(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return true;
    }
    return false;
}

bool valid_guess(char guess[]) {
    int i = 0;

    while (guess[i] != '\0') {
        i++;
    }

    if (i != WORD_LENGTH) {
        return false;
    }

    i = 0;
    while (i < WORD_LENGTH) {
        if (!is_alpha(guess[i])) {
            return false;
        }
        i++;
    }

    return true;
}

void print_all_guesses(char guesses[][WORD_LENGTH + 1], char feedbacks[][WORD_LENGTH + 1], int count) {
    int i;
    for (i = 0; i < count; i++) {
        printf("%s\n", guesses[i]);
        printf("%s\n", feedbacks[i]);
    }
}

void process_feedback(char guess[], char mystery[], char display[], char feedback[]) {
    int i, j;
    bool used[WORD_LENGTH];

    for (i = 0; i < WORD_LENGTH; i++) {
        used[i] = false;
        display[i] = guess[i];
        feedback[i] = ' ';
    }

    for (i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == mystery[i]) {
            display[i] = guess[i] - ('a' - 'A');
            used[i] = true;
        }
    }

    for (i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] != mystery[i]) {
            for (j = 0; j < WORD_LENGTH; j++) {
                if (!used[j] && guess[i] == mystery[j]) {
                    feedback[i] = '^';
                    used[j] = true;
                    break;
                }
            }
        }
    }

    display[WORD_LENGTH] = '\0';
    feedback[WORD_LENGTH] = '\0';
}

bool is_correct(char guess[], char mystery[]) {
    int i = 0;
    while (i < WORD_LENGTH) {
        if (guess[i] != mystery[i]) {
            return false;
        }
        i++;
    }
    return true;
}

int main() {
    FILE *file = fopen("mystery.txt", "r");
    char mystery[WORD_LENGTH + 1];
    int i = 0;
    char c;

    if (file != NULL) {
        while (i < WORD_LENGTH && (c = fgetc(file)) != EOF) {
            if (c >= 'A' && c <= 'Z') {
                c = c + ('a' - 'A');
            }
            mystery[i] = c;
            i++;
        }
        mystery[WORD_LENGTH] = '\0';
        fclose(file);
    } else {
        printf("Could not open mystery.txt\n");
        return 0;
    }

    char guess[100];
    char guesses[MAX_GUESSES + 1][WORD_LENGTH + 1];
    char feedbacks[MAX_GUESSES + 1][WORD_LENGTH + 1];

    int guess_count = 0;
    bool won = false;

    while (guess_count < MAX_GUESSES && won == false) {
        int j = 0;
        char ch;

        if (guess_count == MAX_GUESSES - 1) {
            printf("FINAL GUESS : ");
        } else {
            printf("GUESS %d! Enter your guess: ", guess_count + 1);
        }

        while ((ch = getchar()) != '\n' && ch != EOF && j < 99) {
            guess[j] = ch;
            j++;
        }
        guess[j] = '\0';

        to_lower(guess);

        if (!valid_guess(guess)) {
            printf("Your guess must be 5 letters long.\n");
        } else {
            process_feedback(guess, mystery, guesses[guess_count], feedbacks[guess_count]);

            if (is_correct(guess, mystery)) {
                printf("================================\n");
                printf("\t\t");
                for (i = 0; i < WORD_LENGTH; i++) {
                    if (guess[i] >= 'a' && guess[i] <= 'z') {
                        printf("%c", guess[i] - ('a' - 'A'));
                    } else {
                        printf("%c", guess[i]);
                    }
                }
                printf("\n");
                printf("\tYou won in %d guesses!\n", guess_count + 1);
                printf("\t\tNice!\n");
                won = true;
            } else {
                printf("================================\n");
                print_all_guesses(guesses, feedbacks, guess_count + 1);
            }

            guess_count++;
        }
    }

    if (!won) {
        printf("You lost, better luck next time!\n");
    }

    return 0;
}



              

    

        

   
