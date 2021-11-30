#pragma once
template <typename TL>
class LinkedList
{
public:
	bool headCheck = false;
	LinkedList<TL>* nextNode = NULL;
	LinkedList<TL>* prevNode = NULL;
	TL* data = NULL;

	LinkedList(bool headCheck = false) {
		this->headCheck = headCheck;
	}

	LinkedList<TL>* createNode() {
		LinkedList<TL>* newNode = new LinkedList<TL>;

		LinkedList<TL>* temp = this;
		while (temp->headCheck == false) { temp = temp->prevNode; }

		while (temp->nextNode != NULL) { temp = temp->nextNode; }
		temp->nextNode = newNode;
		newNode->prevNode = temp;
		newNode->nextNode = NULL;

		return newNode;
	}

	void removeNode() {
		if (this->data != NULL)delete this->data;

		if (this->headCheck == false && this->nextNode != NULL) {
			this->prevNode->nextNode = this->nextNode;
			this->nextNode->prevNode = this->prevNode;
			delete this;
		}

		if (this->headCheck == false && this->nextNode == NULL) {
			this->prevNode->nextNode = NULL;
			delete this;
		}
	}

	int size() {
		int count = 0;
		LinkedList<TL>* temp = this;
		while (temp->headCheck != true) { temp = temp->prevNode; }
		while (temp->nextNode != NULL) { temp = temp->nextNode; count++; }
		return count;
	}
};

