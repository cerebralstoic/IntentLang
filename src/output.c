#include <stdio.h>
#include <string.h>

int main() {
    int marks;
    scanf("%d", &marks);

    char grade[20];

    if (marks > 70) strcpy(grade, "B");
    else if (marks > 85) strcpy(grade, "A");
    else strcpy(grade, "C");
    printf("%s\n", grade);
    return 0;
}
