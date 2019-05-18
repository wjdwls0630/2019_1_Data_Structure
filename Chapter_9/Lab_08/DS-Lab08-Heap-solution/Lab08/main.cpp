/**
*	@mainpage	Heap.
*
*				Lab08 설명.<br>
*				Heap를 이용해 제품정보를 관리하는 프로그램을 만든다.<br>
*				추가,삭제,출력,검색,종료 기능을 구현한다.<br>
*				ItemType 에서는 제품ID,제품명,제조업자를 관리한다.<br>
*				CHeapBase 에서는 동적할당한 배열에 데이터를 저장하여 추가,삭제,검색,출력 기능을 구현한다.<br>
*				CMaxHeap 는 제품ID를 기준으로 부모데이터가 자식데이터보다 항상 크다.<br>
*				CMinHeap 는 제품ID를 기준으로 부모데이터가 자식데이터보다 항상 작다.<br>
*				각 기능들은 순수가상함수를 이용하여 재귀적으로 구현하였다.<br>
*				Application 에서는 Heap에서 구현한 기능들을 메뉴를 통해 사용할 수 있게 한다.<br>
*
*	@date	2014.11.20
*	@author	김병우 
*/

#include "Application.h"

/**
*	데이터를 불러오는 프로그램의 메인 기능.
*/
int main()
{
	Application app;	// Application 클래스 선언
	app.Run();			// 프로그램 구동

	return 0;
}