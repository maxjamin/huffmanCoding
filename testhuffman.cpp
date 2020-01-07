#include <iostream>
#include <map>
#include <list>
#include <vector> 

/**********************************************************************
* PQNode for PriorityQueue data structure. 
* 

**********************************************************************/
struct PQNode {
private:
	char c;
	int weight;
public:
	PQNode();
	PQNode(int x, char c);
	PQNode(int x, char c, PQNode left, PQNode right);
	int getWeight() {return weight; }
	char getValue() {return c;		}

	void setWeight(char x) {this->c = x; }
	void incrWeight() { weight++; }
	void setValue(int w)   {this->weight = w;}
};
/**********************************************************************
* Default Constructor

**********************************************************************/
PQNode::PQNode() {
	c = ' ';
	weight = 0;
}
/**********************************************************************
* Constructor

**********************************************************************/
PQNode::PQNode(int x, char chr) {
	weight = x;
	this->c = chr;
}
/**********************************************************************
* Class, made to order PQNodes 

**********************************************************************/
class PriorityQueue {
public:
	std::vector<PQNode> one; 
	int found(char x);
	int add(char x);
	void display();
	int size() {return one.size(); }
	PQNode push();
	PQNode pushFront();
	int sortList(int low, int high);
	int partition(int low, int high);

};
/**********************************************************************
* 
*
**********************************************************************/
PQNode PriorityQueue::push() {
	PQNode temp = one.back();
	one.pop_back();
	return temp; 
}
/**********************************************************************
* 
*
**********************************************************************/
PQNode PriorityQueue::pushFront() {
	PQNode temp = one.front();
	one.erase(one.begin());
	return temp; 
}
/**********************************************************************
* 
*
**********************************************************************/
int PriorityQueue::partition( int low, int high) {
	PQNode pivot = one[high];
	int i = low;

	for(int j=low; j< high; j++) {
		if (one[j].getWeight() > pivot.getWeight()){

			PQNode tempNode = one[i];
			one[i] = one[j];
			one[j] = tempNode;
			i++;
		}
	}

	PQNode tempN = one[i];
	one[i] = one[high];
	one[high] = tempN;
	return i;
}
/**********************************************************************
* 
*
**********************************************************************/
int PriorityQueue::sortList(int low, int high) {

	if(low < high){
		int p = partition(low, high);
		sortList(low, p-1);
		sortList(p+1, high);
	}


	return 0;
}
/**********************************************************************
* 
*
**********************************************************************/
void PriorityQueue::display(){
	std::cout << "---------------\n";
	for(int i = 0; i < one.size();i++) {
		std::cout << one[i].getValue() << " - " 
		<< one[i].getWeight() << "\n";
	}
}
/**********************************************************************
* 
*
**********************************************************************/
//If found return place in queue or return 0
int PriorityQueue::found(char x){
	for(int i = 0; i < one.size();i++) {
		if(one[i].getValue() == x) {return i; }
	}
	return -1;
}
/**********************************************************************
* 
*
**********************************************************************/
int PriorityQueue::add(char x){

	int tempPos;
	int tempWeight;
	PQNode tempNode(1,x);

	if((tempPos = found(x)) != -1){
		
		one[tempPos].incrWeight();
		//std::cout << tempPos << " Position for " << x <<" is found" << "\n";

	}else{
		//std::cout << "is not found \n";
		one.push_back(tempNode);
	}
}
/**********************************************************************
* 
*
**********************************************************************/
class node {
private:
	char value;
	int weight;
public:
	node *left;
	node *right;
	node * next;
	node(char value, int weight);
	node(char value, int weight, node*left, node*right);
	node();
	int getWeight() { return weight; }
	char  getValue() 	{ return value; }
	void setWeight(int weight) { this->weight = weight; }
	void setValue(char value)  { this->value = value;   }

};
/**********************************************************************
* 
*
**********************************************************************/
node::node(){
	this->value = ' ';
	this->weight = 0;
	this->left = NULL;
	this->right= NULL;
	this->next = NULL;
}
/**********************************************************************
* 
*
**********************************************************************/
node::node(char value, int weight) {

	//std::cout << "Node value " << value  << " Weight " << weight << "\n";
	this->value = value;
	this->weight= weight;
	this->left = NULL;
	this->right= NULL;
	this->next = NULL;
}
/**********************************************************************
* 
*
**********************************************************************/
node::node(char value, int weight, node * left, node * right) {

	this->value = value;
	this->weight= weight;
	this->left = left;
	this->right= right;
	this->next = NULL;
}
/**********************************************************************
* 
*
**********************************************************************/
class tree{
public:
	node * root;
	node * table;
	std::map<char, std::string> coder;
	int size;
	tree();
	tree(int size);
	void traverse(node * r);
	int fillQueue();
	std::string findCharToEncode(char c);
	void encodeTree(node * rt, std::string str, std::map<char, 
	std::string> &coder);
	int fillTree(PriorityQueue pq);
	int sizeOfTree() { return size; }

};
/**********************************************************************
* 
*
**********************************************************************/
tree::tree(int size) {
	root = NULL;
	table = NULL;
	this->size = size;
}
/**********************************************************************
* 
*
**********************************************************************/
tree::tree() {
	root = NULL;
	table = NULL;
}
/**********************************************************************
* 
*
**********************************************************************/
void tree::traverse(node *rt){

	if(rt != NULL)
    {
        traverse(rt -> left);
        std::cout << "Weight " << rt->getWeight() << 
        " - " << rt->getValue() << " \n";
        traverse(rt -> right);
    }
}
/**********************************************************************
* 
*
**********************************************************************/
int tree::fillQueue() {

	//add item to each other and place them onto the array
	node * temp = table;
	temp = temp->next;

	while(size > 1) {
		std::cout << "----------------------------------\n";

		node * nodeBefore = table;
		node * nextNode = temp->next;
		while(nodeBefore->next != NULL){
			if(nodeBefore->next->getValue() == temp->getValue()){
				std::cout << "TEST4.1\n";
				break;
			}
			nodeBefore = nodeBefore->next;
		}		

		if(temp->next->getWeight() != 0) {
			std::cout << "TEST4.3\n";
			node * newInternal = new node('^', 
			temp->getWeight()+nextNode->getWeight());

			if(temp->getWeight() >= nextNode->getWeight()){
				newInternal->right = temp;
				newInternal->left  = nextNode;
			}else{
				newInternal->right = nextNode;
				newInternal->left  = temp;
			}

			nodeBefore->next = temp->next->next;

			node * nodeBeforeTemp = table->next;
			while(nodeBeforeTemp->next != NULL){

				if((nodeBeforeTemp->getWeight() <= newInternal->getWeight() && nodeBeforeTemp->next->getWeight() > newInternal->getWeight()) ||
				   (nodeBeforeTemp->next->getWeight() == 0 && newInternal->getWeight() >= nodeBeforeTemp->getWeight())){

					std::cout << "TEST5.2 " << newInternal->getWeight() << 
					"  Before " << nodeBeforeTemp->getWeight() << "- " << nodeBeforeTemp->getValue() << "\n" 
					<<"next " << nodeBeforeTemp->next->getWeight() << " - "<< nodeBeforeTemp->next->getValue() << "\n";
					break;
				}
				nodeBeforeTemp = nodeBeforeTemp->next;
			}

			node *tempPlace = nodeBeforeTemp->next;
			nodeBeforeTemp->next=newInternal;
			newInternal->next = tempPlace;

			temp = table->next;
			size = size-1;
			std::cout << "TEST05\n";



		}
	}

	table = table->next->next;
	std::cout << "LOOP ENDED\n";

	std::cout << " " << "\n";
	node * t = table;
	for(int i = 0; t != NULL ;i++) {
		std::cout << "The value of this is " <<  t->getWeight() 
		<< " - " << t->getValue() << "\n"; 
		t = t->next;
	}
}
/**********************************************************************
* 
*
**********************************************************************/
int tree::fillTree(PriorityQueue pq) {

	//add pq value onto the list
	node * temp = table;
	table = new node();
	for(int i = 0; i < this->size ;i++) {


		PQNode tempNode = pq.pushFront();

		temp = new node(tempNode.getValue(), tempNode.getWeight()); 
		temp->next = table;
		table = temp;
	}
	temp = new node(); 
	temp->next = table;
	table = temp;	

	fillQueue();
	traverse(table);

	std::map<char, std::string> coder;
	encodeTree(table,"", coder);
	this->coder = coder;

	for (std::map<char,std::string>::iterator it=this->coder.begin(); 
	it!=this->coder.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';


}
/**********************************************************************
* Encode tree, after tree is built 
*
**********************************************************************/
// Algorithm based off https://www.techiedelight.com/huffman-coding/
void tree::encodeTree(node * rt, std::string str,
	std::map<char, std::string> &coder) {

	if(rt == NULL){
		return;
	}

	//if leaf is found
	if(rt->getValue() != '^'){
		std::cout << "VALUE IS " << rt->getValue() << "\n";
		coder[rt->getValue()] = str;
	}

	encodeTree(rt->right, str +"1", coder);
	encodeTree(rt->left,  str +"0", coder);
	
}
/**********************************************************************
* Find char encoded with char input. 
*
**********************************************************************/
//returns char to encode
std::string tree::findCharToEncode(char c){

	try{
	std::string returnValue = coder.at(c);
	
		return returnValue;
	}catch(const std::exception ex){
		std::cout << "Error item " << c << " not found\n";
		return "";
	}
}
/**********************************************************************
* Template class 
*
**********************************************************************/
int main(){
	
	PriorityQueue pq;
	std::string test;
	test = "GitHub is a development platform inspired by the way you work. From open source to business, you can host and review code, manage projects, and build software alongside 36 million developers.";

	for(int x = 0; x < test.size(); x++){
		pq.add(test[x]);
	}

	pq.sortList(0, pq.size()-1);
	pq.display();

	/*create new internal tree now*/
	tree * weightTree = new tree(pq.size());
	weightTree->fillTree(pq);

	char x = 'l';
	std::string tester = weightTree->findCharToEncode(x);
	std::cout << "FOUND " << tester << "\n";

	std::cout << "TEST08\n";

}