jigok-flood-simulator-opengl
=============
Fluid Simulator

-도토리는버스둘태워야서로맛-

[개발 환경]
Visual Studio 2015

[버전 관리]
Github

[실행 방법]
기본적인 실행은 프로젝트를 연 후 ctrl+f5로 프로그램을 실행시킬 수 있다.
이때 fluid simulation을 여려가지로 할 수있는데, 이는 config.h를 조작하므로써 설정을 바꿀 수 있다.
(기본적으로 SIMPLE_RENDER 부터 SCENARIO_JELLY 까지 다 주석처리 되어있다고 생각한다.)

1. SCENARIO_NARROW만 주석 해제 할 경우 일반적인 물의 시뮬레이션을 볼 수 있다.

2. SCENARIO_NARROW, SCENARIO_JELLY를 주석 해제 할 경우 점성이 높은 물의 시뮬레이션을 볼 수 있다.

3. SCENARIO_JIGOK만 주석 해제 할 경우 지곡회관오브젝트를 불러오며, 우리의 목표인 지곡회관에 홍수 시뮬레이션을 할 수 있다.





