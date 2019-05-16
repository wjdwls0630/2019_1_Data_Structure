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
     // deep copy 를 해줘야 함
     //정의 안하면 기본으로 shallow copy를 따라가서 멤버변수가 일대일 매칭 됨 포인터=포인터 하면 같을 걸 가리킬거임
     //안정하면 카피한게 카피당한거의 동적할당 메모리를 가리킴 그러면 카피 한걸 소멸하면 원본(카피당한것)도 없어져서 소멸자에서 에러남
     //또한 카피한걸 소멸시키면 원본의 정보도 사라짐
     //따라서 copy constructor 재정의 해야함
     // 지금 메인에서는 티가 안나는데 동적할당에서 매우 중요한 부분임
     //copy constructor 가 호출되는 경우
     /*
     Stack s1(s2); 라고 선언할때
     함수 파라미터가 함수명 (Stack s1)으로 pass by value로 불릴때 s1이 copy constructor 호출
     리턴이 Stack 함수 명 일때 리턴 값은 임시 객체 이므로 대응 되는것이 copy constructor 호출
     함수 안에서 쓴 변수는 함수 끝나면 모두 소멸되는거 알지? 소멸되면 소멸자 부르므로 delete 생각하고
     리턴하는 임시객체가 어디로 가는지도 고려
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
     /* 이것도 비슷한것 같은데 조금더 괜찮은 코드로 짜봄*/
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
