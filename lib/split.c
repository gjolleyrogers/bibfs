#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <bib/bib.h>

int
bib_split(struct bib_field *f, const char *delim)
{
	struct bib_value *v, *w;
	char *s;

	assert(delim != NULL);

	/*
	 * This cuts off delim-seperated terms from each value string in turn,
	 * and pushes the remainder ahead, as a new node in the list. That new
	 * node is then inspected next, and remaining terms are split in the
	 * same manner.
	 */

	for (v = f->value; v != NULL; v = v->next) {
		s = v->text;

		s += strcspn(v->text, delim);
		if (*s == '\0') {
			continue;
		}

		*s = '\0';

		w = bib_new_value(s + 1);
		if (w == NULL) {
			return -1;
		}

		w->next = v->next;
		v->next = w;
	}

	return 0;
}
