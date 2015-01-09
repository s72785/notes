#ifndef _ACCLIST_CLASS_H
# define _ACCLIST_CLASS_H

/*
table of certain size
[][][][]
will be filled by residue-class/hash-function
1st elm can be entered as a 1-elm list(acc1,NULL)
2nd elm on same residue-class result has to be appended on list(acc1,(acc2,NULL))
as hash function simple modulo is sufficient, const operand should be theusual amount of users, so maybe the 4-char as of before => 10.000
*/

typedef struct list_t {
  konto* acc;
  list_t* nxt;
} acclist;

int acclist_append(acclist* ) {
  return 0;
}

int acclist_push() {
  return 0;
}

int acclist_insertsorted() {
  return 0;
}

acclist* acclist_pop() {
}

acclist* acclist_getelm(int accno) {
}

#endif // _ACCLIST_CLASS_H
