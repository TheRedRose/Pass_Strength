#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Function to calculate password strength 
int checkPasswordStrength(const char* password){
    int score = 0;
    int length = strlen(password);
    int hasUpper = 0;
    int hasLower = 0;
    int hasDigit = 0;
    int hasSpecial = 0;
    
    //Check length (up to 5 points)
    if (length >= 8) score += 2;
    if (length >= 12) score += 2;
    if (length >= 16) score += 1;

    // Check character types
    for (int i = 0; i < length; i++){
        if (isupper(password[i])) hasLower =1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSpecial = 1;
    }

    // Add points for character variety
    if (hasUpper) score += 2;
    if (hasLower) score += 2;
    if (hasDigit) score += 2;
    if (hasSpecial) score +=3;

    //Chec k fot consecutive characters 
    int consecutive = 0;
    for (int i = 1; i < length; i++){
        if (password[i] == password[i-1]){
            consecutive++;
        }
    }
    if (consecutive > 0) score -= consecutive;

    return score;
}

// Function to provide password strength feedback
void printStrengthAnalysis (const char* password){
    int score = checkPasswordStrength(password);
    int length = strlen(password);

    printf("\nPassword Strength Analysis:\n");
    printf("-----------------------------\n");
    printf("Length: %d characters\n", length);

    // Print specific checks
    printf("\nCriteria Met:\n");
    printf("✔️ Length >= 8: %s\n", (length >= 8) ? "Yes" : "No");
    printf("✔️ Contains uppercase: %s\n", (strpbrk(password,"ABCDEFGHIJKLMNOPQRSTUVWXYZ") != NULL) ? "Yes" : "No");
    printf("✔️ Contains lowercase: %s\n", (strpbrk(password,"abcdefghijklmnopqrstuvwxyz") != NULL) ? "Yes" : "No");
    printf("✔️ Contains numbers: %s\n", (strpbrk(password, "0123456789") != NULL) ? "Yes" : "No");
    printf("✔️ Contains special characters: %s\n", (strpbrk(password, "!@#$%^&*()_+-=[]{}|:;,.<>?") != NULL) ? "Yes" : "No");

    printf("\nOverall Strength: ");
    if (score >= 12) printf("Strong");
    else if (score >= 8) printf("Medium");
    else printf("Weak");
    printf(" (Score: %d/14)\n", score);

    // Suggestions for improvement
    printf("\nSuggestions for improvement:\n");
    if (length < 12) printf("- Increase length to at least 12 characters\n");
    if (!strpbrk(password, "ABCDEFGHIKLMNOPQRSTUVWXYZ")) printf("- Add uppercase letters\n");
    if (!strpbrk(password, "abcdefghiklmnopqrstuvwxyz")) printf("- Add lowercase letters\n");
    if (!strpbrk(password, "0123456789")) printf("- Add numbers\n");
    if (!strpbrk(password, "!@#$%^&*()_+-=[]{}|;:,.<>?")) printf("- Add special characters\n");
}

int main() {
    char password[100];

    printf("Enter a password to test: ");
    fgets(password, sizeof(password), stdin);

    // Remove newline character if present
    password[strcspn(password, "\n")] = 0;

    printStrengthAnalysis(password);

    return 0;
}