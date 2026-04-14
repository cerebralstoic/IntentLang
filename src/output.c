#include <stdio.h>
#include <string.h>

int main() {
    int marks;
    scanf("%d", &marks);

    char grade[20];

    if (marks > 85) strcpy(grade, "a");
    printf("%s\n", grade);
    return 0;
}
