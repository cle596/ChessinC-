#pragma once

int up = -10;
int dn = 10;
int lt = -1;
int rt = 1;
char ally[] = { 'P','N','B','R','Q','K' };
char foe[] = { 'p','n','b','r','q','k' };
int Nmoves[] = {
	2 * up + rt,up + 2 * rt,dn + 2 * rt,2 * dn + rt,
	2 * dn + lt,dn + 2 * lt,up + 2 * lt,2 * up + lt
};
int Bmoves[] = {
	up + rt,dn + rt,
	dn + lt,up + lt
};
int Rmoves[] = {
	up,rt,
	dn,lt
};
int Kmoves[] = {
	up,up + rt,rt,dn + rt,dn,
	dn + lt,lt,up + lt
};