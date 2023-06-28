#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *fp_sensor_map = fopen("room_sensor.map", "r");
    char line[11];
    memset(line, 0, 11);

    while (fgets(line, sizeof(line), fp_sensor_map) != NULL)
    {
        static int i;
        printf("%d %s\n", i, line);
    }

    // fclose(fp_sensor_map);

    return 0;
}