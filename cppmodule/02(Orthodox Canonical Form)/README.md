# cppmodule 02
사용 언어 : C++   
학습 목표 : Orthodox Canonical Form을 지키며 클래스를 제작해야함.  
학습 개념 : Overload, 고정소수점, 부동소수점  

# details
* ex00에서 고정소수점을 저장하는 클래스를 Orthodox canonical form에 맞춰 작성하게 했다.


* ex01에서 int와 float를 받는 생성자를 만들고 고정소수점 값을 출력하는 멤버함수 제작과 함께 std::cout의 << 연산자를 오버로드해서 고정소수점 클래스를 출력하려고 할 때 고정소수점 값을 출력하게 만들었다.

* ex02에서 고정소수점 클래스의 연산자를 전부 구현하고(>, < , >=, <=, == , !=, +, -, \*, /, ++(전위, 후위), --(전위, 후위)) static 멤버함수인 min, max를 구현했다.   
여기서 주의할 점은 이미 고정소수점으로 만들어버린 경우는 곱셈, 나눗셈 연산을 할 때 변형된 값(현재 가지고 있는 값)으로 하게 되면 계산이 매우 크게 달라지므로 원형으로 돌려놓은 뒤에 계산을 해야 한다.

* ex03에서 현재까지 만들어놓은 클래스를 기반으로 삼각형과 점이 주어졌을 때 이 점이 삼각형 내부에 위치하는지 아닌지를 판별하는 함수를 만들었다.
