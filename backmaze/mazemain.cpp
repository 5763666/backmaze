#include <stdio.h>
#include <stdlib.h>
#define MAZE_SIZE 10

typedef struct {
	short r;
	short c;
} element;

typedef struct stack {
	element* data;
	int capacity;
	int top;
} StackType;

int back = 0;
element here = { 1,0 }, entry = { 1,0 };

void init_stack(StackType* s) {
	s->capacity = 1;
	s->top = -1;
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

int empty(StackType* s) {
	return s->top == -1;
}

int full(StackType* s) {
	return s->top == s->capacity - 1;
}

char maze[MAZE_SIZE][MAZE_SIZE] = {
		{'1','1','1','1','1','1','1','1','1','1'},
		{'e','1','0','1','0','0','0','1','0','1'},
		{'0','0','0','1','0','0','0','1','0','1'},
		{'0','1','0','0','0','1','1','0','0','1'},
		{'1','0','0','0','1','0','0','0','0','1'},
		{'1','0','0','0','1','0','0','0','0','1'},
		{'1','0','0','0','0','0','1','0','1','1'},
		{'1','0','1','1','1','0','1','1','0','1'},
		{'1','1','0','0','0','0','0','0','0','x'},
		{'1','1','1','1','1','1','1','1','1','1'}
};

void push(StackType* s, element value) {
	if (full(s)) {
		s->capacity *= 2;
		void* tmp = realloc(s->data, s->capacity * sizeof(element));
		if (tmp != NULL)
			s->data = (element*)tmp;
	}
	if (s->data != NULL)
		s->data[++s->top] = value;
}

bool is_empty(StackType* s) {
	if (empty(s))
		printf("Error: Stack is empty\n");
	return 0;
}

element pop(StackType* s) {
	if (empty(s))
		is_empty(s);
	return s->data[s->top--];
}

// 위치를 스택에 삽입
void push_loc(StackType* s, int r, int c) {
	if (r < 0 || c < 0)
		return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

// 미로를 화면에 출력한다.
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
	printf("------------\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}

int main(void) {
	int r, c;
	StackType s;
	init_stack(&s);
	here = entry;
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		maze_print(maze);
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);
		if (is_empty(&s)) {
			printf("fail\n");
			return 0;
		}
		else
			here = pop(&s);
		back++;
	}
	printf("------------\n");
	printf("Success\n");
	printf("Back count: %d", back);
	return 0;
}