#include <stdio.h>
#include <stdlib.h>

struct Vote {
    int voterID;
    int candidate;
};

// Candidate names
void displayCandidates() {
    printf("\n====== CANDIDATES ======\n");
    printf("1. Rahul\n");
    printf("2. Priya\n");
    printf("3. Aman\n");
}

// Check whether voter has already voted
int checkVoter(int id) {
    struct Vote v;

    FILE *fp = fopen("votes.dat", "rb");

    if (fp == NULL) {
        return 0;
    }

    while (fread(&v, sizeof(v), 1, fp)) {
        if (v.voterID == id) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// Cast Vote
void castVote() {
    struct Vote v;

    printf("\nEnter Voter ID: ");
    scanf("%d", &v.voterID);

    if (checkVoter(v.voterID)) {
        printf("\nYou have already voted!\n");
        return;
    }

    displayCandidates();

    printf("\nEnter Candidate Number: ");
    scanf("%d", &v.candidate);

    if (v.candidate < 1 || v.candidate > 3) {
        printf("Invalid Candidate!\n");
        return;
    }

    FILE *fp = fopen("votes.dat", "ab");

    if (fp == NULL) {
        printf("File Error!\n");
        return;
    }

    fwrite(&v, sizeof(v), 1, fp);

    fclose(fp);

    printf("\nYour Vote Has Been Recorded Successfully!\n");
}

// Display Election Results
void displayResults() {
    struct Vote v;

    int votes[4] = {0};
    int total = 0;

    FILE *fp = fopen("votes.dat", "rb");

    if (fp == NULL) {
        printf("\nNo Votes Recorded Yet!\n");
        return;
    }

    while (fread(&v, sizeof(v), 1, fp)) {
        votes[v.candidate]++;
        total++;
    }

    fclose(fp);

    printf("\n====== ELECTION RESULTS ======\n");

    printf("Rahul: %d votes\n", votes[1]);
    printf("Priya: %d votes\n", votes[2]);
    printf("Aman: %d votes\n", votes[3]);

    printf("\nTotal Votes: %d\n", total);

    if (total > 0) {
        int max = votes[1];

        if (votes[2] > max)
            max = votes[2];

        if (votes[3] > max)
            max = votes[3];

        if (votes[1] == max && votes[2] == max &&
            votes[3] == max) {
            printf("Result: Three-way tie!\n");
        }
        else if ((votes[1] == max && votes[2] == max) ||
                 (votes[1] == max && votes[3] == max) ||
                 (votes[2] == max && votes[3] == max)) {
            printf("Result: Tie between candidates!\n");
        }
        else if (votes[1] == max) {
            printf("Winner: Rahul\n");
        }
        else if (votes[2] == max) {
            printf("Winner: Priya\n");
        }
        else {
            printf("Winner: Aman\n");
        }
    }
}

// Main Function
int main() {
    int choice;

    do {
        printf("\n================================\n");
        printf("       DIGITAL VOTING SYSTEM\n");
        printf("================================\n");

        printf("1. Display Candidates\n");
        printf("2. Cast Vote\n");
        printf("3. View Election Results\n");
        printf("4. Exit\n");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                displayCandidates();
                break;

            case 2:
                castVote();
                break;

            case 3:
                displayResults();
                break;

            case 4:
                printf("\nThank You for Using Digital Voting System!\n");
                break;

            default:
                printf("\nInvalid Choice! Try Again.\n");
        }

    } while (choice != 4);

    return 0;
}