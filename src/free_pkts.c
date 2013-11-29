#include "proxysql.h"

#define NUMPKTS 128

pkt *mypkt_alloc(mysql_session_t *sess) {
	pkt *p;
	p=g_trash_stack_pop(&sess->handler_thread->free_pkts.stack);
	if (p) {
		debug_print("%p\n", p);
		return p;
	}
	pkt *m;
	if ((m=malloc(sizeof(pkt)*NUMPKTS))==NULL) { exit(EXIT_FAILURE); }
	g_ptr_array_add(sess->handler_thread->free_pkts.blocks,m);
	int i;
	for (i=0; i<NUMPKTS; i++) {
		pkt *n=m+i;
		g_trash_stack_push(&sess->handler_thread->free_pkts.stack,n);
	}
	p=g_trash_stack_pop(&sess->handler_thread->free_pkts.stack);
	debug_print("%p\n", p);
	return p;
}

void mypkt_free(pkt *p, mysql_session_t *sess, int free_data) {
	if (free_data) {
		g_slice_free1(p->length, p->data);
	}
	debug_print("%p\n", p);
	g_trash_stack_push(&sess->handler_thread->free_pkts.stack,p);
}
