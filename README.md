<div align="center">
  <h1>Term Index System</h1>
  <p>Система предметного указателя на C с использованием хэш-таблицы</p>
</div>

**Автор:** учебный проект по теме *"Хэширование"*

Лёгкая система индексации терминов на языке C с использованием хэш-таблицы. Поддерживает иерархическое хранение терминов, подтерминов и подподтерминов с номерами страниц.


## Обзор

Проект реализует **систему предметного указателя** для создания и управления индексами. Использует хэш-таблицу для быстрого поиска терминов и поддерживает трёхуровневую иерархию:

<div align="center">
   <h3>Термин → Подтермин → Подподтермин</h3>
</div>


Каждый уровень хранит:

- Имя (строка)
- Массив номеров страниц (`unsigned short`)
- Ссылки на дочерние элементы

## Возможности

- ✅ **Хэш-таблица** для поиска терминов за O(1) в среднем
- ✅ **CRUD операции** для всех уровней
- ✅ **Каскадное удаление** (при удалении термина удаляются все его подтермины и подподтермины)
- ✅ **Поиск**:
  - Поиск терминов по имени подтермина
  - Поиск подтерминов и подподтерминов по имени термина
- ✅ **Сортировка подтерминов** (по алфавиту или по первому номеру страницы)
- ✅ **Интерактивное консольное меню**
- ✅ **Безопасное управление памятью**

## Структура проекта
```
├── task_main.c
├── task_term_index.c
└── task_term_index.h
```
**Примечание:** Другие файлы в репозитории (если есть) являются тестовыми или временными и не входят в состав рабочего кода.

## 🛠️ Компиляция

Скомпилируйте проект с помощью GCC:

```bash
gcc -o term_index task_main.c task_term_index.c
```
Запустите исполняемый файл:
```bash
./term_index
```

## Использование

После запуска программы отображается интерактивное меню:
```text
============================================
           TERM INDEX SYSTEM
============================================
1. Create hash table
2. Insert term
3. Insert subterm
4. Insert subsubterm
5. Remove term
6. Remove subterm
7. Remove subsubterm
8. Edit term
9. Edit subterm
10. Edit subsubterm
11. Find term by subterm
12. Find subterm by term
13. Show all
14. Sort subterms by name (in term)
15. Sort subterms by first page (in term)
16. Exit
============================================
```

### Типичный сценарий работы
1. Создать хэш-таблицу (пункт 1) — инициализировать систему индексов
2. Добавить термины (пункт 2) — добавить основные термины с номерами страниц
3. Добавить подтермины (пункт 3) — добавить подтермины к существующим терминам
4. Добавить подподтермины (пункт 4) — добавить третий уровень вложенности
5. Показать всё (пункт 13) — отобразить полный указатель

```text
========================================
           TERM INDEX SYSTEM
========================================

Choose option: 1
Hash table created successfully

Choose option: 2
Enter term name: Programming
Enter number of pages (max 20): 3
Enter 3 page numbers: 1 5 10
Termin Programming appended

Choose option: 3
Enter term name: Programming
Enter subterm name: Algorithms
Enter number of pages (max 20): 3
Enter 3 page numbers: 5 6 7
Subterm 'Algorithms' added to term 'Programming'

Choose option: 4
Enter term name: Programming
Enter subterm name: Algorithms
Enter subsubterm name: Sorting
Enter number of pages (max 20): 2
Enter 2 page numbers: 10 11
Subsubterm 'Sorting' added to subterm 'Algorithms'

Choose option: 13

========================================
           TERM INDEX
========================================

[1] TERM: Programming [pages: 1, 5, 10]
    1.1 SUBTERM: Algorithms [pages: 5, 6, 7]
        1.1.1 SUBSUBTERM: Sorting [pages: 10, 11]

========================================
STATISTICS:
  Terms: 1
  Subterms: 1
  Subsubterms: 1
========================================
```

## Структуры данных
```c
// Подподтермин (3-й уровень)
typedef struct SubSubTerm {
    char *name;                 // имя подподтермина
    unsigned short *pages;      // массив номеров страниц
    short pages_count;          // количество страниц
    struct SubSubTerm *next;    // следующий подподтермин в списке
} SubSubTerm;

// Подтермин (2-й уровень)
typedef struct SubTerm {
    char *name;                 // имя подтермина
    unsigned short *pages;      // массив номеров страниц
    short pages_count;          // количество страниц
    SubSubTerm *subsub_list;    // список подподтерминов
    struct SubTerm *next;       // следующий подтермин в списке
} SubTerm;

// Термин (1-й уровень)
typedef struct Term {
    char *name;                 // имя термина (уникально)
    unsigned short *pages;      // массив номеров страниц
    short pages_count;          // количество страниц
    SubTerm *sub_list;          // список подтерминов
    struct Term *next;          // следующий термин в цепочке хэш-таблицы
} Term;

// Хэш-таблица
typedef struct HashTable {
    Term **entries;             // массив указателей на Term (размер 101)
    int size;                   // размер хэш-таблицы
} HashTable;
```

## Операции

### ➕ Добавление

| Функция                          | Описание                     |
|---------------------------------|------------------------------|
| hash_table_insert_term          | Добавить термин              |
| hash_table_insert_sub_term      | Добавить подтермин           |
| hash_table_insert_sub_sub_term  | Добавить подподтермин        |

---

### ❌ Удаление

| Функция                          | Описание                              |
|---------------------------------|---------------------------------------|
| hash_table_remove_term          | Удалить термин (каскадно)              |
| hash_table_remove_sub_term      | Удалить подтермин                      |
| hash_table_remove_sub_sub_term  | Удалить подподтермин                   |

---

### ✏️ Редактирование

| Функция                         | Описание                                |
|--------------------------------|-----------------------------------------|
| hash_table_edit_term           | Изменить страницы термина                |
| hash_table_edit_sub_term       | Изменить страницы подтермина             |
| hash_table_edit_sub_sub_term   | Изменить страницы подподтермина          |

---

### 🔎 Поиск

| Функция                               | Описание                                      |
|--------------------------------------|-----------------------------------------------|
| hash_table_find_term_by_sub_term     | Найти термины, содержащие подтермин            |
| hash_table_find_sub_term_by_term     | Найти подтермины в термине                     |

---

### 🔤 Сортировка

| Функция                    | Описание                                      |
|---------------------------|-----------------------------------------------|
| sort_subterms_by_name     | Сортировка подтерминов по алфавиту            |
| sort_subterms_by_pages    | Сортировка подтерминов по первому номеру страницы |

---

### 🧹 Отображение и очистка

| Функция           | Описание                         |
|------------------|----------------------------------|
| hash_table_show  | Вывод всего указателя            |
| hash_table_free  | Освобождение всей памяти         |
