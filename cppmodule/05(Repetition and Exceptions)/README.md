# cppmodule 05
사용 언어 : C++   
학습 목표 : 예외 발생 시에 프로그램이 종료되지 않도록 예외를 던지는 방법과 예외가 던져졌을 때 어떤 흐름으로 바깥에서 예외를 잡을 수 있는지에 대한 내용이다.   
학습 개념 : try-catch, std::exception, throw, stack unwinding   

# details
* ex00에서 공무원 클래스를 제작하고 생성자에서 등급을 숫자로 받는데, 정해진 숫자 이외의 값이들어오면 예외를 던지는 클래스를 제작한다.

* ex01에서 서명과 실행에 대한 등급제한이 존재하는 양식 클래스를 제작한다. 만약 각 등급제한에 어긋나는게 들어오면 예외를 던져야 한다.

* ex02에서는 ex01에서 제작한 양식 클래스를 상속받아서 서명과 실행을 실제로 동작하게 하는 클래스들을 제작하는데, 실행에 대한 함수만 클래스별로 Override하고 나머지는 상속받은 양식 클래스의 함수들을 동작하게 한다.

* ex03에서는 문자열을 받아서 해당 문자열과 일치하는 양식클래스를 생성하여 반환하는 인턴 클래스를 제작한다.
