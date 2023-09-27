# cppmodule 03
사용 언어 : C++   
학습 목표 : 클래스를 상속하는 방법과 다이아몬드 상속이라는 문제점에 대해 알아봐야 함  
학습 개념 : 상속, 가상 상속, 다이아몬드 상속, Override, Protect  

# details
* ex00에서 기반이 될 클래스를 제작한다.

* ex01에서는 ex00에서 제작한 클래스를 상속받아서 생성자를 호출할 때 부모 클래스의 생성자를 호출하는 법, 그리고 생성/파괴 시에 일어나는 순서가 부모생성->자식생성 / 자식파괴->부모파괴 순으로 일어나는 것을 메시지를 명시적으로 출력함으로 확인할 수 있음.

* ex02는 ex01과 똑같은 방법으로 ex01과는 다른 자식 클래스를 만드는 것이다.

* ex03에서는 ex01, ex02에서 만든 클래스를 상속받는 기이한 형태의 클래스를 제작하는 것인데 문제점이 두 가지가 있다.  
1. 컴파일러가 상속 관계에서 생기는 모호함 때문에 컴파일이 불가능한 점.  
2. 가상상속을 통해 1번의 문제를 해결해도 공통된 값이 존재할 경우 가장 나중에 상속받는 클래스를 기준으로 덮어써지는 점.  
이렇게 두 가지가 존재하여 해당 문제점들을 알아보는 과제이며 어떻게 피하면 될지 고민하는 과제이다.