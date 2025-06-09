#include <iostream>

using namespace std;

template<typename T, typename E>
class Element {
public:
    E priority;
    T value;
    //int index;
    Element<T, E>(T value, E priority){
        this->value = value;
        this->priority = priority;
    }
};

template<typename T, typename E>
class UniversalQueueWithPriorities {
public:
    Element<T, E>* mainArray[64];
    int elementCount = 0;
    void enqueue(Element<T, E>* elem) {
        if (elementCount < 64) {
            mainArray[elementCount] = elem;
            elementCount += 1;
            int i = elementCount - 1;
            int parent = (i - 1) / 2;
            while (i > 0 && mainArray[parent]->priority < mainArray[i]->priority) {
                Element<T, E>* temp = mainArray[i];
                mainArray[i] = mainArray[parent];
                mainArray[parent] = temp;
                i = parent;
                parent = (i - 1) / 2;
            }
        }
    }
    Element<T, E>* dequeue() {
        Element<T, E>* temp = mainArray[0];
        mainArray[0] = mainArray[elementCount - 1];
        int i = 0;
        while (2 * i + 1 < elementCount) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int j = left;
            if (right < elementCount and mainArray[left] < mainArray[right]) {
                j = right;
            }
            if (mainArray[i] > mainArray[j]) {
                break;
            }
            Element<T, E>* temp2 = mainArray[i];
            mainArray[i] = mainArray[j];
            mainArray[j] = temp2;
            i = j;
        }
        return temp;
    }
    Element<T, E>* peek() {
        return mainArray[0];
    }
    void increasePriority(int index) {
        if (1 <= index && index <= elementCount - 1) {
            T temp = mainArray[index]->value;
            mainArray[index]->value = mainArray[(index - 1) / 2]->value;
            mainArray[(index - 1) / 2]->value = temp;
        }
    }
    void decreasePriority(int index) {
        if (1 <= index && index <= elementCount - 2) {
            T temp = mainArray[index]->value;
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int j = left;
            if (right <= elementCount - 1 && mainArray[left]->value < mainArray[right]->value) {
                j = right;
            }
            mainArray[index]->value = mainArray[j]->value;
            mainArray[j] = temp;
        }
    }
};

int main()
{
    Element<int, int> el{9, 1};
    Element<int, int> el2{10, 2};
    Element<int, int> el3{11, 3};
    Element<int, int> el4{12, 4};
    Element<int, int> el5{20, 20};
    UniversalQueueWithPriorities<int, int> queue{};
    queue.enqueue(&el);
    queue.enqueue(&el2);
    queue.enqueue(&el3);
    queue.increasePriority(1);
    cout << queue.peek()->value;
}
