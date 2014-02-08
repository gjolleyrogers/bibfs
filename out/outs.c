#define _POSIX_SOURCE

#include <sys/types.h>
#include <sys/stat.h>

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <bib/bib.h>
#include <bib/out.h>

static size_t
readall(FILE *f, char *buf, size_t size)
{
	size_t n;

	n = 0;

	assert(f != NULL);
	assert(buf != NULL);
	assert(size > 0);

	while (n < size) {
		int r;

		r = fread(buf + n, 1, size - n, f);
		if (r == -1) {
			return 0;
		}

		if (r == 0) {
			break;
		}

		n += r;
	}

	buf[n] = '\0';

	return n;
}

char *
bib_outs(const struct bib_entry *e,
	void (*out)(FILE *f, const struct bib_entry *, int))
{
	struct stat st;
	FILE *f;
	char *s;

	assert(e != NULL);
	assert(out != NULL);

	f = tmpfile();
	if (f == NULL) {
		return NULL;
	}

	/* TODO: error-check */
	out(f, e, 0);

	fflush(f);

	/* TODO: wouldn't need to fstat() if out() returns the number of bytes written */
	if (-1 == fstat(fileno(f), &st)) {
		fclose(f);
		return NULL;
	}

	s = malloc(st.st_size + 1);
	if (s == NULL) {
		fclose(f);
		return NULL;
	}

	rewind(f);

	if (0 == readall(f, s, st.st_size + 1)) {
		fclose(f);
		free(s);
		return NULL;
	}

	fclose(f);

	return s;
}

