#include "LinkGraph.cpp"

int main()
{
	/*
	LinkGraph<char,int> lg1;

	for(int i=0; i<6; i++)
		lg1.insertVertex('A'+i);

	lg1.insertEdge(0,2,3);
	lg1.insertEdge(0,5,20);
	lg1.insertEdge(1,0,10);
	lg1.insertEdge(2,1,13);
	lg1.insertEdge(2,3,5);
	lg1.insertEdge(3,5,6);
	lg1.insertEdge(5,2,11);
	lg1.insertEdge(5,4,6);

	lg1.show();

	cout<<"Weight of 'A' and 'C' is "<<lg1.getWeight('A','C')<<". \n";
	cout<<"Weight of 'C' and 'D' is "<<lg1.getWeight('C','D')<<". \n";

	cout<<endl<<"DFS order: ";
	lg1.DFS('A');
	cout<<endl<<"BFS order: ";
	lg1.BFS('A');
*/
	LinkGraph<char,int> lg2;
	for(int i=0; i<5; i++)
		lg2.insertVertex('A'+i);

	lg2.insertEdge(0, 1, 0);	
	lg2.insertEdge(0, 2, 0);	
	lg2.insertEdge(1, 2, 0);	
	lg2.insertEdge(1, 3, 0);	
	lg2.insertEdge(1, 4, 0);	
	lg2.insertEdge(2, 3, 0);	
	lg2.insertEdge(3, 4, 0);	
	lg2.insertEdge(4, 0, 0);	
	lg2.insertEdge(4, 2, 0);	

	lg2.show();

	for(int i=0; i<5; i++)
		cout<<((char)('A' + i))<<" outdegrees: "<<lg2.outDegrees((char)('A'+i))<<"\t\t"<<"indegrees: "<<lg2.inDegrees((char)('A'+i))<<endl;

	cout<<endl<<"DFS order: ";
	lg2.DFS('A');
	cout<<endl<<"BFS order: ";
	lg2.BFS('B');


	return 0;
}
