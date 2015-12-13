#include "p2Defs.h"
#include "p2DynArray.h"
#include "p2SList.h"
#include "p2List.h"
#include "p2Point.h"
#include "p2Queue.h"
#include "p2Queue2.h"
#include "p2Stack.h"
#include "p2Stack2.h"
#include "p2String.h"
#include "p2Graph.h"

uint done = 0;
uint failed = 0;

#define TEST(msg, test) done++; printf("\t%s\t%s\n", !(##test) ? failed++,"FAIL" : "OK", msg)

int main()
{
	// DynArray -------------------
	{
		printf("Testing DynArray ...\n");
		p2DynArray<int> container;
		TEST("Empty constructor", container.capacity() == DYN_ARRAY_BLOCK_SIZE);
		p2DynArray<int> container1(5);
		TEST("Capacity constructor", container1.capacity() == 5);
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
		TEST("Push Back", container[2] == 3 && container.size() == 3);
		TEST("Front", *(container.front()) == 1);
		TEST("Back", *(container.back()) == 3);
		TEST("Empty", container.empty() == false);
		int d;
		container.pop_back(d);
		container.pop_back(d);
		container.pop_back(d);
		TEST("Pop Back", d == 1 && container.pop_back(d) == false);
	}

	// List -------------------
	{
		printf("Testing Double Linked List ...\n");
		p2List<int> container;
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
		TEST("Push Back", container.size() == 3);
		TEST("Front", *(container.front()) == 1);
		TEST("Back", *(container.back()) == 3);
		TEST("Empty", container.empty() == false);
		int d;
		container.pop_back(d);
		container.pop_back(d);
		container.pop_back(d);
		TEST("Pop Back", d == 1 && container.pop_back(d) == false);
	}

	// Single List -------------------
	{
		printf("Testing Single Linked List ...\n");
		p2SList<int> container;
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
		TEST("Push Back", container.size() == 3);
		TEST("Front", *(container.front()) == 1);
		TEST("Back", *(container.back()) == 3);
		TEST("Empty", container.empty() == false);
		int d;
		container.pop_back(d);
		container.pop_back(d);
		container.pop_back(d);
		TEST("Pop Back", d == 1 && container.pop_back(d) == false);
	}

	// Queue List -------------------
	{
		printf("Testing Queue implemented with Single Linked List ...\n");
		p2Queue<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 1);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 3 && container.pop(d) == false);
	}

	// Queue2 DynArray -------------------
	{
		printf("Testing Queue implemented with Dynamic Array ...\n");
		p2Queue2<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 1);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 3 && container.pop(d) == false);
	}

	// Stack List -------------------
	{
		printf("Testing Stack implemented with Dynamic Array ...\n");
		p2Stack<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 3);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 1 && container.pop(d) == false);
	}

	// Stack2 List -------------------
	{
		printf("Testing Stack implemented with SIngle Linked List ...\n");
		p2Stack2<int> container;
		container.push(1);
		container.push(2);
		container.push(3);
		TEST("Push", container.size() == 3);
		TEST("Empty", container.empty() == false);
		TEST("Peek", *(container.peek()) == 3);
		int d;
		container.pop(d);
		container.pop(d);
		container.pop(d);
		TEST("Pop", d == 1 && container.pop(d) == false);
	}

	// String -------------------
	{
		printf("Testing String ...\n");
		p2String str;
		TEST("Empty Constructor", str.capacity() == 1 && str.size() == 0);
		p2String str1(25);
		TEST("Capacity Constructor", str1.capacity() == 25 && str1.size() == 0);
		p2String str2("hello world");
		TEST("C String Constructor", str2.capacity() == 12 && str2.size() == 11);
		TEST("Operator == string", !(str2 == str1));
		TEST("Operator == c string", str2 == "hello world");
		str1 = str2;
		TEST("Operator = string", str1 == "hello world");
		str2 = "bye world";
		TEST("Operator = c string", str2 == "bye world");
		str2 += " test";
		TEST("Operator += c string", str2 == "bye world test");
	}

	// Point -------------------
	{
		printf("Testing Point ...\n");
		iPoint a(2, 2);
		iPoint b = a + a;

		TEST("Operator + Point", b == iPoint(4, 4));
		TEST("Operator -= Point", (b -= a) == iPoint(2, 2));
		TEST("Distance", iPoint(2, 2).DistanceTo(iPoint(2,5)) == 3);
	}

	// Graph -------------------
	{
		printf("Testing Graph ...\n");
		p2Graph<int> container;
		TEST("Empty", container.empty() == true);
		p2Graph<int>::vertice* vertice_1 = container.push_back(1);
		p2Graph<int>::vertice* vertice_2 = container.push_back(2);
		p2Graph<int>::vertice* vertice_3 = container.push_back(3);
		TEST("Push Back", container.size() == 3);
		vertice_1->links.push_back(vertice_2);
		vertice_2->links.push_back(vertice_3);
		vertice_3->links.push_back(vertice_3); // loop
		vertice_3->links.push_back(vertice_2);
		TEST("Push Back", container.size() == 3);
		TEST("is_reachable A", container.is_reachable(vertice_1, vertice_3) == true);
		TEST("is_reachable B", container.is_reachable(vertice_3, vertice_1) == false);
		container.clear();
		TEST("Clear", container.size() == 0);
	}

	printf("\nFailures: %d/%d", failed, done);

	getchar();
	return 0;
}