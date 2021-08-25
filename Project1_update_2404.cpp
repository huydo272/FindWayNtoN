#include<iostream>
#include<conio.h>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<queue>
using namespace std;

const int cr = 25, sm = 5, xmax = 100, ymax = 100, ttl = 10, qmax = 4, tf = 20, ts = 4;
struct toa_do
{
	int x;
	int y;
};
struct packet
{
	int id;
	int tg;
};
class node
{
private:
	int ID;
	toa_do td;
	int hop_count = -1;
	int prt = 1;
	packet psend;
public:
	vector<node> neighbor, parent;
	queue<packet> q;
public:
	void setID(int i)
	{
		this->ID = i;
	}
	int getID()
	{
		return this->ID;
	}
	void set_hc(int i)
	{
		this->hop_count = i;
	}
	int get_hc()
	{
		return this->hop_count;
	}
	void rand_node()
	{
		this->td.x = rand() % (xmax);
		this->td.y = rand() % (ymax);
	}
	int get_x()
	{
		return this->td.x;
	}
	int get_y()
	{
		return this->td.y;
	}
	void q_init()
	{
		packet temp;
		int r;
		if (ID != 1)
			r = (ID % qmax) + 1;
		else r = 0;
		for (int j = 0; j < r; j++)
		{
			if (ID == 1)
				break;
			else
			{
				temp.id = j + 1;
				temp.tg = 0;
				q.push(temp);
			}
		}//load packets into queue
	}
	void q_delete(int t)
	{
		while ((q.size() > 0) && (t == (q.front().tg + ttl)))
		{
				this->q.pop();//delete packet khi hết tg sống
		}
	}
	int stat(int t)
	{
		int a;
		for (int i = 0; i < 20; i++)
		{
			if ((t == (4 * i + (this->ID % 4))) && (ID != 1) && (this->parent.size() > 0))
			{
				a = this->parent.front().ID;
				break;
			}
			else a = 0;
		}
		return a;
	}//hàm status
	int chan(int t)
	{
		switch (ID % 3)
		{
		case 0:
		{
			switch (t % 3)
			{
			case 0: {return 1; break; }
			case 1: {return 2; break; }
			case 2: {return 3; break; }
			}
		}
		case 1:
		{
			switch (t % 3)
			{
			case 0: {return 2; break; }
			case 1: {return 3; break; }
			case 2: {return 1; break; }
			}
		}
		case 2:
		{
			switch (t % 3)
			{
			case 0: {return 3; break; }
			case 1: {return 1; break; }
			case 2: {return 2; break; }
			}
		}
		}
	}//quản lý channel
	void set_prt(int x)
	{
		this->prt = x;
	}
	int get_prt()
	{
		return this->prt;
	}
	void set_p(packet a)
	{
		this->psend = a;
	}
	packet get_p()
	{
		return this->psend;
	}
};
void trafic(node& a, node& b, int t)
{
	if ((a.stat(t) == b.getID()) && (b.stat(t) == 0) && (a.get_prt() == 0))
	{
		if (a.q.size() > 0)
		{
			cout << "Sending packet " << a.q.front().id << " from node " << a.getID() << " to node " << a.stat(t) << " on channel " << a.chan(t) << endl;
			a.set_p(a.q.front());
			a.q.pop();
		}
		else
		{
			cout << "No packet to send!" << endl;
			return;
		}//hàm gửi
		if (b.q.size() < qmax)
		{
			b.q.push(a.get_p());
			b.q.back().tg = 0;
			cout << "Node " << b.getID() << " received packet " << b.q.back().id << " from node " << a.getID()<<" tai "<< t << endl;
			if ((b.getID() == 1) && (b.q.size() == 4))
			{
				cout << "Sink da nhan du du lieu tai t = " << t << ". Ket thuc!";
				system("pause");
			}
		}
		else cout << "Failed to receive a packet!" << endl;//hàm nhận
	}
}
double dist(node a, node b)
{
	double kq, hieux, hieuy;
	hieux = pow(a.get_x() - b.get_x(), 2);
	hieuy = pow(a.get_y() - b.get_y(), 2);
	kq = sqrt(hieux + hieuy);
	return kq;
};
int min(int a, int b)
{
	if (a < b)
		return a;
	else return b;
}
int main()
{
	int so_node, i, j;
	cout << "Nhap so node muon mo phong: ";
	cin >> so_node;
	while (so_node <= 0 || so_node > 50)
	{
		cout << "So node phai lon hon 0 va nho hon 50. Nhap lai: ";
		cin >> so_node;
	}
	node n[50];
	srand(time(NULL));
	n[0].setID(1);
	n[0].rand_node();
	for (i = 1; i < so_node; i++)
	{
		n[i].setID(i + 1);
		do
		{
			n[i].rand_node();
		} while (dist(n[i], n[i - 1]) > cr);
	}//random n<=50 node
	for (i = 0; i < so_node; i++)
	{
		int k = 0;
		for (j = 0; j < so_node; j++)
		{
			if (i != j && dist(n[i], n[j]) <= sm)
				n[i].rand_node();
		}
		cout << endl;
	}//check small length
	cout << "Cac node co toa do nhu sau: " << endl;
	for (i = 0; i < so_node; i++)
		cout << "Node" << n[i].getID() << "(" << n[i].get_x() << ";" << n[i].get_y() << ")" << endl;
	for (i = 0; i < so_node; i++)
	{
		cout << "Cac neighbor cua node " << n[i].getID() << " la: ";
		int k = 0;
		for (j = 0; j < so_node; j++)
		{
			if (i != j && dist(n[i], n[j]) <= cr)
			{
				n[i].neighbor.push_back(n[j]);
				cout << "Node" << n[i].neighbor[k++].getID() << "   ";
			}
			else continue;
		}
		cout << endl;
	}//neighbor
	n[0].set_hc(0);
	node& sink = n[0];
	cout << "Sink la node" << sink.getID() << endl;
	for (int k = 0; k < so_node; k++)
	{
		for (i = 0; i < so_node; i++)
		{
			if (n[i].get_hc() == k)
			{
				for (j = 0; j < n[i].neighbor.size(); j++)
				{
					if (n[n[i].neighbor[j].getID() - 1].get_hc() == -1)
						n[n[i].neighbor[j].getID() - 1].set_hc(k + 1);
				}
			}
		}
	}//hop_count
	for (i = 0; i < so_node; i++)
	{
		for (j = 0; j < n[i].neighbor.size(); j++)
		{
			n[i].neighbor[j].set_hc(n[n[i].neighbor[j].getID() - 1].get_hc());
		}
	}
	for (i = 0; i < so_node; i++)
		cout << "Hop_count cua node " << n[i].getID() << " la " << n[i].get_hc() << endl;
	int hc[50], id[50];
	for (i = 1; i < so_node; i++)
	{
		if (n[i].neighbor.size() > 0)
		{
			hc[i] = n[i].neighbor.front().get_hc();
			for (j = 0; j < n[i].neighbor.size() - 1; j++)
			{
				hc[i] = min(hc[i], n[i].neighbor[j + 1].get_hc());
			}
		}
	}//tim hop_count min cua cac neighbor cua moi node
	for (i = 1; i < so_node; i++)
	{
		for (j = 0; j < n[i].neighbor.size(); j++)
		{
			if (n[i].neighbor[j].get_hc() == hc[i])
			{
				n[i].parent.push_back(n[n[i].neighbor[j].getID() - 1]);//luu ID cac neighbor co hop count nho nhat
				break;
			}
		}
		if(n[i].parent.size()>0)
			cout << "Node " << n[i].getID() << " co node parent la node " << n[i].parent.front().getID() << endl;
	}//parent
	int t1, t2;
	for (int i = 0; i < so_node; i++)
		n[i].q_init();
	for (t1 = 1; t1 <= tf; t1++)
	{
		for (t2 = 1; t2 <= ts; t2++)
		{
			int t = 4 * (t1 - 1) + t2;
			for (int i = 0; i < so_node; i++)
				n[i].q_delete(t);
			for (int i = 0; i < so_node; i++)
				for (int j = 0; j < so_node; j++)
					if (i != j)
					{
						if ((n[i].chan(t) == n[j].chan(t)) && (n[i].stat(t) != 0)&&(n[i].stat(t)!=0))
						{
							if ((n[i].get_hc() < n[j].get_hc()) && (n[i].q.size() > 0))
							{
								n[j].set_prt(1);
								n[i].set_prt(0);
							}
							else
							{
								n[i].set_prt(1);
								n[j].set_prt(0);
							}
						}
					}
			for (int i = 0; i < so_node; i++)
				for (int j = 0; j < so_node; j++)
					if (i != j)
						trafic(n[i], n[j], t);
		}
	}
	return 0;
}