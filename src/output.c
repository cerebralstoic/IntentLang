#include <stdio.h>
#include <string.h>

int main() {
    int marks;
    scanf("%d", &marks);
    float attendance;
    scanf("%f", &attendance);

    char grade[20];

    if (marks < 40) strcpy(grade, "fail");
    else if (attendance < 75) strcpy(grade, "fail");
    else if (marks >= 85) strcpy(grade, "A");
    else if (marks >= 70) strcpy(grade, "B");
    else strcpy(grade, "C");
    printf("%s\n", grade);
    return 0;
}
