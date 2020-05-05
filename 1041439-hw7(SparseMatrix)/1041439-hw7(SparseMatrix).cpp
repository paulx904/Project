#include <iostream>
#include <cstdlib>
using namespace std;

#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

struct entryNode
{
	int row;
	int col;
	int value;
};

enum tagfield
{
	head, entry
};

struct MatrixNode
{
	MatrixNode *down;
	MatrixNode *right;
	tagfield tag;
	union
	{
		MatrixNode *next;
		entryNode entry;
	} u;
};

MatrixNode *hdnode[100];

class SparseMatrix
{
	// print out sparseMatrix in row major form
	friend ostream &operator<<(ostream &output, const SparseMatrix &sparseMatrix);
public:
	SparseMatrix(); // default constructor with empty body

	SparseMatrix(const SparseMatrix &matrixToCopy); // copy constructor

	~SparseMatrix(); // destructor in which the matrix is erased

	const SparseMatrix &operator=(const SparseMatrix &op2);

	void read(); // read in a matrix and set up its linked representation

	SparseMatrix operator+(SparseMatrix &op2); // Returns the sum of two sparse matrices

	void printColumnMajor(); // print out the matrix in column major form

	void erase(); // erase the matrix
private:
	MatrixNode *node; // a pointer to the header node for the list of header nodes
};

#endif

SparseMatrix::SparseMatrix()
: node(0)
{
}

SparseMatrix::SparseMatrix(const SparseMatrix &matrixToCopy)
{
	node = matrixToCopy.node;
}

SparseMatrix::~SparseMatrix()
{
	//erase();
}

const SparseMatrix &SparseMatrix::operator=(const SparseMatrix &op2)
{
	node = op2.node;
	return *this;
}

void SparseMatrix::read()
{
	int numRows, numCols, numTerms, numHeads, i;
	int row, col, value, currentRow;
	MatrixNode *last;

	cin >> numRows >> numCols >> numTerms;
	numHeads = (numCols > numRows) ? numCols : numRows;

	MatrixNode *newNode = new MatrixNode;
	newNode->tag = entry;
	newNode->u.entry.row = numRows;
	newNode->u.entry.col = numCols;
	newNode->u.entry.value = numTerms;
	node = newNode;

	if (!numHeads) 
		newNode->right = newNode;
	else {
		for (i = 0; i < numHeads; i++) {
			MatrixNode *temp = new MatrixNode;
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		currentRow = 0;
		last = hdnode[0];

		for (i = 0; i < numTerms; i++) {
			cin >> row >> col >> value;
			if (row > currentRow) {
				last->right = hdnode[currentRow];
				currentRow = row;
				last = hdnode[row];
			}
			MatrixNode *temp = new MatrixNode;
			temp->tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;
			last->right = temp;
			last = temp;
			hdnode[col]->u.next->down = temp;
			hdnode[col]->u.next = temp;
		}
		last->right = hdnode[currentRow];

		for (i = 0; i < numHeads; i++)
			hdnode[i]->u.next->down = hdnode[i];
		for (i = 0; i < numHeads - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[numHeads - 1]->u.next = node;
		node->right = hdnode[0];
	}
	
}

SparseMatrix SparseMatrix:: operator+(SparseMatrix &op2)
{/*
	int row, col, numHeads, numTerms = 0;

	SparseMatrix op3;
	MatrixNode *newNode = new MatrixNode;
	newNode->tag = entry;
	newNode->u.entry.row = node->u.entry.row;
	newNode->u.entry.col = node->u.entry.col;
	op3.node = newNode;
	numHeads = (newNode->u.entry.col > newNode->u.entry.row) ? newNode->u.entry.col : newNode->u.entry.row;

	for (int i = 0; i < numHeads; i++) {
		MatrixNode *temp = new MatrixNode;
		hdnode[i] = temp;
		hdnode[i]->tag = head;
		hdnode[i]->right = temp;
		hdnode[i]->u.next = temp;
	}
	MatrixNode *op1_head, *op2_head, *op3_head, *x, *y, *z;
	op1_head = node->right;
	op2_head = op2.node->right;
	z = hdnode[0];

	for (row = 0; row < newNode->u.entry.row; row++){
		MatrixNode *temp = new MatrixNode;
		x = op1_head->right;
		y = op2_head->right;
		z = hdnode[row];

		while (x != op1_head && y != op2_head){
			if (x->u.entry.col < y->u.entry.col){
				temp->tag = entry;
				temp->u.entry.row = x->u.entry.row;
				temp->u.entry.col = x->u.entry.col;
				temp->u.entry.value = x->u.entry.value;
				x = x->right;
			}
			else if (x->u.entry.col > y->u.entry.col){
				temp->tag = entry;
				temp->u.entry.row = y->u.entry.row;
				temp->u.entry.col = y->u.entry.col;
				temp->u.entry.value = y->u.entry.value;
				y = y->right;
			}
			else{
				temp->tag = entry;
				temp->u.entry.row = y->u.entry.row;
				temp->u.entry.col = y->u.entry.col;
				temp->u.entry.value = x->u.entry.value + y->u.entry.value;
				x = x->right;
				y = y->right;
			}
			z->right = temp;
			z = temp;
			hdnode[temp->u.entry.col]->u.next->down = temp;
			hdnode[temp->u.entry.col]->u.next = temp;
			numTerms++;
			cout << z->u.entry.value;
		}
		while (x != op1_head){
			temp->tag = entry;
			temp->u.entry.row = x->u.entry.row;
			temp->u.entry.col = x->u.entry.col;
			temp->u.entry.value = x->u.entry.value;
			x = x->right;
			z->right = temp;
			z = temp;
			hdnode[temp->u.entry.col]->u.next->down = temp;
			hdnode[temp->u.entry.col]->u.next = temp;
			numTerms++; cout << z->u.entry.value;
		}
		while (y != op2_head){
			temp->tag = entry;
			temp->u.entry.row = y->u.entry.row;
			temp->u.entry.col = y->u.entry.col;
			temp->u.entry.value = y->u.entry.value;
			y = y->right;
			z->right = temp;
			z = temp;
			hdnode[temp->u.entry.col]->u.next->down = temp;
			hdnode[temp->u.entry.col]->u.next = temp;
			numTerms++; cout << z->u.entry.value;
		}
		z->right = hdnode[row];
		op1_head = op1_head->u.next;
		op2_head = op2_head->u.next; cout << endl;
	}
	z->right = hdnode[row];

	for (int i = 0; i < numHeads; i++)
		hdnode[i]->u.next->down = hdnode[i];
	for (int i = 0; i < numHeads - 1; i++)
		hdnode[i]->u.next = hdnode[i + 1];
	hdnode[numHeads - 1]->u.next = node;
	op3.node->right = hdnode[0];
	op3.node->u.entry.value = numTerms;
	//cout << op3.node->right->right->u.entry.row << op3.node->right->right->u.entry.col << op3.node->right->right->u.entry.value;
	return op3;
	*/
	SparseMatrix tmp = *this;
	MatrixNode *mytmp, *mytmp2, *frontrow, *frontcol, *firstcol, *nextrow, *nextcol;
	bool asigned = false;
	for (MatrixNode *find = op2.node->right; find != op2.node; find = find->u.next) {
		for (MatrixNode *find2 = find->right; find2 != find; find2 = find2->right) {
			mytmp = tmp.node->right;
			for (int i = 0; i < find2->u.entry.row; i++, mytmp = mytmp->u.next); //指到被加的矩陣的那列相等於要加的矩陣的那個元素的那列
			for (mytmp2 = mytmp->right, firstcol = tmp.node->right; mytmp2 != mytmp && mytmp2->u.entry.col <= find2->u.entry.col; mytmp2 = mytmp2->right) {
				if (mytmp2->u.entry.col == find2->u.entry.col) {
					mytmp2->u.entry.value += find2->u.entry.value;
					if (mytmp2->u.entry.value == 0) {
						for (int i = 0; i < mytmp2->u.entry.col; i++) firstcol = firstcol->u.next;
						for (frontrow = mytmp; frontrow->right != mytmp2; frontrow = frontrow->right);
						for (frontcol = firstcol; frontcol->down != mytmp2; frontcol = frontcol->down);
						nextrow = mytmp2->right; nextcol = mytmp2->down;
						delete mytmp2;
						frontrow->right = nextrow; frontcol->down = nextcol;
						tmp.node->u.entry.value--;
					}
					asigned = true;
					break;
				}
			}
			if (!asigned) {
				mytmp2 = new MatrixNode(); mytmp2->tag = entry;
				mytmp2->u.entry.row = find2->u.entry.row; mytmp2->u.entry.col = find2->u.entry.col; mytmp2->u.entry.value = find2->u.entry.value;
				for (frontrow = mytmp, firstcol = tmp.node->right; frontrow->right != mytmp && frontrow->right->u.entry.col <= mytmp2->u.entry.col; frontrow = frontrow->right); //frontrow會指到比要新加的元素左邊一個位置
				for (int i = 0; i < mytmp2->u.entry.col; i++, firstcol = firstcol->u.next);
				for (frontcol = firstcol; frontcol->down != firstcol && frontcol->down->u.entry.row <= mytmp2->u.entry.row; frontcol = frontcol->down);
				nextrow = frontrow->right; nextcol = frontcol->down;
				frontrow->right = mytmp2; mytmp2->right = nextrow; frontcol->down = mytmp2; mytmp2->down = nextcol;
				tmp.node->u.entry.value++;
			}
			asigned = false;
		}
	}
	return tmp;
}

void SparseMatrix::printColumnMajor()
{  // print out the matrix in column major form
	cout << node->u.entry.row << " ";
	cout << node->u.entry.col << " ";
	cout << node->u.entry.value << endl;

	for (MatrixNode *head = node->right; head != node; head = head->u.next)
	for (MatrixNode *temp = head->down; temp != head; temp = temp->down)
	{
		cout << temp->u.entry.row << " ";
		cout << temp->u.entry.col << " ";
		cout << temp->u.entry.value << endl;
	}
}

void SparseMatrix::erase()
{
	MatrixNode *x, *y, *head = node->right;
	int i;
	for (i = 0; i < node->u.entry.row; i++) {
		y = head->right;
		while (y != head) {
			x = y;  y = y->right;  free(x);
		}
		x = head;  head = head->u.next; free(x);
	}
	
	y = head;
	while (y != node) {
		x = y;  y = y->u.next;  free(x);
	}

	free(node);  node = NULL;
}

ostream &operator<<(ostream &output, const SparseMatrix &sparseMatrix)
{  // print out the matrix in row major form
	cout << sparseMatrix.node->u.entry.row << " ";
	cout << sparseMatrix.node->u.entry.col << " ";
	cout << sparseMatrix.node->u.entry.value << endl;

	MatrixNode *head = sparseMatrix.node;
	for (head = head->right; head != sparseMatrix.node; head = head->u.next)
	for (MatrixNode *temp = head->right; temp != head; temp = temp->right)
	{
		cout << temp->u.entry.row << " ";
		cout << temp->u.entry.col << " ";
		cout << temp->u.entry.value << endl;
	}

	return output; // enables cout << x << y;
}

int main()
{
	SparseMatrix addend;
	SparseMatrix adder;
	addend.read();
	adder.read();
	SparseMatrix sum;
	sum = addend + adder;
	cout << sum << endl;
	sum.printColumnMajor();
	system("pause");
}
