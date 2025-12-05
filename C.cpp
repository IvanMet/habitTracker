#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>


#define FILENAME "habits.txt"

typedef struct {
    int id;
    char name[50];
    char description[200];
    int completed_days;
    int total_days;
    char category[50];
} Habit;

Habit habits[100];
int habit_count = 0;
int next_id = 1;

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void add_habit() {
    if (habit_count >= 100) {
        printf("Достигнуто максимальное количество привычек!\n");
        return;
    }

    Habit new_habit;
    new_habit.id = next_id++;
    new_habit.completed_days = 0;
    new_habit.total_days = 0;

    printf("Введите название привычки: ");
    if (fgets(new_habit.name, 50, stdin) == NULL) {
        printf("Ошибка ввода!\n");
        return;
    }
    new_habit.name[strcspn(new_habit.name, "\n")] = '\0';

    printf("Введите описание привычки: ");
    if (fgets(new_habit.description, 200, stdin) == NULL) {
        printf("Ошибка ввода!\n");
        return;
    }
    new_habit.description[strcspn(new_habit.description, "\n")] = '\0';

    printf("Введите категорию привычки: ");
    if (fgets(new_habit.category, 50, stdin) == NULL) {
        printf("Ошибка ввода!\n");
        return;
    }
    new_habit.category[strcspn(new_habit.category, "\n")] = '\0';

    habits[habit_count++] = new_habit;
    printf("Привычка добавлена успешно! ID: %d\n", new_habit.id);
}

void remove_habit() {
    if (habit_count == 0) {
        printf("Нет привычек для удаления!\n");
        return;
    }

    int id;
    printf("Введите ID привычки для удаления: ");
    if (scanf("%d", &id) != 1) {
        printf("Ошибка ввода ID!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    int found_index = -1;
    for (int i = 0; i < habit_count; i++) {
        if (habits[i].id == id) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("Привычка с ID %d не найдена!\n", id);
        return;
    }

    printf("Вы уверены, что хотите удалить привычку '%s'? (y/n): ", habits[found_index].name);
    char confirm;
    if (scanf("%c", &confirm) != 1) {
        printf("Ошибка ввода!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = found_index; i < habit_count - 1; i++) {
            habits[i] = habits[i + 1];
        }
        habit_count--;
        printf("Привычка удалена успешно!\n");
    }
    else {
        printf("Удаление отменено.\n");
    }
}

void mark_habit_completed() {
    if (habit_count == 0) {
        printf("Нет привычек для отметки!\n");
        return;
    }

    int id;
    printf("Введите ID привычки для отметки: ");
    if (scanf("%d", &id) != 1) {
        printf("Ошибка ввода ID!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    for (int i = 0; i < habit_count; i++) {
        if (habits[i].id == id) {
            habits[i].completed_days++;
            habits[i].total_days++;
            printf("Привычка '%s' отмечена как выполненная!\n", habits[i].name);
            return;
        }
    }

    printf("Привычка с ID %d не найдена!\n", id);
}

void print_habits_sorted_by_name() {
    if (habit_count == 0) {
        printf("Нет привычек для отображения!\n");
        return;
    }

    Habit sorted_habits[100];
    memcpy(sorted_habits, habits, sizeof(Habit) * habit_count);

    for (int i = 0; i < habit_count - 1; i++) {
        for (int j = i + 1; j < habit_count; j++) {
            if (strcmp(sorted_habits[i].name, sorted_habits[j].name) > 0) {
                Habit temp = sorted_habits[i];
                sorted_habits[i] = sorted_habits[j];
                sorted_habits[j] = temp;
            }
        }
    }

    printf("\n=== ПРИВЫЧКИ (отсортировано по названию) ===\n");
    for (int i = 0; i < habit_count; i++) {
        float percentage = sorted_habits[i].total_days > 0 ?
            (float)sorted_habits[i].completed_days / sorted_habits[i].total_days * 100 : 0;

        printf("ID: %d\n", sorted_habits[i].id);
        printf("Название: %s\n", sorted_habits[i].name);
        printf("Описание: %s\n", sorted_habits[i].description);
        printf("Категория: %s\n", sorted_habits[i].category);
        printf("Выполнено дней: %d/%d\n", sorted_habits[i].completed_days, sorted_habits[i].total_days);
        printf("Процент выполнения: %.1f%%\n", percentage);
        printf("----------------------------------------\n");
    }
}

void print_habits_sorted_by_percentage() {
    if (habit_count == 0) {
        printf("Нет привычек для отображения!\n");
        return;
    }

    Habit sorted_habits[100];
    memcpy(sorted_habits, habits, sizeof(Habit) * habit_count);

    for (int i = 0; i < habit_count - 1; i++) {
        for (int j = i + 1; j < habit_count; j++) {
            float perc_i = sorted_habits[i].total_days > 0 ?
                (float)sorted_habits[i].completed_days / sorted_habits[i].total_days : 0;
            float perc_j = sorted_habits[j].total_days > 0 ?
                (float)sorted_habits[j].completed_days / sorted_habits[j].total_days : 0;

            if (perc_i < perc_j) {
                Habit temp = sorted_habits[i];
                sorted_habits[i] = sorted_habits[j];
                sorted_habits[j] = temp;
            }
        }
    }

    printf("\n=== ПРИВЫЧКИ (отсортировано по проценту выполнения) ===\n");
    for (int i = 0; i < habit_count; i++) {
        float percentage = sorted_habits[i].total_days > 0 ?
            (float)sorted_habits[i].completed_days / sorted_habits[i].total_days * 100 : 0;

        printf("ID: %d\n", sorted_habits[i].id);
        printf("Название: %s\n", sorted_habits[i].name);
        printf("Описание: %s\n", sorted_habits[i].description);
        printf("Категория: %s\n", sorted_habits[i].category);
        printf("Выполнено дней: %d/%d\n", sorted_habits[i].completed_days, sorted_habits[i].total_days);
        printf("Процент выполнения: %.1f%%\n", percentage);
        printf("----------------------------------------\n");
    }
}

void print_habits() {
    if (habit_count == 0) {
        printf("Нет привычек для отображения!\n");
        return;
    }

    int choice;
    printf("\nВыберите способ сортировки:\n");
    printf("1 - По названию\n");
    printf("2 - По проценту выполнения\n");
    printf("Ваш выбор: ");
    if (scanf("%d", &choice) != 1) {
        printf("Ошибка ввода!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    switch (choice) {
    case 1:
        print_habits_sorted_by_name();
        break;
    case 2:
        print_habits_sorted_by_percentage();
        break;
    default:
        printf("Неверный выбор!\n");
        break;
    }
}

void save_habits_to_file() {
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла для записи!\n");
        return;
    }

    fprintf(file, "%d\n", next_id);
    fprintf(file, "%d\n", habit_count);

    for (int i = 0; i < habit_count; i++) {
        fprintf(file, "%d\n", habits[i].id);
        fprintf(file, "%s\n", habits[i].name);
        fprintf(file, "%s\n", habits[i].description);
        fprintf(file, "%s\n", habits[i].category);
        fprintf(file, "%d\n", habits[i].completed_days);
        fprintf(file, "%d\n", habits[i].total_days);
    }

    fclose(file);
    printf("Данные успешно сохранены в файл '%s'!\n", FILENAME);
}

void load_habits_from_file() {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Файл с данными не найден. Будет создан новый при сохранении.\n");
        return;
    }
    if (fscanf(file, "%d", &next_id) != 1) {
        printf("Ошибка чтения next_id из файла!\n");
        fclose(file);
        return;
    }

    if (fscanf(file, "%d", &habit_count) != 1) {
        printf("Ошибка чтения habit_count из файла!\n");
        fclose(file);
        return;
    }
    clear_input_buffer();

    for (int i = 0; i < habit_count; i++) {
        if (fscanf(file, "%d", &habits[i].id) != 1) {
            printf("Ошибка чтения ID привычки %d из файла!\n", i);
            break;
        }
        clear_input_buffer();

        if (fgets(habits[i].name, 50, file) == NULL) {
            printf("Ошибка чтения названия привычки %d!\n", i);
            break;
        }
        habits[i].name[strcspn(habits[i].name, "\n")] = '\0';

        if (fgets(habits[i].description, 200, file) == NULL) {
            printf("Ошибка чтения описания привычки %d!\n", i);
            break;
        }
        habits[i].description[strcspn(habits[i].description, "\n")] = '\0';

        if (fgets(habits[i].category, 50, file) == NULL) {
            printf("Ошибка чтения категории привычки %d!\n", i);
            break;
        }
        habits[i].category[strcspn(habits[i].category, "\n")] = '\0';

        if (fscanf(file, "%d", &habits[i].completed_days) != 1) {
            printf("Ошибка чтения completed_days для привычки %d!\n", i);
            break;
        }

        if (fscanf(file, "%d", &habits[i].total_days) != 1) {
            printf("Ошибка чтения total_days для привычки %d!\n", i);
            break;
        }
        clear_input_buffer();
    }

    fclose(file);
    printf("Данные успешно загружены из файла '%s'!\n", FILENAME);
}

void print_menu() {
    printf("\n=== ТРЕКЕР ПРИВЫЧЕК ===\n");
    printf("1 - Добавить привычку\n");
    printf("2 - Удалить привычку\n");
    printf("3 - Отметить привычку как выполненную\n");
    printf("4 - Просмотр привычек и статистики\n");
    printf("5 - Сохранить данные\n");
    printf("6 - Загрузить данные\n");
    printf("9 - Выход\n");
    printf("Выберите действие: ");
}

int main() {
    // Установка русской локали
    setlocale(LC_ALL, "Russian");

    load_habits_from_file();

    int choice;

    do {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода! Пожалуйста, введите число.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
        case 1:
            add_habit();
            break;
        case 2:
            remove_habit();
            break;
        case 3:
            mark_habit_completed();
            break;
        case 4:
            print_habits();
            break;
        case 5:
            save_habits_to_file();
            break;
        case 6:
            load_habits_from_file();
            break;
        case 9:
            printf("Выход из программы...\n");
            break;
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            break;
        }
    } while (choice != 9);

    return 0;
}