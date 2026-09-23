PArvABB remover(PArvABB a, int x) {
	PArvABB t,pai;
	if(a==NULL) {
		return NULL;
	}
	if(x<a->info) {
		a->esq1=remover(a->esq1, x);
	} else if(x>a->info) {
		a->dir1=remover(a->dir1, x);
	} else {
		if(a->esq1==NULL && a->dir1==NULL) {
			free(a);
			return NULL;
		}
		if(a->dir1==NULL) {
			t=a->esq1;
			free(a);
			return t;
		}
		if(a->esq1==NULL) {
			t=a->dir1;
			free(a);
			return t;
		}
		pai=a;
		t=a->esq1;
		while(t->dir1!=NULL) {
			pai=t;
			t=t->dir1;
		}
		a->info=t->info;
		if(pai==a) {
			pai->esq1=t->esq1;
		} else {
			pai->dir1=t->esq1;
		}
		free(t);
		return a;
	}
}
