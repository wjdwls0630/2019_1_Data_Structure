/**
*	@mainpage	Array list.
*				This is a simple example of Lab01 on data structures course.<br>
*
*				- Doxygen GUI 설정법<br>
*				Step 1: Doxygen 으로 문서화 할 프로젝트 경로 삽입.<br>
*				Step 2: Wizard 탭에서 Project name 설정.<br>
*				Step 3: Wizard 탭에서 Source code directory 에 문서화 할 소스 경로 지정 후 Scan recursively 를 체크.
*						[Step 1] 의 경로와 같은 경로를 삽입해도 됨.<br>
*				Step 4: Destination directory 에 문서화한 데이터가 저장될 경로 지정.<br>
*				Step 5: Wizard 탭의 Output 에서 LaTeX 체크 해제.<br>
*				Step 6: Run 탭의 Run doxygen 수행 후, "Doxygen has finished" 확인.<br>
*				
*				- 한글사용을 위해서는 Doxywizard에서 아래와 같이 설정할 것.<br>
*				Expert 탭 -> Input (Topics 에서 선택) -> INPUT_ENCODING 을 "EUC-KR" 로 설정.
*
*	@date	2016.04.08 (작성일자 쓸 것!)
*	@author	김동준 (작성자 이름 쓸 것!) 
*/

#include "Application.h"

/**
*	program main function for data structures course.
*/
int main()
{
	Application app;	// Program application
	app.Run();			// run program

	return 0;
}