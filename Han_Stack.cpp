#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class Stack {
private:
   int *p_list;
   int size;
   int MAX_SIZE;

public:
   Stack(int _MAX_SIZE = 1000){
      MAX_SIZE = _MAX_SIZE;
      this->size = 0;
      p_list = new int[MAX_SIZE];
   }
   ~Stack() { delete p_list; };
   Stack(Stack &stack) : size(0), MAX_SIZE(1000){
     this->p_list=new int[MAX_SIZE];
     for (int i = 0; i < stack.get_size(); i++) {
       this->p_list[i]=stack.get_item(i);
     }
     // deep copy �� ����� ��
     //���� ���ϸ� �⺻���� shallow copy�� ���󰡼� ��������� �ϴ��� ��Ī �� ������=������ �ϸ� ���� �� ����ų����
     //�����ϸ� ī���Ѱ� ī�Ǵ��Ѱ��� �����Ҵ� �޸𸮸� ����Ŵ �׷��� ī�� �Ѱ� �Ҹ��ϸ� ����(ī�Ǵ��Ѱ�)�� �������� �Ҹ��ڿ��� ������
     //���� ī���Ѱ� �Ҹ��Ű�� ������ ������ �����
     //���� copy constructor ������ �ؾ���
     // ���� ���ο����� Ƽ�� �ȳ��µ� �����Ҵ翡�� �ſ� �߿��� �κ���
     //copy constructor �� ȣ��Ǵ� ���
     /*
     Stack s1(s2); ��� �����Ҷ�
     �Լ� �Ķ���Ͱ� �Լ��� (Stack s1)���� pass by value�� �Ҹ��� s1�� copy constructor ȣ��
     ������ Stack �Լ� �� �϶� ���� ���� �ӽ� ��ü �̹Ƿ� ���� �Ǵ°��� copy constructor ȣ��
     �Լ� �ȿ��� �� ������ �Լ� ������ ��� �Ҹ�Ǵ°� ����? �Ҹ�Ǹ� �Ҹ��� �θ��Ƿ� delete �����ϰ�
     �����ϴ� �ӽð�ü�� ���� �������� ���
     */
   }

   int find_index(int _item) {
      for (int i = 0; i < this->size; i++)
      {
         if (p_list[i] == _item) {
            return i;
         }
      }
      return -1;
   }
   void push(int _item) {
     if (this->size==this->MAX_SIZE) {
       return;
     }
     this->p_list[this->size++]= _item;

   }
   int pop(){
      if (this->size == 0) {
         cout << "Error: NO item exist in the list" << endl;
         return -1;
      }
      this->size--;
      return this->p_list[this->size];
   }
   void print()const{
      cout << "Items in the list : ";
      for (int i = 0; i < this->size; i++)
      {
         cout << p_list[i] << ", ";
      }
      cout << endl;
   }
   int get_size() { return this->size; }
   int get_item(int _index) {
     if (_index>=this->size) {
       std::cout << "Error: index is over" << '\n';
       return -1;
     }
      return this->p_list[_index];
   }
   bool operator==(Stack& _s1) {
     /* �̰͵� ����Ѱ� ������ ���ݴ� ������ �ڵ�� ¥��*/
     if (this->get_size()!=_s1.get_size()) {
       return false;
     }
     for (int i = 0; i < this->get_size(); i++) {
       if (this->get_item(i)!=_s1.get_item(i)) {
         return false;
       }
     }
     return true;
   }
   Stack& operator+=(Stack& _s1) {
    for (int i = 0; i < _s1.get_size(); i++) {
      if (this->find_index(_s1.get_item(i))==-1) {
        this->push(_s1.get_item(i));
      }
    }
    return *this;
  }
};
int main() {
   Stack s1, s2;
   s1.push(1);
   s1.push(2);
   s1.push(3);

   s2.push(1);
   s2.push(2);
   s2.push(5);

   s1.print();
   s2.print();

   s1 += s2;

   s1.print();
   s2.print();

   cout << "s1 == s2 ? " << (s1==s2) << endl;

   s1.pop();
   s1.pop();
   s2.pop();
   cout << "s1 == s2 ? " << (s1 == s2) << endl;
   s2.pop();
   s2.pop();
   s2.pop();

   return 0;
}
