#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task_term_index.h"

#define MAX_PAGES 20

void print_menu(void) {
    printf("\n========================================\n");
    printf("           TERM INDEX SYSTEM\n");
    printf("========================================\n");
    printf("1. Create hash table\n");
    printf("2. Insert term\n");
    printf("3. Insert subterm\n");
    printf("4. Insert subsubterm\n");
    printf("5. Remove term\n");
    printf("6. Remove subterm\n");
    printf("7. Remove subsubterm\n");
    printf("8. Edit term\n");
    printf("9. Edit subterm\n");
    printf("10. Edit subsubterm\n");
    printf("11. Find term by subterm\n");
    printf("12. Find subterm by term\n");
    printf("13. Show all\n");
    printf("14. Sort subterms by name (in term)\n");
    printf("15. Sort subterms by first page (in term)\n");
    printf("16. Exit\n");
    printf("========================================\n");
    printf("Choose option: ");
}

unsigned short* read_pages(short *count) {
    printf("Enter number of pages (max %d): ", MAX_PAGES);
    scanf("%hd", count);
    
    if (*count <= 0 || *count > MAX_PAGES) {
        printf("Invalid page count\n");
        return NULL;
    }
    
    unsigned short *pages = malloc(*count * sizeof(unsigned short));
    if (pages == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    
    printf("Enter %hd page numbers: ", *count);
    for (int i = 0; i < *count; i++) {
        scanf("%hu", &pages[i]);
    }
    
    return pages;
}

int main(void) {
    HashTable *ht = NULL;
    int choice;
    char term_name[100];
    char sub_name[100];
    char subsub_name[100];
    unsigned short *pages = NULL;
    short pages_count;
    int result;
    
    while (1) {
        print_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // Create hash table
                if (ht != NULL) {
                    printf("Hash table already exists. Freeing old one...\n");
                    hash_table_free(ht);
                }
                ht = hash_table_create(101);
                if (ht == NULL) {
                    printf("Failed to create hash table\n");
                } else {
                    printf("Hash table created successfully\n");
                }
                break;
                
            case 2: // Insert term
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                pages = read_pages(&pages_count);
                if (pages == NULL) break;
                result = hash_table_insert_term(ht, term_name, pages, pages_count);
                free(pages);
                break;
                
            case 3: // Insert subterm
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                printf("Enter subterm name: ");
                scanf("%s", sub_name);
                pages = read_pages(&pages_count);
                if (pages == NULL) break;
                result = hash_table_insert_sub_term(ht, term_name, sub_name, pages, pages_count);
                free(pages);
                break;
                
            case 4: // Insert subsubterm
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                printf("Enter subterm name: ");
                scanf("%s", sub_name);
                printf("Enter subsubterm name: ");
                scanf("%s", subsub_name);
                pages = read_pages(&pages_count);
                if (pages == NULL) break;
                result = hash_table_insert_sub_sub_term(ht, term_name, sub_name, subsub_name, pages, pages_count);
                free(pages);
                break;
                
            case 5: // Remove term
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                hash_table_remove_term(ht, term_name);
                break;
                
            case 6: // Remove subterm
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                printf("Enter subterm name: ");
                scanf("%s", sub_name);
                hash_table_remove_sub_term(ht, term_name, sub_name);
                break;
                
            case 7: // Remove subsubterm
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                printf("Enter subterm name: ");
                scanf("%s", sub_name);
                printf("Enter subsubterm name: ");
                scanf("%s", subsub_name);
                hash_table_remove_sub_sub_term(ht, term_name, sub_name, subsub_name);
                break;
                
            case 8: // Edit term
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                pages = read_pages(&pages_count);
                if (pages == NULL) break;
                result = hash_table_edit_term(ht, term_name, pages, pages_count);
                free(pages);
                break;
                
            case 9: // Edit subterm
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                printf("Enter subterm name: ");
                scanf("%s", sub_name);
                pages = read_pages(&pages_count);
                if (pages == NULL) break;
                result = hash_table_edit_sub_term(ht, term_name, sub_name, pages, pages_count);
                free(pages);
                break;
                
            case 10: // Edit subsubterm
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                printf("Enter subterm name: ");
                scanf("%s", sub_name);
                printf("Enter subsubterm name: ");
                scanf("%s", subsub_name);
                pages = read_pages(&pages_count);
                if (pages == NULL) break;
                result = hash_table_edit_sub_sub_term(ht, term_name, sub_name, subsub_name, pages, pages_count);
                free(pages);
                break;
                
            case 11: // Find term by subterm
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter subterm name to search: ");
                scanf("%s", sub_name);
                hash_table_find_term_by_sub_term(ht, sub_name);
                break;
                
            case 12: // Find subterm by term
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                hash_table_find_sub_term_by_term(ht, term_name);
                break;
                
            case 13: // Show all
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                hash_table_show(ht);
                break;
                
            case 14: // Sort subterms by name
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                sort_subterms_by_name(ht, term_name);
                break;
                
            case 15: // Sort subterms by pages
                if (ht == NULL) {
                    printf("Error: hash table not created\n");
                    break;
                }
                printf("Enter term name: ");
                scanf("%s", term_name);
                sort_subterms_by_pages(ht, term_name);
                break;

            case 16: // Exit
                if (ht != NULL) {
                    hash_table_free(ht);
                }
                printf("Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
    
    return 0;
}