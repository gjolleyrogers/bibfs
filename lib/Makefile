.include "../share/mk/top.mk"

SRC += lib/lex.c
SRC += lib/bib.c
SRC += lib/refactor.c
SRC += lib/find.c
SRC += lib/merge.c
SRC += lib/cull.c
SRC += lib/free.c
SRC += lib/parser.c
SRC += lib/tex.c

PARSER += lib/parser.sid

LIB         += libbib
SYMS.libbib += lib/libbib.syms

# apparently a default: clause is not enough to satisfy -Weverything
.if ${CC:T:Mclang}
CFLAGS.lib/lex.c += -Wno-switch-enum
.endif

# int to char conversion for tolower()
.if ${CC:T:Mclang}
CFLAGS.lib/refactor.c += -Wno-conversion
.endif

# t.e - t.s where e > s
.if ${CC:T:Mclang}
CFLAGS.lib/parser.c += -Wno-sign-conversion
.endif

# SID generates fall-throughs which we cannot control
.if ${CC:T:Mclang}
CFLAGS.lib/parser.c += -Wno-switch-enum
.endif

.for src in ${SRC:Mlib/*.c} ${SRC:Mout/*.c}
${BUILD}/lib/libbib.o:    ${BUILD}/${src:R}.o
${BUILD}/lib/libbib.opic: ${BUILD}/${src:R}.opic
.endfor

