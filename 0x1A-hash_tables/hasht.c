#include "hash_tables.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};


static hash_node_t *hti(const char *k, const char *v)
{
	hash_node_t *i = malloc(sizeof(hash_node_t));

	i->key = strdup(k);
	i->value = strdup(v);
	return(i);
}

hash_table_t *ht_new()
{
	hash_table_t *ht = malloc(sizeof(hash_table_t));

	ht->size = 53;
	ht->count = 0;
	ht->array = calloc((size_t)ht->size, sizeof(hash_node_t));
}

static void ht_del_node(hash_node_t *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void ht_del_ht(hash_table_t *ht)
{
	int i = 0;
	hash_node_t *node;

	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		if (node != NULL)
		{
			ht_del_node(node);
		}
	}
	free(ht->array);
	free(ht);
}

static int ht_hash(const char *s, const int a, const int m)
{
	long hash = 0;
	const int len = strlen(s);
	int i = 0;

	for (i = 0; i < len; i++)
	{
		hash += (long)pow(a, len - (i + 1)) * s[i];
		hash = hash % m;
	}
	return (hash);
}
static int ht_get_hash(const char *s, const int nbuckets, const int attempt)
{
	const int hash_a = ht_hash(s, HT_PRIME_1, nbuckets);
	const int hash_b = ht_hash(s, HT_PRIME_2, nbuckets);

	return (hash_a +(attempt * (hash_b + 1)) % nbuckets);
}

void ht_insert(hash_table_t* ht, const char* key, const char* value)
{
	const int load = ht->count * 100 / ht->size;
	ht_item* item = ht_new_item(key, value);
	int index = ht_get_hash(item->key, ht->size, 0);
	ht_item* cur_item = ht->items[index];
	int i = 1;


	if (load > 70)
	{
		ht_resize_up(ht);
	}
	while (cur_item != NULL)
	{
		if (cur_item != &HT_DELETED_ITEM)
		{
			if (strcmp(cur_item->key, key) == 0)
			{
				ht_del_item(cur_item);
				ht->items[index] = item;
				return;
			}
		}
		index = ht_get_hash(item->key, ht->size, i);
		cur_item = ht->items[index];
		i++;
	}
	ht->items[index] = item;
	ht->count++;
}

char *ht_search(ht_hash_table* ht, const char* key)
{
	int index = ht_get_hash(key, ht->size, 0);
	ht_item* item = ht->items[index];
	int i = 1;

	while (item != NULL)
	{
		if (item != &HT_DELETED_ITEM)
		{
			if (strcmp(item->key, key) == 0)
			{
				return (item->value);
			}
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	return (NULL);
}

void ht_delete(hash_table_t* ht, const char* key) {
	const int load = ht->count * 100 / ht->size;
	int index = ht_get_hash(key, ht->size, 0);
	ht_item* item = ht->items[index];
	int i = 1;

	if (load < 10)
	{
		ht_resize_down(ht);
	}
	while (item != NULL)
	{
		if (item != &HT_DELETED_ITEM)
		{
			if (strcmp(item->key, key) == 0)
			{
				ht_del_item(item);
				ht->items[index] = &HT_DELETED_ITEM;
			}
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	ht->count--;
}

static void ht_resize(hash_table_t* ht, const int base_size) {
	if (base_size < HT_INITIAL_BASE_SIZE) {
		return;
	}
	hash_table_t* new_ht = ht_new_sized(base_size);
	for (int i = 0; i < ht->size; i++) {
		ht_item* item = ht->items[i];
		if (item != NULL && item != &HT_DELETED_ITEM) {
			ht_insert(new_ht, item->key, item->value);
		}
	}

	ht->base_size = new_ht->base_size;
	ht->count = new_ht->count;

	// To delete new_ht, we give it ht's size and items
	const int tmp_size = ht->size;
	ht->size = new_ht->size;
	new_ht->size = tmp_size;

	ht_item** tmp_items = ht->items;
	ht->items = new_ht->items;
	new_ht->items = tmp_items;

	ht_del_hash_table(new_ht);
}

static void ht_resize_up(ht_hash_table* ht) {
	const int new_size = ht->base_size * 2;
	ht_resize(ht, new_size);
}


static void ht_resize_down(ht_hash_table* ht) {
	const int new_size = ht->base_size / 2;
	ht_resize(ht, new_size);
}

int main()
{
	hash_table_t *ht = ht_new();
	ht_del_ht(ht);
}
