#include <stdio.h>
#include <math.h>

#define C 64 // set cache size
#define B 16 // set block size
#define E 4  // set number of lines per set
#define m 32 // number of physical address bits
#define setMask 0x1 // set set mask

int hit = 0;
int miss = 0;
int time = 0;

int get_addr(int row, int col, int s_d) {
        int addr;
        if (s_d == 0) {
                addr = (row*4 + col)*4;
                return addr;
        }
        else {
                addr = 0x40 + (row*4 + col)*4;
                return addr;
        }
}

int get_set(int addr, int b) {
        int set;
        set = (addr >> b) & (setMask);
        return set;
}

int get_tag(int addr, int b, int s) {
        int tag;
        tag = addr >> (b+s);
        return tag;
}

void initCache(int set, int line, int valid[set][line], int timeArray[set][line]){
        int i,j;

        for (i = 0; i < set; i++) {
                for (j = 0; j < line; j++) {
                        valid[i][j] = 0;
                        timeArray[i][j]= 0;
                }
        }
}

int simCache(int addr, int b, int s, int n_sets, int n_lines, int valid[n_sets][n_lines], int tagArray[n_sets][n_lines], int timeArray[n_sets][n_lines]) {
        int set;
        set = get_set(addr, b);
        int tag;
        tag = get_tag(addr, b, s);

        switch(n_sets) {
                case 1:
                        time++;

                        if ((valid[0][0] == 1) && (valid[0][1] == 1) && (valid[0][2] == 1) && (valid[0][3] == 1)) {
                                if (tagArray[0][0] == tag) {
                                        hit++;
                                        timeArray[0][0] = time;
                                        return 1;
                                }
                                else if (tagArray[0][1] == tag) {
                                        hit++;
                                        timeArray[0][1] = time;
                                        return 1;
                                }
                                else if (tagArray[0][2] == tag) {
                                        hit++;
                                        timeArray[0][2] = time;
                                        return 1;
                                }
                                else if (tagArray[0][3] == tag) {
                                        hit++;
                                        timeArray[0][3] = time;
                                        return 1;
                                }
                                else {
                                        miss++;
                                        if ((timeArray[0][0] < timeArray[0][1]) && (timeArray[0][0] < timeArray[0][2]) && (timeArray[0][0] < timeArray[0][3])) {
                                                tagArray[0][0] = tag;
                                                timeArray[0][0] = time;
                                        }
                                        else if ((timeArray[0][1] < timeArray[0][2]) && (timeArray[0][1] < timeArray[0][3])) {
                                                tagArray[0][1] = tag;
                                                timeArray[0][1] = time;
                                        }
                                        else if (timeArray[0][2] < timeArray[0][3]) {
                                                tagArray[0][2] = tag;
                                                timeArray[0][2] = time;
                                        }
                                        else {
                                                tagArray[0][3] = tag;
                                                timeArray[0][3] = time;
                                        }
                                        return 0;
                                }
                        }
                        else {
                                if (valid[0][0] == 0) {
                                        miss++;
                                        valid[0][0] = 1;
                                        tagArray[0][0] = tag;
                                        timeArray[0][0] = time;
                                        return 0;
                                }
                                else {
                                        if (tagArray[0][0] == tag) {
                                                hit++;
                                                timeArray[0][0] = time;
                                                return 1;
                                        }

                                        else if (valid[0][1] == 0) {
                                                miss++;
                                                valid[0][1] = 1;
                                                tagArray[0][1] = tag;
                                                timeArray[0][1] = time;
                                                return 0;
                                        }
                                        else if (valid[0][2] == 0) {
                                                miss++;
                                                valid[0][2] = 1;
                                                tagArray[0][2] = tag;
                                                timeArray[0][2] = time;
                                                return 0;
                                        }
                                        else if (valid[0][3] == 0) {
                                                miss++;
                                                valid[0][3] = 1;
                                                tagArray[0][3] = tag;
                                                timeArray[0][3] = time;
                                                return 0;
                                        }
                                }
                        }
                        break;

                case 2:
                        time++;

                        if ((valid[set][0] == 1) && (valid[set][1] == 1)) {
                                if (tagArray[set][0] == tag) {
                                        hit++;
                                        timeArray[set][0] = time;
                                        return 1;
                                }
                                else if (tagArray[set][1] == tag) {
                                        hit++;
                                        timeArray[set][1] = time;
                                        return 1;
                                }
                                else {
                                        miss++;
                                        if (timeArray[set][0] < timeArray[set][1]) {
                                                tagArray[set][0] = tag;
                                                timeArray[set][0] = time;
                                        }
                                        else {
                                                tagArray[set][1] = tag;
                                                timeArray[set][1] = time;
                                        }
                                        return 0;
                                }
                        }
                        else if (valid[set][0] == 1) {
                                if (tagArray[set][0] == tag) {
                                        hit++;
                                        timeArray[set][0] = time;
                                        return 1;
                                }
                                else {
                                        miss++;
                                        valid[set][1] = 1;
                                        tagArray[set][1] = tag;
                                        timeArray[set][1] = time;
                                }
                                return 0;
                        }
                        else {
                                miss++;
                                valid[set][0] = 1;
                                tagArray[set][0] = tag;
                                timeArray[set][0] = time;
                                return 0;
                        }
                        break;

                case 4:
                        if (valid[set][0] == 1) {
                                if (tagArray[set][0] == tag) {
                                        hit++;
                                        return 1;
                                }
                                else {
                                        tagArray[set][0] = tag;
                                        miss++;
                                        return 0;
                                }
                        }
                        else {
                                valid[set][0] = 1;
                                tagArray[set][0] = tag;
                                miss++;
                                return 0;
                        }
                        break;
        }
}

int main() {
        int S = (C/(B*E));
        int b = log(B)/log(2);
        int s = log(S)/log(2);
        int t = m - (s+ b);
        printf("s = %d, b = %d, S = %d\n", s, b, S);

        int valid[S][E];
        int tagArray[S][E];
        int timeArray[S][E];
        initCache(S, E, valid, timeArray);

        int i,j;
        int address;
        int src_cache[4][4];
        int dst_cache[4][4];

        for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                        address = get_addr(i,j,0);
                        src_cache[i][j] = simCache(address, b, s, S, E, valid, tagArray, timeArray);
                        printf("src_cache[%d][%d] = %d\n", i,j,src_cache[i][j]);
                        address = get_addr(j,i,1);
                        dst_cache[j][i] = simCache(address, b, s, S, E, valid, tagArray, timeArray);
                        printf("dst_cache[%d][%d] = %d\n", j,i,dst_cache[j][i]);
                }
        }

        printf("hit: %d, miss: %d\n",hit, miss);
}
