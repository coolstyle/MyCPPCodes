// MulvariableTest1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
#include<stdlib.h>
#include<conio.h>
using namespace std;
struct poly
{
	int coeff;
	int x;
	int y;
	int z;
	struct poly * next;
};

class polynomial
{
private:
	poly *head;

public:
	polynomial() :head(NULL)
	{
	}


	void getdata();
	void display();
	void insert(poly *prv, poly *curr, poly *p);
	poly* getPreNode(polynomial* p,poly* KeyNode) {
		poly* tmp;
		poly* pHead = p->head;
		while (pHead) {
			tmp = pHead;
			pHead = pHead->next;
			if (pHead == KeyNode) {
				return tmp;
			}
		}

	}
	polynomial simplify(polynomial p) {
		poly* pHead = p.head;
		
		poly* it = p.head->next;

		while (pHead)
		{
			it = pHead->next;
			while (it)
			{
				if (pHead->x == it->x && pHead->y == it->y && pHead->z == it->z)
				{
					pHead->coeff += it->coeff;
					poly* pre = getPreNode(&p, it);
					poly* tmp = it;
					pre->next = it->next;
					it = pre;
					delete tmp;
				}
				it = it->next;

			}
			pHead = pHead->next;
		}

		return p;

	}
	polynomial operator + (polynomial& p1)
	{
		poly* end;
		poly* pHead = this->head;
		while (pHead)
		{
			end = pHead;
			pHead = pHead->next;
			
		}
		end->next = p1.head;
		polynomial pTmp=this->simplify(*this);
		return pTmp;
	}
	polynomial operator - (polynomial& p1)
	{
		poly* pHead = p1.head;
		while (pHead)
		{
			pHead->coeff *= -1;
			pHead = pHead->next;
		}
		polynomial tmp = *this + p1;

		return tmp;
	}
	polynomial operator * (polynomial& p1)
	{
		poly* LocalPoly = this->head;
		poly* multiplicator=p1.head;
		polynomial storagePolynomial;

		poly* storageTerm=new poly;
		storagePolynomial.head = storageTerm;
		while (LocalPoly)
		{
			 multiplicator = p1.head;
			 
			while (multiplicator)
			{
				storageTerm->coeff = LocalPoly->coeff * multiplicator->coeff;
				storageTerm->x = LocalPoly->x + multiplicator->x;
				storageTerm->y = LocalPoly->y + multiplicator->y;
				storageTerm->z = LocalPoly->z + multiplicator->z;
				storageTerm->next = NULL;
				if (multiplicator->next)
				{
					
					storageTerm->next = new poly;
					storageTerm = storageTerm->next;
				}
				multiplicator = multiplicator->next;
			}
			LocalPoly = LocalPoly->next;
			if (LocalPoly)
			{
				storageTerm->next = new poly;
				storageTerm = storageTerm->next;
			}
		}
		polynomial result = storagePolynomial.simplify(storagePolynomial);
		return result;
	}
};
void polynomial::insert(poly *prv, poly *curr, poly *node)
{
	if (node->x == curr->x && node->y == curr->y && node->z == curr->z)
	{
		curr->coeff += node->coeff;
		delete node;
	}
	else if((node->x > curr->x) || (node->x == curr->x && node->y > curr->y) || (node->x == curr->x && node->y == curr->y && node->z > curr->z))
	{
		node->next = curr;
		prv->next = node;
	}
	else
	{
		prv = curr;
		curr = curr->next;
		if (curr == NULL)
		{
			prv->next = node;
			node->next = NULL;
			return;
		}
		insert(prv, curr, node);
	}
	return;
}

void polynomial::getdata()
{
	int tempcoeff;
	poly *node;
	while (1)
	{
		cout << endl << "Coefficient : ";

		cin >> tempcoeff;
		if (tempcoeff == 0)
			break;
		node = new poly;
		node->coeff = tempcoeff;
		cout << endl << "Power of X : ";
		cin >> node->x;
		cout << endl << "Power of Y : ";
		cin >> node->y;
		cout << endl << "Power of Z : ";
		cin >> node->z;
		if (head == NULL)
		{
			node->next = NULL;
			head = node;
		}
		else if(node->x == head->x && node->y == head->y && node->z == head->z)
		{
			head->coeff += node->coeff;
			delete node;
		}

		else if((node->x > head->x) || (node->x == head->x && node->y > head->y) || (node->x == head->x && node->y == head->y && node->z > head->z))
		{
			node->next = head;
			head = node;
		}
		else if(head->next == NULL)
		{
			head->next = node;
			node->next = NULL;
		}
		else
			insert(head, head->next, node);
	}
}
void polynomial::display()
{
	poly *temp;
	temp = this->head;
	cout << endl << "Polynomial:";
	while (temp)
	{
		if (temp->coeff != 0)
		{
			if (temp->coeff == 1)
			{
				cout << "(" << "x^" << temp->x << "y^" << temp->y << "z^" << temp->z << ")";
			}
			else if (temp->coeff == -1)
			{
				cout << "(" <<"-"<< "x^" << temp->x << "y^" << temp->y << "z^" << temp->z << ")";
			}
			else
				cout << "(" << temp->coeff << "x^" << temp->x << "y^" << temp->y << "z^" << temp->z << ")";
		}
		 
		else 
			cout << 0;

		temp = temp->next;
		if (temp) {
			cout << "+";
		}
			
	}
	
}
void main()
{
	polynomial px1, px2, px3;
	px1.getdata();
	px1.display();
	px2.getdata();
	px2.display();
	px3 = px1+px2;
	cout << endl;
	cout << "*********----- RESULT------- **********"<< endl;
	px3.display();
	getch();
}

