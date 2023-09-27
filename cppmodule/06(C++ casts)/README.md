# cppmodule 06
사용 언어 : C++   
학습 목표 : C++에서 명시적 캐스팅을 어떻게 하는지 배우는 단계이다.   
학습 개념 : static_cast, reinterpret_cast, dynamic_cast   

# details
* ex00 : static_cast 컴파일 타임에서의 오류를 잡아주는 캐스팅이다. C에서의 캐스팅보다 한층 안전하게 사용할 수 있는 캐스팅.  

* ex01 : reinterpret_cast C에서의 캐스팅과 동일한 동작을 한다. 자료형과 관계없이 주소접근을 할 때 용이한 캐스팅.  

* ex02 : dynamic_cast 런타임에서 오류를 잡아주는(?) 캐스팅이다. 성공시에는 하고자 했던 형변환을 반환하고 실패했을 때는 null을 리턴하는 것이 포인트이다.(참조자의 경우 예외를 던짐)
