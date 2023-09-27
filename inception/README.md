# inception
사용 기술 : Dockerfile, Docker-Compose, Shell-Script   
학습 목표 : Docker를 활용해 웹서비스를 구축해보는 과제이다.  
학습 개념 : Linux Container, Docker, Docker-Compose, PID 1, Volume Mount, bridge network  

# details
Docker를 활용해서 웹 서비스를 구축해보는 과제인데  
외부에서 Docker Container에 접근할 수 있는 외부 포트는 443 하나 뿐이며 각 컨테이너는 하나의 서비스만 존재해야 한다.
예시) DB 컨테이너에는 DB 서비스 하나만 포그라운드에서 실행돼야 하는 등 목적에 맞는 서비스만 존재해야 한다.
DB 컨테이너와 웹서비스 컨테이너, nginx 컨테이너 이렇게 세 개의 컨테이너를 구축하여 하나의 웹 서비스를 만들었다.
