MENU_SRC=menu.c
MOCK_SRC=mock.c
ALGOS_SRC=insertion_sort.c bubble_sort.c merge_sort.c quick_sort.c simple_bst.c rb_bst.c heap_sort.c
LIST_SRC=list.c
COMMON_SRC=common.c 
HEADERS=list.h common.h insertion_sort.h bubble_sort.h merge_sort.h quick_sort.h simple_bst.h rb_bst.h heap_sort.h

algos: $(MENU_SRC) $(LIST_SRC) $(COMMON_SRC) $(HEADERS) $(ALGOS_SRC) Makefile
	gcc -fstack-protector-all -o $@ $(MENU_SRC) $(LIST_SRC) $(COMMON_SRC) $(ALGOS_SRC) $(HEADERS) -lm

mock: $(MOCK_SRC) $(LIST_SRC) $(COMMON_SRC) $(HEADERS) $(ALGOS_SRC) Makefile
	gcc -fstack-protector-all -o $@ $(MOCK_SRC) $(LIST_SRC) $(COMMON_SRC) $(ALGOS_SRC) $(HEADERS) -lm

clean:
	rm -f algos mock
