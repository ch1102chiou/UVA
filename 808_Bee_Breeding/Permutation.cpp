#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CYCLE 57
#define min(x,y) (((x) > (y)) ? (y):(x))
typedef struct _hexpos{
	int x;
	int y;
} hex_pos_t;

typedef struct hex{

} hex_t;

void gotpos(int pos, hex_pos_t *hex);

int cycles[59] = { 1, 7, 19, 37, 61, 91, 127, 169, 217, 271, 331, 397, 469, 547, 631, 721, 817, 919, 1027, 
  1141, 1261, 1387, 1519, 1657, 1801, 1951, 2107, 2269, 2437, 2611, 2791, 2977, 3169, 3367, 
  3571, 3781, 3997, 4219, 4447, 4681, 4921, 5167, 5419, 5677, 5941, 6211, 6487, 6769, 7057, 
  7351, 7651, 7957, 8269, 8587, 8911, 9241, 9577, 9919, 10001};

void gotpos(int pos, hex_pos_t *hex) {
	// binary search for cycles
	int max = MAX_CYCLE;
	int min = 0;
	int index = (max + min) / 2;
	int sidelen = 0;
	int offset = 0;
	int tmp;
	while (1) {
		if (pos >= cycles[index] && pos < cycles[index+1]) {
			hex->x = index;
			hex->y = 0;
			sidelen = index + 1;
			offset = pos - cycles[index];
			break;
		}
		else if(pos > cycles[index]){
			min = index + 1;
			index = (max + min) / 2;
		} else {
			max = index - 1;
			index = (max + min) / 2;
		}
	}
	if (offset > 0) {
		offset = offset - 1;
		hex->x++;
		hex->y--;
	}
	if (offset > 0) {
		tmp = offset >= sidelen - 1 ? sidelen - 1:offset;
		offset -= tmp;
		hex->y-=tmp;
	}
	if (offset > 0) {
		tmp = offset >= sidelen  ? sidelen:offset;
		offset -= tmp;
		hex->x-=tmp;
	}
	if (offset > 0) {
		tmp = offset >= sidelen  ? sidelen:offset;
		offset -= tmp;
		hex->x-=tmp;
		hex->y+=tmp;
	}
	if (offset > 0) {
		tmp = offset >= sidelen  ? sidelen:offset;
		offset -= tmp;
		hex->y+=tmp;
	}
	if (offset > 0) {
		tmp = offset >= sidelen  ? sidelen:offset;
		offset -= tmp;
		hex->x+=tmp;
	}
	if (offset > 0) {
		tmp = offset >= sidelen - 1 ? sidelen - 1:offset;
		offset -= tmp;
		hex->x+=tmp;
		hex->y-=tmp;
	}
	return;
}

int main (void) {
	int x,y, dis;
	hex_pos_t xhex;
	hex_pos_t yhex;
	hex_pos_t delta;
#if 0	
	for (int i = 1; i <= 10000; i++) {
		gotpos(i, &xhex);
		printf("id:%d hex x:%d y:%d\n", i, xhex.x, xhex.y);
	}
#endif
	scanf ("%d %d\n", &x, &y);	
	while (1) {
		if (x == 0 && y == 0)
			break;
		gotpos(x, &xhex);
		gotpos(y, &yhex);
		delta.x = yhex.x - xhex.x;
		delta.y = yhex.y - xhex.y;
		if (delta.x * delta.y >= 0) {
			dis = abs(delta.x) + abs(delta.y);
		} else {
			dis = abs(abs(delta.x) - abs(delta.y)) + min(abs(delta.x), abs(delta.y));
		}
		printf("The distance between cells %d and %d is %d.\n", x, y,dis);
		scanf ("%d %d\n", &x, &y);
	}
}
