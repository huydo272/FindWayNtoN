#include<iostream>
#include<conio.h>
#include<cmath>
using namespace std;
const int cr = 40, sm = 5;//communication range, small length
struct toa_do
{
	int x;
	int y;
};
struct node
{
	int ID;
	toa_do td;
	int hop_count;
};
double dist(node a, node b)
{
	double kq, hieux, hieuy;
	hieux = pow(a.td.x - b.td.x, 2);
	hieuy = pow(a.td.y - b.td.y, 2);
	kq = sqrt(hieux + hieuy);
	return kq;
};
int min(int a, int b)
{
	int min;
	if (a < b)
		min = a;
	else min = b;
	return min;
};
int main()
{
	int i, m = 20, j, cha[9], k;
	node n[9];
	for (i = 0; i < 9; i++)
	{
		n[i].ID = i + 1;
		n[i].td.x = m;
		n[i].td.y = 20 + (i%3)*30;
		if ((i + 1) % 3 == 0)
			m = m + 30;
	}//tạo topo 9 node mỗi node cách nhau 30cm xếp thành hình vuông
	cout << "Cac node co toa do nhu sau: " << endl;
	for (i = 0; i < 9; i++)
		cout <<  "Node" << n[i].ID << "(" << n[i].td.x << ";" << n[i].td.y << ")" << endl;
	node sink, neighbor[9][9], temp[9][9];
	sink = n[0];
	cout << "Sink la node" << sink.ID << endl;
	for (i = 0; i < 9; i++)
	{
		cout << "Cac neighbor cua node " << n[i].ID << " la: ";
		for (j = 0; j < 9; j++)
		{
			if (i != j && dist(n[i], n[j]) <= cr)
			{
				neighbor[i][j] = n[j];
				cout << "Node" << neighbor[i][j].ID << ", ";
			}
		}
		cout << endl;
	}
	/*for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			cha[i] = min(neighbor[i][j].ID, neighbor[i][j + 1].ID);
		}

	}
	for (i = 0; i < 9; i++)
	{
		cout << "Node cha cua node " << i + 1 << " la node " << cha[i] << endl;
	}*/
	system("pause");
	return 0;
}