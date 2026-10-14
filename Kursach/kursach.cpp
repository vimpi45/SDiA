#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100 // Максимальное количество вершин в графе

// Структура для представления узла односвязного списка смежности
struct Node {
    int vertex; // Номер входящей вершины (предшественника)
    Node* next; // Указатель на следующий узел списка
};

// Массив списков смежности для хранения транспонированного графа G^T
Node* adj_rev[MAX_VERTICES];

// Функция создания нового узла списка из статического пула
Node* createNode(int v) {
    Node* newNode = new Node; // Взятие адреса следующего свободного узла из пула
    newNode->vertex = v; // Запись номера вершины
    newNode->next = NULL; // Инициализация указателя на следующий узел
    return newNode;
}

// Функция добавления обратной дуги (u -> v) в список смежности вершины v
void addEdgeRev(int u, int v) {
    Node* newNode = createNode(u); // Создаем узел для вершины u
    newNode->next = adj_rev[v]; // Вставляем узел в начало списка вершины v
    adj_rev[v] = newNode; // Обновляем головной узел списка
}

int main() {
    int N, v_target, L; // N - число вершин, v_target - целевая вершина, L - длина пути

    // Инициализация массива списков смежности нулевыми указателями
    for (int i = 0; i < MAX_VERTICES; i++)
        adj_rev[i] = NULL;

    // Чтение входных данных из текстового файла
    FILE* fin = fopen("input.txt", "r");

    if (!fin) {
        printf("Ошибка: Не удалось открыть файл input.txt\n");
        return 1;
    }

    // Считывание количества вершин, целевой вершины и длины пути L
    if (fscanf(fin, "%d %d %d", &N, &v_target, &L) != 3) {
        printf("Ошибка: Неверный формат заголовочных данных в input.txt\n");
        fclose(fin);
        return 1;
    }

    // Построение транспонированного графа: считывание дуг (u, v)
    int u, v;
    while (fscanf(fin, "%d %d", &u, &v) == 2)
        if (u >= 0 && u < N && v >= 0 && v < N)
            addEdgeRev(u, v); // Сохраняем дугу u -> v в список вершины v

    fclose(fin); // Закрытие входного файла

    // Структуры для хранения уровней обхода BFS
    int current_layer[MAX_VERTICES]; // Массив вершин текущего уровня обхода
    int current_size = 0;             // Количество вершин на текущем уровне

    int next_layer[MAX_VERTICES];    // Буферный массив для формирования следующего уровня
    int next_size = 0;                // Количество вершин на следующем уровне

    int visited_in_step[MAX_VERTICES]; // Массив флагов для предотвращения дублирования вершин на шаге

    // Помещаем целевую вершину v_target на начальный уровень
    current_layer[0] = v_target;
    current_size = 1;

    // Послойный поиск в ширину (BFS) по обратным дугам на глубину L
    for (int step = 1; step <= L; step++) {
        next_size = 0; // Сброс размера следующего уровня

        // Сброс массива посещений перед началом формирования нового уровня
        for (int i = 0; i < N; i++)
            visited_in_step[i] = 0;

        // Обход всех вершин текущего уровня и поиск их предшественников
        for (int i = 0; i < current_size; i++) {
            int curr_v = current_layer[i];
            Node* temp = adj_rev[curr_v]; // Получение списка предшественников вершины curr_v

            // Проход по списку смежности транспонированного графа
            while (temp != NULL) {
                int predecessor = temp->vertex;
                // Добавляем вершину, только если она еще не была добавлена на данном шаге
                if (!visited_in_step[predecessor]) {
                    visited_in_step[predecessor] = 1;      // Отмечаем вершину как посещенную
                    next_layer[next_size++] = predecessor; // Добавляем в следующий уровень
                }
                temp = temp->next; // Переход к следующему предшественнику
            }
        }

        // Переход к следующему уровню (копирование из next_layer в current_layer)
        current_size = next_size;
        for (int i = 0; i < current_size; i++)
            current_layer[i] = next_layer[i];
    
        // Прерывание обхода, если на текущем шаге не найдено ни одной вершины
        if (current_size == 0)
            break;
        
    }

    // Сохранение итогового результата (вершины L-го уровня)
    int result[MAX_VERTICES];
    int result_count = current_size;

    for (int i = 0; i < result_count; i++)
        result[i] = current_layer[i];

    // Запись результатов работы в файл output.txt и консоль
    FILE* fout = fopen("output.txt", "w");
   
    // Вывод результатов при наличии найденных вершин
    if (result_count > 0) {
        printf("Вершины на расстоянии L=%d от v_target=%d:\n", L, v_target);
        fprintf(fout, "Вершины: ");
        for (int i = 0; i < result_count; i++) {
            printf("%d ", result[i]);
            fprintf(fout, "%d ", result[i]);
        }
        printf("\n");
        fprintf(fout, "\n");
    } else { // Вывод сообщения, если подходящие вершины не найдены
        printf("Вершины, от которых существует путь длины L=%d к v_target=%d, не найдены.\n", L, v_target);
        fprintf(fout, "Вершины не найдены\n");
    }

    fclose(fout); // Закрытие выходного файла
  
    return 0;
}