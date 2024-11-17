#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*Define constants*/
#define NUM_TEAMS 5   // Define the number of teams in the league.
#define SQUAD_SIZE 11 // Define the maximum squad size for each team.

/*Defining struct type datas used in function*/
typedef struct {
    int day;
    int month;
    int year;
} birth_date_t;

typedef struct {
    char name[26];    // Full name (max 25 characters)
    int kit_number;   // Kit number (1-99)
    char club[21];    // Club name (max 20 characters)
    birth_date_t birth_date; // Date of birth
    char position[21];  // Player position (max 20 characters)
} player_t;

typedef struct {
    char name[21];     // Team name (max 20 characters)
    player_t players[SQUAD_SIZE]; // Array of players in the team
    int active_size;   // Number of enrolled players in the team
} team_t;

/*Prototypes of functions used in program*/
void display_menu(void); //display menu function 
int enroll_club(team_t teams[], int num_teams); //enrol clubs function
int add_player(team_t teams[], int num_teams); //adding players to clubs function
void search_update(team_t teams[], int num_teams); //updating details function
void display_club_statistics(team_t teams[], int num_teams); //Display club's info function
void handle_error(char message[]); //error cases function

/*Main Function Code*/
int main() {
    team_t teams[NUM_TEAMS];
    int num_teams = 0;

    while (1) {
        display_menu();
        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n'); // Clear buffer

        switch (choice) {
            case 1: 
            num_teams = enroll_club(teams, num_teams); break; 
            
            case 2: 
            num_teams = add_player(teams, num_teams); break; 
            
            case 3: 
            search_update(teams, num_teams);break; 
            
            case 4: 
            display_club_statistics(teams, num_teams); break; 
            
            case 5: 
            printf("Exiting program.\n"); 
            return 0; 
            
            default: 
            handle_error("Invalid choice. Exiting."); 
            return 1;
        }
    }
}

void display_menu(void) {
    printf("\n--- Menu ---\n");
    printf("1. Enroll a club\n");
    printf("2. Add a player\n");
    printf("3. Search and update a player\n");
    printf("4. Display club statistics\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int enroll_club(team_t teams[], int num_teams) {
    if (num_teams >= NUM_TEAMS) {
        printf("Maximum number of clubs reached. Cannot enroll more.\n");
        return num_teams;
    }

    char club_name[21];
    printf("Enter the club name: ");
    fgets(club_name, sizeof(club_name), stdin);
    club_name[strcspn(club_name, "\n")] = 0; // Remove the newline character

    strcpy(teams[num_teams].name, club_name);
    teams[num_teams].active_size = 0; // No players initially
    num_teams++;
    printf("Club %s has been enrolled successfully.\n", club_name);

    return num_teams;
}

int add_player(team_t teams[], int num_teams) {
    char club_name[21];
    printf("Enter the club name to add a player: ");
    fgets(club_name, sizeof(club_name), stdin);
    club_name[strcspn(club_name, "\n")] = 0;

    // Find team by name
    int team_index = -1;
    for (int i = 0; i < num_teams; i++) {
        if (strcmp(teams[i].name, club_name) == 0) {
            team_index = i;
            break;
        }
    }
    if (team_index == -1) {
        printf("Team not found.\n");
        return num_teams;
    }

    if (teams[team_index].active_size >= SQUAD_SIZE) {
        printf("The team already has the maximum number of players.\n");
        return num_teams;
    }

    player_t new_player;
    printf("Enter player's full name (First Last): ");
    fgets(new_player.name, sizeof(new_player.name), stdin);
    new_player.name[strcspn(new_player.name, "\n")] = 0;

    printf("Enter player's kit number (1-99): ");
    scanf("%d", &new_player.kit_number);
    while (getchar() != '\n'); // Clear buffer

    // Check if kit number is valid
    if (new_player.kit_number < 1 || new_player.kit_number > 99) {
        handle_error("Invalid kit number. Must be between 1 and 99.");
        return num_teams;
    }

    // Check for duplicate kit number
    for (int i = 0; i < teams[team_index].active_size; i++) {
        if (teams[team_index].players[i].kit_number == new_player.kit_number) {
            handle_error("Kit number already taken by another player.");
            return num_teams;
        }
    }

    // Check for duplicate player name
    for (int i = 0; i < teams[team_index].active_size; i++) {
        if (strcmp(teams[team_index].players[i].name, new_player.name) == 0) {
            handle_error("Player name already exists.");
            return num_teams;
        }
    }

    printf("Enter player's birthdate (day month year): ");
    scanf("%d %d %d", &new_player.birth_date.day, &new_player.birth_date.month, &new_player.birth_date.year);
    while (getchar() != '\n'); // Clear buffer

    // Validate birthdate
    if (new_player.birth_date.month < 1 || new_player.birth_date.month > 12 ||
        new_player.birth_date.day < 1 || new_player.birth_date.day > 31 ||
        (new_player.birth_date.month == 2 && new_player.birth_date.day > 29)) {
        handle_error("Invalid birthdate.");
        return num_teams;
    }

    printf("Enter player's position: ");
    fgets(new_player.position, sizeof(new_player.position), stdin);
    new_player.position[strcspn(new_player.position, "\n")] = 0;

    teams[team_index].players[teams[team_index].active_size] = new_player;
    teams[team_index].active_size++;
    printf("Player added successfully.\n");

    return num_teams;
}

void search_update(team_t teams[], int num_teams) {
    char search_term[26];
    int choice;
    printf("Search by:\n");
    printf("1. Player name\n");
    printf("2. Kit number\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Clear buffer

    if (choice == 1) {
        printf("Enter player name: ");
        fgets(search_term, sizeof(search_term), stdin);
        search_term[strcspn(search_term, "\n")] = 0;

        for (int i = 0; i < num_teams; i++) {
            for (int j = 0; j < teams[i].active_size; j++) {
                if (strcmp(teams[i].players[j].name, search_term) == 0) {
                    printf("Player found: %s, Kit number: %d, Age: %d/%d/%d, Position: %s\n",
                           teams[i].players[j].name,
                           teams[i].players[j].kit_number,
                           teams[i].players[j].birth_date.day,
                           teams[i].players[j].birth_date.month,
                           teams[i].players[j].birth_date.year,
                           teams[i].players[j].position);

                    printf("Enter new position: ");
                    fgets(teams[i].players[j].position, sizeof(teams[i].players[j].position), stdin);
                    teams[i].players[j].position[strcspn(teams[i].players[j].position, "\n")] = 0;
                    printf("Player updated.\n");
                    return;
                }
            }
        }
        handle_error("Player not found.");
    } else if (choice == 2) {
        int kit_number;
        printf("Enter kit number: ");
        scanf("%d", &kit_number);
        while (getchar() != '\n'); // Clear buffer

        for (int i = 0; i < num_teams; i++) {
            for (int j = 0; j < teams[i].active_size; j++) {
                if (teams[i].players[j].kit_number == kit_number) {
                    printf("Player found: %s, Kit number: %d, Age: %d/%d/%d, Position: %s\n",
                           teams[i].players[j].name,
                           teams[i].players[j].kit_number,
                           teams[i].players[j].birth_date.day,
                           teams[i].players[j].birth_date.month,
                           teams[i].players[j].birth_date.year,
                           teams[i].players[j].position);

                    printf("Enter new position: ");
                    fgets(teams[i].players[j].position, sizeof(teams[i].players[j].position), stdin);
                    teams[i].players[j].position[strcspn(teams[i].players[j].position, "\n")] = 0;
                    printf("Player updated.\n");
                    return;
                }
            }
        }
        handle_error("Player not found.");
    } else {
        handle_error("Invalid choice.");
    }
}

void display_club_statistics(team_t teams[], int num_teams) {
    for (int i = 0; i < num_teams; i++) {
        printf("\nTeam: %s\n", teams[i].name);
        printf("Number of players: %d\n", teams[i].active_size);

        // Calculate average age
        int total_age = 0;
        for (int j = 0; j < teams[i].active_size; j++) {
            int current_year = 2024; // Assuming current year is 2024
            total_age += current_year - teams[i].players[j].birth_date.year;
        }
        float average_age = (teams[i].active_size > 0) ? (float)total_age / teams[i].active_size : 0.0;

        printf("Average age: %.2f\n", average_age);

        for (int j = 0; j < teams[i].active_size; j++) {
            printf("Player %d: %s, Kit number: %d, Position: %s, DOB: %d/%d/%d\n",
                   j + 1,
                   teams[i].players[j].name,
                   teams[i].players[j].kit_number,
                   teams[i].players[j].position,
                   teams[i].players[j].birth_date.day,
                   teams[i].players[j].birth_date.month,
                   teams[i].players[j].birth_date.year);
        }
    }
}


void handle_error(char message[]) {
    printf("Error: %s\n", message);
}