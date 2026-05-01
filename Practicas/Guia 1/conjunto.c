#include <stdio.h>
#include <glib.h>

int main() {
    // Crear un conjunto
    GHashTable *set = g_hash_table_new(g_direct_hash, g_direct_equal);

    // Añadir elementos al conjunto
    int element1 = 1, element2 = 2, element3 = 3;
    g_hash_table_insert(set, GINT_TO_POINTER(element1), GINT_TO_POINTER(element1));
    g_hash_table_insert(set, GINT_TO_POINTER(element2), GINT_TO_POINTER(element2));
    g_hash_table_insert(set, GINT_TO_POINTER(element3), GINT_TO_POINTER(element3));

    // Verificar si un elemento está en el conjunto
    int query_element = 2;
    if (g_hash_table_contains(set, GINT_TO_POINTER(query_element))) {
        printf("%d está en el conjunto.\n", query_element);
    } else {
        printf("%d no está en el conjunto.\n", query_element);
    }

    // Iterar sobre los elementos del conjunto
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, set);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        printf("Elemento: %d\n", GPOINTER_TO_INT(key));
    }

    // Liberar la memoria utilizada por el conjunto
    g_hash_table_destroy(set);

    return 0;
}
