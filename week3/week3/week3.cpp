#include <iostream> //입출력 스트림
#include <vector>//배열
#include <Windows.h>//키보드 입력을 모니터링

bool running = true;//프로그램이 실행중인지 여부를 나타내는 boolean변수를 초기화 

int main() {
    std::vector<WORD> inputSequence;//입력한 키 저장하기 위한 배열 생성

    while (running) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            running = false;
            break;
        } //esc키를 누르면 프로그램 종료

        if (inputSequence.size() < 3) {//키를 3개까지만 입력받도록 배열의 크기를 3으로 지정함
            if (GetAsyncKeyState(VK_RIGHT)) {//오른쪽 방향키
                inputSequence.push_back(VK_RIGHT);//배열에 추가
                Sleep(300);//오른쪽 방향키가 눌린 경우 배열에 추가하고 0.3초 동안 대기
            }
            else if (GetAsyncKeyState(VK_DOWN)) {//아래 방향키
                inputSequence.push_back(VK_DOWN);//배열에 추가
                Sleep(300);//아래 방향키가 눌린 경우 배열에 추가하고 0.3초 동안 대기
            }
            else if (GetAsyncKeyState(0x41)) { // 'A' 키
                inputSequence.push_back(0x41);//배열에 추가
                Sleep(300);//a키가 눌린 경우 배열에 추가하고 0.3초 동안 대기
            }
            else if (GetAsyncKeyState(0x46)) { // 'f' 키
                inputSequence.push_back(0x46);//배열에 추가
                Sleep(300); // 'f' 키가 눌린 경우 배열에 추가하고 0.3초 동안 대기
            }
        }
        else {
            if (inputSequence[0] == VK_DOWN && inputSequence[1] == VK_RIGHT && inputSequence[2] == 0x41) {
                std::cout << "아도겐! =o" << std::endl;
            }// 아래 오른쪽 a 를 눌렀을 때 아도겐 이라고 출력
            else if (inputSequence[0] == VK_DOWN && inputSequence[1] == VK_RIGHT && inputSequence[2] == 0x46) {
                std::cout << "뻐큐! ( -_-)-ㅗ" << std::endl;
            }//아래 오른쪽 f 를 눌렀을 때 뻐큐 출력
            else if (inputSequence[0] == VK_RIGHT && inputSequence[1] == VK_DOWN && inputSequence[2] == 0x41) {
                std::cout << "ㅎㅇ" << std::endl;
            }//오른쪽 아래 a 를 눌렀을 때 하이 출력
            else if (inputSequence[0] == VK_RIGHT && inputSequence[1] == VK_DOWN && inputSequence[2] == 0x46) {
                std::cout << "ㅂㅇ" << std::endl;
            }//오른쪽 아래 f 를 눌렀을 때 바이 출력
           
            inputSequence.clear();//새로운 값을 받기 위해 배열 초기화
        }
    }

    return 0;//프로그램 정상종료
}
//***다른 단어가 섞여 있을 때도 정상적으로 프로그램이 작동하는 것 추가해야함***